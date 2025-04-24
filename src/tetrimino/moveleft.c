#include "moveleft.h"

#include "tetrimino.h"
#include "validation.h"
#include "../game/game.h"
#include "../game/gamesettings.h"

static void indices_for_left(Tetrimino *current, int indices[]);
static bool is_self(int indices[], int current);

void move_tetrimino_left(GameData *game)
{
    int indices[SQUARES_PER_TETRIMINO];
    indices_for_left(&game->currentTetrimino, indices);

    if (!valid_move(game->playfield, indices, is_self))
    {
        return;
    }

    // Clear old spaces.
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indices[i] + 1] = Tetrimino_empty;
    }

    // Assign new spaces.
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indices[i]] = game->currentTetrimino.type;
    }

    --game->currentTetrimino.centroid;
    return;
}

static void indices_for_left(Tetrimino *current, int indices[])
{
    switch (current->type)
    {
        case Tetrimino_empty:
            return;

        case Tetrimino_lightBlue:
            indices[0] = current->centroid - 1;
            indices[1] = current->centroid - 2;
            indices[2] = current->centroid;
            indices[3] = current->centroid + 1;
            return;

        case Tetrimino_darkBlue:
            indices[0] = current->centroid - 1;
            indices[1] = current->centroid - 2;
            indices[2] = current->centroid - PLAYFIELD_COLUMNS - 2;
            indices[3] = current->centroid;
            return;

        case Tetrimino_orange:
            indices[0] = current->centroid - 1;
            indices[1] = current->centroid - 2;
            indices[2] = current->centroid;
            indices[3] = current->centroid - PLAYFIELD_COLUMNS;
            return;

        case Tetrimino_yellow:
            indices[0] = current->centroid - 1;
            indices[1] = current->centroid - PLAYFIELD_COLUMNS - 1;
            indices[2] = current->centroid;
            indices[3] = current->centroid - PLAYFIELD_COLUMNS;
            return;

        case Tetrimino_green:
            indices[0] = current->centroid - 1;
            indices[1] = current->centroid - 2;
            indices[2] = current->centroid - PLAYFIELD_COLUMNS - 1;
            indices[3] = current->centroid - PLAYFIELD_COLUMNS;
            return;

        case Tetrimino_red:
            indices[0] = current->centroid - 1;
            indices[1] = current->centroid - PLAYFIELD_COLUMNS - 1;
            indices[2] = current->centroid - PLAYFIELD_COLUMNS - 2;
            indices[3] = current->centroid;
            return;

        case Tetrimino_magenta:
            indices[0] = current->centroid - 1;
            indices[1] = current->centroid - 2;
            indices[2] = current->centroid - PLAYFIELD_COLUMNS - 1;
            indices[3] = current->centroid;
            return;
    }
}

static bool is_self(int indices[], int current)
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (indices[i] + 1 == current)
        {
            return true;
        }
    }

    return false;
}

