#include "game.h"

#include <string.h>

int rungame(void)
{
    Game game;
    initialize_game(&game);

    spawn_tetrimino(&game);
    show_preview(&game);

    return 0;
}

void initialize_game(Game *game)
{
    initialize_ui(&game->ui);

}

void clear_playfield(Game *game)
{
    memset(game->playfield, 0, PLAYFIELD_SIZE * sizeof(TetriminoColor));
}

void clear_preview(Game *game)
{
    memset(game->preview, 0, PREVIEW_SIZE * sizeof(TetriminoColor));
}

void reset_bag(TetriminoColor bag[])
{
    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        bag[i] = (TetriminoColor)(i + 1);
    }
}

void spawn_tetrimino(Game *game)
{
    switch (game->currentTetrimino.type)
    {
        case Tetrimino_empty:
            // TODO: Should never happen - how to handle error?
            return;

        //   [ ][*][ ][ ]
        case Tetrimino_lightBlue:
            game->currentTetrimino.centroidRow = 0;
            game->currentTetrimino.centroidColumn = 4;
            playfield[0][3] = game->currentTetrimino.type;
            playfield[0][4] = game->currentTetrimino.type;
            playfield[0][5] = game->currentTetrimino.type;
            playfield[0][6] = game->currentTetrimino.type;
            return;

        //   [ ]
        //   [ ][*][ ]
        case Tetrimino_darkBlue:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            playfield[0][3] = game->currentTetrimino.type;
            playfield[1][3] = game->currentTetrimino.type;
            playfield[1][4] = game->currentTetrimino.type;
            playfield[1][5] = game->currentTetrimino.type;
            return;

        //         [ ]
        //   [ ][*][ ]
        case Tetrimino_orange:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            playfield[1][3] = game->currentTetrimino.type;
            playfield[1][4] = game->currentTetrimino.type;
            playfield[1][5] = game->currentTetrimino.type;
            playfield[0][5] = game->currentTetrimino.type;
            return;

        //   [ ][ ]
        //   [*][ ]
        case Tetrimino_yellow:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            playfield[0][4] = game->currentTetrimino.type;
            playfield[0][5] = game->currentTetrimino.type;
            playfield[1][4] = game->currentTetrimino.type;
            playfield[1][5] = game->currentTetrimino.type;
            return;

        //   [ ][ ]
        //      [*][ ]
        case Tetrimino_red:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            playfield[0][3] = game->currentTetrimino.type;
            playfield[0][4] = game->currentTetrimino.type;
            playfield[1][4] = game->currentTetrimino.type;
            playfield[1][5] = game->currentTetrimino.type;
            return;

        //      [ ][ ]
        //   [ ][*]
        case Tetrimino_green:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            playfield[0][4] = game->currentTetrimino.type;
            playfield[0][5] = game->currentTetrimino.type;
            playfield[1][3] = game->currentTetrimino.type;
            playfield[1][4] = game->currentTetrimino.type;
            return;

        //      [ ]
        //   [ ][*][ ]
        case Tetrimino_magenta:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            playfield[0][4] = game->currentTetrimino.type;
            playfield[1][3] = game->currentTetrimino.type;
            playfield[1][4] = game->currentTetrimino.type;
            playfield[1][5] = game->currentTetrimino.type;
            return;
    }
}

void show_preview(Game *game)
{
    switch (game->currentTetrimino.type)
    {
        case Tetrimino_empty:
            // TODO: Should never happen - how to handle error?
            return;

        //   [ ][*][ ][ ]
        case Tetrimino_lightBlue:
            game->currentTetrimino.centroidRow = 0;
            game->currentTetrimino.centroidColumn = 4;
            preview[0][1] = game->currentTetrimino.type;
            preview[0][2] = game->currentTetrimino.type;
            preview[0][3] = game->currentTetrimino.type;
            preview[0][4] = game->currentTetrimino.type;
            return;

        //   [ ]
        //   [ ][*][ ]
        case Tetrimino_darkBlue:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            preview[0][1] = game->currentTetrimino.type;
            preview[1][1] = game->currentTetrimino.type;
            preview[1][2] = game->currentTetrimino.type;
            preview[1][3] = game->currentTetrimino.type;
            return;

        //         [ ]
        //   [ ][*][ ]
        case Tetrimino_orange:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            preview[1][1] = game->currentTetrimino.type;
            preview[1][2] = game->currentTetrimino.type;
            preview[1][3] = game->currentTetrimino.type;
            preview[0][3] = game->currentTetrimino.type;
            return;

        //   [ ][ ]
        //   [*][ ]
        case Tetrimino_yellow:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            preview[0][2] = game->currentTetrimino.type;
            preview[0][3] = game->currentTetrimino.type;
            preview[1][2] = game->currentTetrimino.type;
            preview[1][3] = game->currentTetrimino.type;
            return;

        //   [ ][ ]
        //      [*][ ]
        case Tetrimino_red:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            preview[0][1] = game->currentTetrimino.type;
            preview[0][2] = game->currentTetrimino.type;
            preview[1][2] = game->currentTetrimino.type;
            preview[1][3] = game->currentTetrimino.type;
            return;

        //      [ ][ ]
        //   [ ][*]
        case Tetrimino_green:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            preview[0][2] = game->currentTetrimino.type;
            preview[0][3] = game->currentTetrimino.type;
            preview[1][1] = game->currentTetrimino.type;
            preview[1][2] = game->currentTetrimino.type;
            return;

        //      [ ]
        //   [ ][*][ ]
        case Tetrimino_magenta:
            game->currentTetrimino.centroidRow = 1;
            game->currentTetrimino.centroidColumn = 4;
            preview[0][2] = game->currentTetrimino.type;
            preview[1][1] = game->currentTetrimino.type;
            preview[1][2] = game->currentTetrimino.type;
            preview[1][3] = game->currentTetrimino.type;
            return;
    }
}

