#include "game.h"
#include "gamesettings.h"
#include "../ui/ui.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

void play_tetris(void)
{
    GameData game;
    initialize_game(&game);

    while (true)
    {
        draw_playfield(&game);
    }


    exit_game(0);
}

void initialize_game(GameData *game)
{
    srand(time(NULL));
    reset_bag(game->randomBag);
    game->nextTetrimino = make_random_tetrimino(game->randomBag);
    initialize_ui(game);
    set_preview(game);
    wait_for_keypress(game);
    cycle_in_next_tetrimino(game);
}

void cycle_in_next_tetrimino(GameData *game)
{
    game->currentTetrimino = game->nextTetrimino;
    game->nextTetrimino = make_random_tetrimino(game->randomBag);
    spawn_tetrimino(game);
    set_preview(game);
}

void wait_for_keypress(GameData *game)
{
    mvwprintw(game->ui.playfieldWindow, 8, 4, "Press any key");
    mvwprintw(game->ui.playfieldWindow, 9, 5, "to begin...");
    wrefresh(game->ui.playfieldWindow);
    getch();
    mvwprintw(game->ui.playfieldWindow, 8, 4, "             ");
    mvwprintw(game->ui.playfieldWindow, 9, 5, "           ");
    wrefresh(game->ui.playfieldWindow);
}

void clear_playfield(GameData *game)
{
    memset(game->playfield, 0, PLAYFIELD_SIZE * sizeof(TetriminoColor));
}

void reset_bag(TetriminoColor bag[])
{
    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        bag[i] = (TetriminoColor)(i + 1);
    }
}

Tetrimino make_random_tetrimino(TetriminoColor bag[])
{
    return (Tetrimino){ 0, get_next_tetrimino(bag), Facing_up };
}

TetriminoColor only_one_remains(TetriminoColor bag[])
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

TetriminoColor get_next_tetrimino(TetriminoColor bag[])
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

void spawn_tetrimino(GameData *game)
{
    switch (game->currentTetrimino.type)
    {
        case Tetrimino_empty:
            // TODO: Should never happen.
            return;

        //   [ ][*][ ][ ]
        case Tetrimino_lightBlue:
            game->currentTetrimino.centroid = LIGHTBLUE_SPAWNPOINT;
            game->playfield[3] = game->currentTetrimino.type;
            game->playfield[4] = game->currentTetrimino.type;
            game->playfield[5] = game->currentTetrimino.type;
            game->playfield[6] = game->currentTetrimino.type;
            return;

        //   [ ]
        //   [ ][*][ ]
        case Tetrimino_darkBlue:
            game->currentTetrimino.centroid = DARKBLUE_SPAWNPOINT;
            game->playfield[3] = game->currentTetrimino.type;
            game->playfield[13] = game->currentTetrimino.type;
            game->playfield[14] = game->currentTetrimino.type;
            game->playfield[15] = game->currentTetrimino.type;
            return;

        //         [ ]
        //   [ ][*][ ]
        case Tetrimino_orange:
            game->currentTetrimino.centroid = ORANGE_SPAWNPOINT;
            game->playfield[5] = game->currentTetrimino.type;
            game->playfield[13] = game->currentTetrimino.type;
            game->playfield[14] = game->currentTetrimino.type;
            game->playfield[15] = game->currentTetrimino.type;
            return;

        //   [ ][ ]
        //   [*][ ]
        case Tetrimino_yellow:
            game->currentTetrimino.centroid = YELLOW_SPAWNPOINT;
            game->playfield[4] = game->currentTetrimino.type;
            game->playfield[5] = game->currentTetrimino.type;
            game->playfield[14] = game->currentTetrimino.type;
            game->playfield[15] = game->currentTetrimino.type;
            return;

        //   [ ][ ]
        //      [*][ ]
        case Tetrimino_red:
            game->currentTetrimino.centroid = RED_SPAWNPOINT;
            game->playfield[3] = game->currentTetrimino.type;
            game->playfield[4] = game->currentTetrimino.type;
            game->playfield[14] = game->currentTetrimino.type;
            game->playfield[15] = game->currentTetrimino.type;
            return;

        //      [ ][ ]
        //   [ ][*]
        case Tetrimino_green:
            game->currentTetrimino.centroid = GREEN_SPAWNPOINT;
            game->playfield[4] = game->currentTetrimino.type;
            game->playfield[5] = game->currentTetrimino.type;
            game->playfield[13] = game->currentTetrimino.type;
            game->playfield[14] = game->currentTetrimino.type;
            return;

        //      [ ]
        //   [ ][*][ ]
        case Tetrimino_magenta:
            game->currentTetrimino.centroid = MAGENTA_SPAWNPOINT;
            game->playfield[4] = game->currentTetrimino.type;
            game->playfield[13] = game->currentTetrimino.type;
            game->playfield[14] = game->currentTetrimino.type;
            game->playfield[15] = game->currentTetrimino.type;
            return;
    }
}

