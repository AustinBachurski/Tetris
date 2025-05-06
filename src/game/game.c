#include "game.h"

#include "gamesettings.h"
#include "input.h"
#include "../ui/ui.h"
#include "../tetrimino/movement.h"
#include "../tetrimino/tetrimino.h"

#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define ONE_SECOND_US 1000000

#ifdef UNIT_TEST
    #define INTERNAL /* as nothing for unit testing */
#else
    #define INTERNAL static
#endif

INTERNAL void clear_playfield(GameData *game);
static void cycle_in_next_tetrimino(GameData *game);
[[nodiscard]] INTERNAL bool is_game_over(GameData *game);
static TetriminoColor get_next_tetrimino(TetriminoColor bag[]);
static void initialize_game(GameData *game);
[[nodiscard]] static bool is_time_for_gravity(GameData *game);
INTERNAL Tetrimino make_random_tetrimino(TetriminoColor bag[]);
static void new_game(GameData *game, atomic_int *command, pthread_t *inputThread);
static TetriminoColor only_one_remains(TetriminoColor bag[]);
static void place_tetrimino(GameData *game);
INTERNAL void reset_bag(TetriminoColor bag[]);
[[nodiscard]] static int spawnpoint_for(TetriminoColor const color);
static void wait_for_keypress(GameData *game);

void play_tetris(void)
{
    GameData game;
    initialize_game(&game);

    atomic_int command;
    atomic_init(&command, (int)Command_doNothing);

    pthread_t inputThread;
    pthread_create(&inputThread, NULL, read_user_input, &command);

    while (true)
    {
        draw_playfield(&game);

        move_tetrimino(&game, &command);

        if (!is_time_for_gravity(&game))
        {
            continue;
        }

        if (gravity_down(&game))
        {
            gettimeofday(&game.dropTime, NULL);
            continue;
        }

        if (!is_game_over(&game))
        {
            cycle_in_next_tetrimino(&game);
            gettimeofday(&game.dropTime, NULL);
            continue;
        }

        if (game_over_exit(&game, &command))
        {
            break;
        }
        else
        {
            new_game(&game, &command, &inputThread);
        }
    }

    pthread_cancel(inputThread);

    mvwprintw(game.ui.previewWindow, 2, 1, "Exiting!");
    wrefresh(game.ui.previewWindow);

    pthread_join(inputThread, NULL);

    exit_game(0);
}

INTERNAL void clear_playfield(GameData *game)
{
    memset(game->playfield, 0, PLAYFIELD_SIZE * sizeof(TetriminoColor));
}

static void cycle_in_next_tetrimino(GameData *game)
{
    game->currentTetrimino = game->nextTetrimino;
    game->nextTetrimino = make_random_tetrimino(game->randomBag);
    place_tetrimino(game);
    set_preview(game);
}

static TetriminoColor get_next_tetrimino(TetriminoColor bag[])
{
    TetriminoColor selection = only_one_remains(bag);

    if (Tetrimino_empty != selection)
    {
        reset_bag(bag);
        return selection;
    }

    int index = rand() % (TETRIMINO_COUNT - 1);

    while (Tetrimino_empty == bag[index])
    {
        index = rand() % (TETRIMINO_COUNT - 1);
    }

    selection = bag[index];
    bag[index] = Tetrimino_empty;

    return selection;
}

static bool is_time_for_gravity(GameData *game)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    long diffSeconds = now.tv_sec - game->dropTime.tv_sec;
    long diffMicroseconds = now.tv_usec - game->dropTime.tv_usec;

    double diff = (double)(diffSeconds * ONE_SECOND_US + diffMicroseconds);

    double compare = ONE_SECOND_US * game->difficulty;

    bool result = diff >= compare;
    return result;
}

static void initialize_game(GameData *game)
{
    srand((unsigned int)time(NULL));
    reset_bag(game->randomBag);
    game->nextTetrimino = make_random_tetrimino(game->randomBag);
    game->difficulty = 1.0;

    clear_playfield(game);
    initialize_ui(game);
    set_preview(game);
    wait_for_keypress(game);
    cycle_in_next_tetrimino(game);
    gettimeofday(&game->dropTime, NULL);
}

INTERNAL Tetrimino make_random_tetrimino(TetriminoColor bag[])
{
    TetriminoColor const color = get_next_tetrimino(bag);

    return (Tetrimino){ spawnpoint_for(color), color, North };
}

static void new_game(GameData *game,
                     atomic_int *command, pthread_t *inputThread)
{
    pthread_cancel(*inputThread);
    pthread_join(*inputThread, NULL);

    initialize_game(game);

    pthread_create(inputThread, NULL, read_user_input, command);
    atomic_store_explicit(command,
                          (int)Command_doNothing,
                          memory_order_release);
}

static TetriminoColor only_one_remains(TetriminoColor bag[])
{
    TetriminoColor selection = Tetrimino_empty;

    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        if (Tetrimino_empty != bag[i])
        {
            if (Tetrimino_empty != selection)
            {
                return Tetrimino_empty;
            }

            selection = bag[i];
        }
    }

    return selection;
}

static void place_tetrimino(GameData *game)
{
    int indices[SQUARES_PER_TETRIMINO];
    indices_for(&game->currentTetrimino, indices);

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indices[i]] = game->currentTetrimino.type;
    }
}

INTERNAL void reset_bag(TetriminoColor bag[])
{
    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        bag[i] = (TetriminoColor)(i + 1);
    }
}

INTERNAL bool is_game_over(GameData *game)
{
    int indices[SQUARES_PER_TETRIMINO];
    indices_for(&game->nextTetrimino, indices);

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (Tetrimino_empty != game->playfield[indices[i]])
        {
            return true;
        }
    }
    return false;
}

static int spawnpoint_for(TetriminoColor const color)
{
    switch (color)
    {
        case Tetrimino_empty:
            // TODO: Should never happen.
            break;

        case Tetrimino_lightBlue:
            return LIGHTBLUE_SPAWNPOINT;

        case Tetrimino_darkBlue:
            return DARKBLUE_SPAWNPOINT;

        case Tetrimino_orange:
            return ORANGE_SPAWNPOINT;

        case Tetrimino_yellow:
            return YELLOW_SPAWNPOINT;

        case Tetrimino_green:
            return GREEN_SPAWNPOINT;

        case Tetrimino_red:
            return RED_SPAWNPOINT;

        case Tetrimino_magenta:
            return MAGENTA_SPAWNPOINT;
    }

    return -1;
}

static void wait_for_keypress(GameData *game)
{
    mvwprintw(game->ui.playfieldWindow, 8, 4, "Press any key");
    mvwprintw(game->ui.playfieldWindow, 9, 5, "to begin...");
    wrefresh(game->ui.playfieldWindow);
    getch();
    mvwprintw(game->ui.playfieldWindow, 8, 4, "             ");
    mvwprintw(game->ui.playfieldWindow, 9, 5, "           ");
    wrefresh(game->ui.playfieldWindow);
}

