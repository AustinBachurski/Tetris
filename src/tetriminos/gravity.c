#include "tetrimino.h"

#include "gravity.h"
#include "../game/gamesettings.h"

void indicies_for_down(Tetrimino *current, int indicies[])
{
    switch (current->type)
    {
        case Tetrimino_empty:
            // TODO: Probably a better way to do this...
            return;

        case Tetrimino_lightBlue:
            indicies[0] = current->centroid + PLAYFIELD_COLUMNS;
            indicies[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indicies[2] = current->centroid + PLAYFIELD_COLUMNS + 1;
            indicies[3] = current->centroid + PLAYFIELD_COLUMNS + 2;
            return;

        case Tetrimino_darkBlue:
            indicies[0] = current->centroid + PLAYFIELD_COLUMNS;
            indicies[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indicies[2] = current->centroid - 1;
            indicies[3] = current->centroid + PLAYFIELD_COLUMNS + 1;
            return;

        case Tetrimino_orange:
            indicies[0] = current->centroid + PLAYFIELD_COLUMNS;
            indicies[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indicies[2] = current->centroid + PLAYFIELD_COLUMNS + 1;
            indicies[3] = current->centroid + 1;
            return;

        case Tetrimino_yellow:
            indicies[0] = current->centroid + PLAYFIELD_COLUMNS;
            indicies[1] = current->centroid;
            indicies[2] = current->centroid + PLAYFIELD_COLUMNS + 1;
            indicies[3] = current->centroid + 1;
            return;

        case Tetrimino_green:
            indicies[0] = current->centroid + PLAYFIELD_COLUMNS;
            indicies[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indicies[2] = current->centroid;
            indicies[3] = current->centroid + 1;
            return;

        case Tetrimino_red:
            indicies[0] = current->centroid + PLAYFIELD_COLUMNS;
            indicies[1] = current->centroid;
            indicies[2] = current->centroid - 1;
            indicies[3] = current->centroid + PLAYFIELD_COLUMNS + 1;
            return;

        case Tetrimino_magenta:
            indicies[0] = current->centroid + PLAYFIELD_COLUMNS;
            indicies[1] = current->centroid + PLAYFIELD_COLUMNS - 1;
            indicies[2] = current->centroid;
            indicies[3] = current->centroid + PLAYFIELD_COLUMNS + 1;
            return;
    }
}

bool is_self(int indicies[], int current)
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (indicies[i] - PLAYFIELD_COLUMNS == current)
        {
            return true;
        }
    }

    return false;
}

bool move_down(GameData *game)
{
    int indicies[SQUARES_PER_TETRIMINO];
    indicies_for_down(&game->currentTetrimino, indicies);

    if (!valid_move(game->playfield, indicies))
    {
        return false;
    }

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indicies[i] - PLAYFIELD_COLUMNS] = Tetrimino_empty;
    }

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        game->playfield[indicies[i]] = game->currentTetrimino.type;
    }

    game->currentTetrimino.centroid += PLAYFIELD_COLUMNS;
    return true;
}

bool valid_move(TetriminoColor playfield[], int indicies[])
{
    int current = 0;

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        current = indicies[i];

        if ( 0 > current)
        {
            return false;
        }

        if (PLAYFIELD_SIZE <= current)
        {
            return false;
        }

        if (Tetrimino_empty != playfield[current])
        {
            if (!is_self(indicies, current))
            {
                return false;
            }
        }
    }

    return true;
}

