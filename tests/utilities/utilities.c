#include "utilities.h"
#include "gamesettings.h"

[[nodiscard]]
static bool should_be_occupied(int const index, int const indices[]);

[[nodiscard]]
bool correct_spaces_occupied(GameData* game, int const indices[])
{
    for (int i = 0; i < PLAYFIELD_SIZE; ++i)
    {
        if (game->playfield[i] && !should_be_occupied(i, indices))
        {
            return false;
        }
    }
    return true;
}

[[nodiscard]]
bool playfield_is_empty(GameData* game)
{
    for (int i = 0; i < PLAYFIELD_SIZE; ++i)
    {
        if (game->playfield[i])
        {
            return false;
        }
    }
    return true;
}

static bool should_be_occupied(int const index, int const indices[])
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        if (index == indices[i])
        {
            return true;
        }
    }

    return false;
}

