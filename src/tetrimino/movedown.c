#include "movedown.h"

#include "movement.h"
#include "../game/game.h"
#include "../game/gamesettings.h"

#include <sys/time.h>

[[nodiscard]] static bool is_valid_move(GameData *game, MovementData *data);

bool gravity_down(GameData *game)
{
    MovementData data;
    data.target = game->currentTetrimino;
    data.target.centroid -= PLAYFIELD_COLUMNS;

    indices_for(&game->currentTetrimino, data.sourceIndices);
    indices_for(&data.target, data.targetIndices);

    if (is_valid_move(game, &data))
    {
        apply_changes(game, &data);
        return true;
    }

    return false;
}

void move_tetrimino_down(GameData *game)
{
    MovementData data;
    data.target = game->currentTetrimino;
    data.target.centroid -= PLAYFIELD_COLUMNS;

    indices_for(&game->currentTetrimino, data.sourceIndices);
    indices_for(&data.target, data.targetIndices);

    if (is_valid_move(game, &data))
    {
        apply_changes(game, &data);
        gettimeofday(&game->dropTime, NULL);
    }
}

static bool is_valid_move(GameData *game, MovementData *data)
{
    for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
    {
        int const targetIndex = data->targetIndices[i];

        if (0 > targetIndex)
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

