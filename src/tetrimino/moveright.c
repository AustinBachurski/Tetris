#include "moveright.h"

#include "movement.h"
#include "../game/game.h"
#include "../game/gamesettings.h"

[[nodiscard]] static bool is_valid_move(GameData *game, MovementData *data);

void move_tetrimino_right(GameData *game)
{
    MovementData data;

    data.target = game->currentTetrimino;
    ++data.target.centroid;
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
        int const sourceIndex = data->sourceIndices[i];
        int const targetIndex = data->targetIndices[i];
        int const lowerBound = sourceIndex / 10 * 10;
        int const upperBound = lowerBound + 9;

        if (targetIndex < lowerBound || targetIndex > upperBound)
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

    return true;
}

