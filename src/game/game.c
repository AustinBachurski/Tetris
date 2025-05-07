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
#include <time.h>

#ifdef UNIT_TEST
    #define INTERNAL /* as nothing for unit testing */
#else
    #define INTERNAL static
#endif

INTERNAL void clear_playfield(GameData *game);
static void cycle_in_next_tetrimino(GameData *game);
static void game_loop(GameData *game, InputHandles *input, FrameTime *times);
[[nodiscard]] INTERNAL bool is_game_over(GameData *game);
static TetriminoColor get_next_tetrimino(TetriminoColor bag[]);
static void initialize_game(GameData *game);
static void initialize_input(InputHandles *input);
static void initialize_time(FrameTime *times);
[[nodiscard]] static bool is_time_for_gravity(GameData *game);
INTERNAL Tetrimino make_random_tetrimino(TetriminoColor bag[]);
static void new_game(GameData *game, InputHandles *input);
static TetriminoColor only_one_remains(TetriminoColor bag[]);
static void place_tetrimino(GameData *game);
INTERNAL void reset_bag(TetriminoColor bag[]);
static void sleep_for(FrameTime *times);
[[nodiscard]] static int spawnpoint_for(TetriminoColor const color);
static void wait_for_keypress(GameData *game);

void play_tetris(void)
{
    GameData game;
    InputHandles input;
    FrameTime times;

    initialize_game(&game);
    initialize_input(&input);
    initialize_time(&times);

    game_loop(&game, &input, &times);

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
    gettimeofday(&game->dropTime, NULL);
}

static void game_loop(GameData *game, InputHandles *input, FrameTime *times)
{
    while (true)
    {
        draw_playfield(game);
        move_tetrimino(game, &input->command);

        if (is_time_for_gravity(game))
        {
            if (!gravity_down(game))
            {
                if (!is_game_over(game))
                {
                    cycle_in_next_tetrimino(game);
                }
                else if (play_again(game, input))
                {
                    new_game(game, input);
                }
                else
                {
                    break;
                }
            }
        }

        sleep_for(times);
    }

    pthread_cancel(input->thread);
    pthread_join(input->thread, NULL);
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

    long deltaSeconds = now.tv_sec - game->dropTime.tv_sec;
    long deltaMicroseconds = now.tv_usec - game->dropTime.tv_usec;

    long deltaTime = deltaSeconds * MICROSECONDS_PER_SECOND + deltaMicroseconds;
    float moveTime = MICROSECONDS_PER_SECOND * game->difficulty;

    if ((float)deltaTime >= moveTime)
    {
        gettimeofday(&game->dropTime, NULL);
        return true;
    }

    return false;
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
}

static void initialize_input(InputHandles *input)
{
    atomic_init(&input->command, (int)Command_doNothing);
    pthread_create(&input->thread, NULL, read_user_input, &input->command);
}

static void initialize_time(FrameTime *times)
{
    times->loopStart.tv_sec = 0;
    times->loopStart.tv_usec = 0;
    times->loopEnd.tv_sec = 0;
    times->loopEnd.tv_usec = 0;
    times->delta.tv_sec = 0;
    times->delta.tv_nsec = 0;
}

INTERNAL Tetrimino make_random_tetrimino(TetriminoColor bag[])
{
    TetriminoColor const color = get_next_tetrimino(bag);

    return (Tetrimino){ spawnpoint_for(color), color, North };
}

static void new_game(GameData *game, InputHandles *input)
{
    pthread_cancel(input->thread);
    pthread_join(input->thread, NULL);

    initialize_game(game);

    pthread_create(&input->thread, NULL, read_user_input, &input->command);
    atomic_store_explicit(&input->command,
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

static void sleep_for(FrameTime *times)
{
    gettimeofday(&times->loopEnd, NULL);

    long frameTime = times->loopEnd.tv_usec - times->loopStart.tv_usec;

    if (frameTime < TARGET_FRAME_TIME)
    {
        times->delta.tv_nsec =
            (TARGET_FRAME_TIME - frameTime) * NANOSECONDS_PER_MICROSECOND;

        nanosleep(&times->delta, NULL);
    }

    gettimeofday(&times->loopStart, NULL);
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

