#include "validation.h"

#include "../game/gamesettings.h"

#include <stdbool.h>

bool valid_move(TetriminoColor playfield[],
                int indices[],
                bool (*is_self)(int[], int))
{
    int current = 0;

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        current = indices[i];

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
            if (!is_self(indices, current))
            {
                return false;
            }
        }
    }

    return true;
}

