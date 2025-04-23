#include "game.h"

#include "gamesettings.h"
#include "../ui/ui.h"
#include "../tetrimino/movement.h"
#include "../tetrimino/tetrimino.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

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
INTERNAL Tetrimino make_random_tetrimino(TetriminoColor bag[]);
static TetriminoColor only_one_remains(TetriminoColor bag[]);
static void place_tetrimino(GameData *game, int const indices[]);
INTERNAL void reset_bag(TetriminoColor bag[]);
[[nodiscard]] static bool space_is_occupied(GameData* game, int const indices[]);
INTERNAL void spawn_tetrimino(GameData *game);
static void wait_for_keypress(GameData *game);

int const lightBlueSpawnIndices[SQUARES_PER_TETRIMINO] = { 3, 4, 5, 6, };
int const darkBlueSpawnIndices[SQUARES_PER_TETRIMINO] = { 3, 13, 14, 15, };
int const orangeSpawnIndices[SQUARES_PER_TETRIMINO] = { 5, 13, 14, 15, };
int const yellowSpawnIndices[SQUARES_PER_TETRIMINO] = { 4, 5, 14, 15 };
int const greenSpawnIndices[SQUARES_PER_TETRIMINO] = { 4, 5, 13, 14 };
int const redSpawnIndices[SQUARES_PER_TETRIMINO] = { 3, 4, 14, 15 };
int const magentaSpawnIndices[SQUARES_PER_TETRIMINO] = { 4, 13, 14, 15 };

void play_tetris(void)
{
    GameData game;
    initialize_game(&game);

    while (true)
    {
        draw_playfield(&game);

        const char choice = (char)getch();
        move_tetrimino(&game, choice);

        /*
        if (!move_down(&game))
        {
            if (!is_game_over(&game))
            {
                cycle_in_next_tetrimino(&game);
            }
            else
            {
                show_game_over(&game);  // May exit application.
                initialize_game(&game);
            }
        }
    */
    }

    if (is_game_over(&game))
    {
        exit_game(1);
    }

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
    spawn_tetrimino(game);
    set_preview(game);
}

INTERNAL bool is_game_over(GameData *game)
{
    switch (game->nextTetrimino.type)
    {
        case Tetrimino_empty:
            // TODO: Should never happen - how to handle error?
            return true;

        case Tetrimino_lightBlue:
            return space_is_occupied(game, lightBlueSpawnIndices);

        case Tetrimino_darkBlue:
            return space_is_occupied(game, darkBlueSpawnIndices);

        case Tetrimino_orange:
            return space_is_occupied(game, orangeSpawnIndices);

        case Tetrimino_yellow:
            return space_is_occupied(game, yellowSpawnIndices);

        case Tetrimino_green:
            return space_is_occupied(game, greenSpawnIndices);

        case Tetrimino_red:
            return space_is_occupied(game, redSpawnIndices);

        case Tetrimino_magenta:
            return space_is_occupied(game, magentaSpawnIndices);
    }

    return true; // TODO: Handle this.
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

static void initialize_game(GameData *game)
{
    srand((unsigned int)time(NULL));
    reset_bag(game->randomBag);
    game->nextTetrimino = make_random_tetrimino(game->randomBag);

    clear_playfield(game);
    initialize_ui(game);
    set_preview(game);
    wait_for_keypress(game);
    cycle_in_next_tetrimino(game);
}

INTERNAL Tetrimino make_random_tetrimino(TetriminoColor bag[])
{
    return (Tetrimino){ 0, get_next_tetrimino(bag), Facing_up };
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

static void place_tetrimino(GameData *game, int const indices[])
{
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

static bool space_is_occupied(GameData* game, int const indices[])
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (Tetrimino_empty != game->playfield[indices[i]])
        {
            return true;
        }
    }
    return false;
}

INTERNAL void spawn_tetrimino(GameData *game)
{
    switch (game->currentTetrimino.type)
    {
        case Tetrimino_empty:
            // TODO: Should never happen.
            return;

        case Tetrimino_lightBlue:
            game->currentTetrimino.centroid = LIGHTBLUE_SPAWNPOINT;
            place_tetrimino(game, lightBlueSpawnIndices);
            return;

        case Tetrimino_darkBlue:
            game->currentTetrimino.centroid = DARKBLUE_SPAWNPOINT;
            place_tetrimino(game, darkBlueSpawnIndices);
            return;

        case Tetrimino_orange:
            game->currentTetrimino.centroid = ORANGE_SPAWNPOINT;
            place_tetrimino(game, orangeSpawnIndices);
            return;

        case Tetrimino_yellow:
            game->currentTetrimino.centroid = YELLOW_SPAWNPOINT;
            place_tetrimino(game, yellowSpawnIndices);
            return;

        case Tetrimino_green:
            game->currentTetrimino.centroid = GREEN_SPAWNPOINT;
            place_tetrimino(game, greenSpawnIndices);
            return;

        case Tetrimino_red:
            game->currentTetrimino.centroid = RED_SPAWNPOINT;
            place_tetrimino(game, redSpawnIndices);
            return;

        case Tetrimino_magenta:
            game->currentTetrimino.centroid = MAGENTA_SPAWNPOINT;
            place_tetrimino(game, magentaSpawnIndices);
            return;
    }
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

