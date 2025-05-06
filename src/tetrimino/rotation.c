#include "rotation.h"

#include "movement.h"
#include "../game/game.h"
#include "../game/gamesettings.h"

#include <stdlib.h>

#define MAXIMUM_SPAN 2

[[nodiscard]] static bool is_valid_move(GameData *game, MovementData *data);
static void set_rotation_value(Tetrimino *tetrimino);
[[nodiscard]] static bool through_the_wall(MovementData const *data);

void rotate_tetrimino(GameData *game)
{
    MovementData data;
    data.target = game->currentTetrimino;
    set_rotation_value(&data.target);

    indices_for(&game->currentTetrimino, data.sourceIndices);
    indices_for(&data.target, data.targetIndices);

    if (is_valid_move(game, &data))
    {
        apply_changes(game, &data);
    }
}

static bool is_valid_move(GameData *game, MovementData *data)
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        int const targetIndex = data->targetIndices[i];

        if (PLAYFIELD_SIZE <= targetIndex || 0 >= targetIndex)
        {
            return false;
        }

        if (Tetrimino_empty != game->playfield[targetIndex])
        {
            if (!is_self(targetIndex, data->sourceIndices))
            {
                return false;
            }
        }
    }

    return !through_the_wall(data);
}

static void set_rotation_value(Tetrimino *tetrimino)
{
    switch (tetrimino->orientation)
    {
        case North:
            tetrimino->orientation = East;
            return;

        case East:
            tetrimino->orientation = South;
            return;

        case South:
            tetrimino->orientation = West;
            return;

        case West:
            tetrimino->orientation = North;
            return;
    }
}

static bool through_the_wall(MovementData const *data)
{
    int const normalizedCentroid = data->target.centroid % PLAYFIELD_COLUMNS;

    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        int collapsedIndex = data->targetIndices[i] % PLAYFIELD_COLUMNS;

        if (abs(normalizedCentroid - collapsedIndex) > MAXIMUM_SPAN)
        {
            return true;
        }
    }

    return false;
}

