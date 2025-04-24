#include "moveright.h"

#include "tetrimino.h"
#include "validation.h"
#include "../game/game.h"
#include "../game/gamesettings.h"

static void indices_for_right(Tetrimino *current, int indices[]);
static bool is_self(int indices[], int current);

void move_tetrimino_right(GameData *game)
{
    int indices[SQUARES_PER_TETRIMINO];
    indices_for_right(&game->currentTetrimino, indices);

    if (!valid_move(game->playfield, indices, is_self))
    {
        return;
    }

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indices[i] - 1] = Tetrimino_empty;
    }

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indices[i]] = game->currentTetrimino.type;
    }

    ++game->currentTetrimino.centroid;
    return;
}

static void indices_for_right(Tetrimino *current, int indices[])
{
    switch (current->type)
    {
        case Tetrimino_empty:
            return;

        case Tetrimino_lightBlue:
            indices[0] = current->centroid + 1;
            indices[1] = current->centroid;
            indices[2] = current->centroid + 2;
            indices[3] = current->centroid + 3;
            return;

        case Tetrimino_darkBlue:
            indices[0] = current->centroid + 1;
            indices[1] = current->centroid;
            indices[2] = current->centroid - PLAYFIELD_COLUMNS;
            indices[3] = current->centroid + 2;
            return;

        case Tetrimino_orange:
            indices[0] = current->centroid + 1;
            indices[1] = current->centroid;
            indices[2] = current->centroid + 2;
            indices[3] = current->centroid - PLAYFIELD_COLUMNS + 2;
            return;

        case Tetrimino_yellow:
            indices[0] = current->centroid + 1;
            indices[1] = current->centroid - PLAYFIELD_COLUMNS + 1;
            indices[2] = current->centroid + 2;
            indices[3] = current->centroid - PLAYFIELD_COLUMNS + 2;
            return;

        case Tetrimino_green:
            indices[0] = current->centroid + 1;
            indices[1] = current->centroid;
            indices[2] = current->centroid - PLAYFIELD_COLUMNS + 1;
            indices[3] = current->centroid - PLAYFIELD_COLUMNS + 2;
            return;

        case Tetrimino_red:
            indices[0] = current->centroid + 1;
            indices[1] = current->centroid - PLAYFIELD_COLUMNS + 1;
            indices[2] = current->centroid - PLAYFIELD_COLUMNS;
            indices[3] = current->centroid + 2;
            return;

        case Tetrimino_magenta:
            indices[0] = current->centroid + 1;
            indices[1] = current->centroid;
            indices[2] = current->centroid - PLAYFIELD_COLUMNS + 1;
            indices[3] = current->centroid + 2;
            return;
    }
}

static bool is_self(int indices[], int current)
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (indices[i] - 1 == current)
        {
            return true;
        }
    }

    return false;
}

