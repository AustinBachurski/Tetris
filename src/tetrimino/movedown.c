#include "movedown.h"

#include "tetrimino.h"
#include "validation.h"
#include "../game/gamesettings.h"
#include "../game/game.h"

static void indices_for_down(Tetrimino *current, int indices[]);
static bool is_self(int indices[], int current);

bool move_down(GameData *game)
{
    int indices[SQUARES_PER_TETRIMINO];
    indices_for_down(&game->currentTetrimino, indices);

    if (!valid_move(game->playfield, indices, is_self))
    {
        return false;
    }

    // Clear old spaces.
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indices[i] - PLAYFIELD_COLUMNS] = Tetrimino_empty;
    }

    // Assign new spaces.
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indices[i]] = game->currentTetrimino.type;
    }

    game->currentTetrimino.centroid += PLAYFIELD_COLUMNS;
    return true;
}

static void indices_for_down(Tetrimino *current, int indices[])
{
    switch (current->type)
    {
        case Tetrimino_empty:
            return;

        case Tetrimino_lightBlue:
            indices[0] = current->centroid + PLAYFIELD_COLUMNS;
            indices[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indices[2] = current->centroid + PLAYFIELD_COLUMNS + 1;
            indices[3] = current->centroid + PLAYFIELD_COLUMNS + 2;
            return;

        case Tetrimino_darkBlue:
            indices[0] = current->centroid + PLAYFIELD_COLUMNS;
            indices[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indices[2] = current->centroid - 1;
            indices[3] = current->centroid + PLAYFIELD_COLUMNS + 1;
            return;

        case Tetrimino_orange:
            indices[0] = current->centroid + PLAYFIELD_COLUMNS;
            indices[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indices[2] = current->centroid + PLAYFIELD_COLUMNS + 1;
            indices[3] = current->centroid + 1;
            return;

        case Tetrimino_yellow:
            indices[0] = current->centroid + PLAYFIELD_COLUMNS;
            indices[1] = current->centroid;
            indices[2] = current->centroid + PLAYFIELD_COLUMNS + 1;
            indices[3] = current->centroid + 1;
            return;

        case Tetrimino_green:
            indices[0] = current->centroid + PLAYFIELD_COLUMNS;
            indices[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indices[2] = current->centroid;
            indices[3] = current->centroid + 1;
            return;

        case Tetrimino_red:
            indices[0] = current->centroid + PLAYFIELD_COLUMNS;
            indices[1] = current->centroid;
            indices[2] = current->centroid - 1;
            indices[3] = current->centroid + PLAYFIELD_COLUMNS + 1;
            return;

        case Tetrimino_magenta:
            indices[0] = current->centroid + PLAYFIELD_COLUMNS;
            indices[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indices[2] = current->centroid;
            indices[3] = current->centroid + PLAYFIELD_COLUMNS + 1;
            return;
    }
}

static bool is_self(int indices[], int current)
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (indices[i] - PLAYFIELD_COLUMNS == current)
        {
            return true;
        }
    }

    return false;
}

