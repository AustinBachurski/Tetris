#include "utilities.h"

#include "../../src/game/gamesettings.h"

#define PLAYFIELD_MIDPOINT 4

[[nodiscard]] static bool should_be_occupied(int const index,
                                             int const indices[]);
[[nodiscard]] static bool no_wrap_left(GameData* game);
[[nodiscard]] static bool no_wrap_right(GameData* game);

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

[[nodiscard]]
bool tetrimino_has_not_wrapped(GameData* game)
{
    if (game->currentTetrimino.centroid % PLAYFIELD_COLUMNS < PLAYFIELD_MIDPOINT)
    {
        return no_wrap_right(game);
    }
    else
    {
        return no_wrap_left(game);
    }
}

static bool no_wrap_left(GameData* game)
{
    int midpoint = 0;

    for (int row = 0; row < PLAYFIELD_ROWS; ++row)
    {
        midpoint = row * PLAYFIELD_COLUMNS + PLAYFIELD_MIDPOINT;

        for (int i = row * PLAYFIELD_COLUMNS; i < midpoint; ++i)
        {
            if (game->playfield[i])
            {
                return false;
            }
        }
    }

    return true;
}

static bool no_wrap_right(GameData* game)
{
    int midpoint = 0;
    int rowEnd = 0;

    for (int row = 0; row < PLAYFIELD_ROWS; ++row)
    {
        midpoint = row * PLAYFIELD_COLUMNS + PLAYFIELD_MIDPOINT + 1;
        rowEnd = row * PLAYFIELD_COLUMNS + PLAYFIELD_COLUMNS;

        for (int i = midpoint; i < rowEnd; ++i)
        {
            if (game->playfield[i])
            {
                return false;
            }
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

