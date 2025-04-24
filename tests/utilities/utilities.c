#include "utilities.h"

[[nodiscard]] bool correct_spaces_occupied(GameData* game, int const indices[])
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (Tetrimino_empty == game->playfield[indices[i]])
        {
            return false;
        }
    }
    return true;
}

void shift_indices_down(int indices[])
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        indices[i] += 10;
    }
}
