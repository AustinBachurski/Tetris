#include "gameover.h"

#include "../../src/game/game.h"
#include "../../src/game/gamesettings.h"
#include "../../src/tetrimino/tetrimino.h"

#include "unity.h"

extern void clear_playfield(GameData *game);
[[nodiscard]] extern bool is_game_over(GameData *game);

static int index_of(int const index, TetriminoColor const next);

void game_over(void)
{
    GameData game;

    for (int tetrimino = 0; tetrimino < TETRIMINO_COUNT; ++tetrimino)
    {
        game.nextTetrimino =
         (Tetrimino){ 0, (TetriminoColor)(tetrimino + 1), Facing_up };

        for (int i = 0; i < SQUARES_PER_TETRIMINO; ++i)
        {
            clear_playfield(&game);
            TEST_ASSERT_MESSAGE(!is_game_over(&game),
                                "Game over triggered with empty board.");

            game.playfield[index_of(i, game.nextTetrimino.type)]
                = (TetriminoColor)(tetrimino + 1);

            TEST_ASSERT_MESSAGE(is_game_over(&game),
                                "Game over didn't trigger when it should've.");
        }
    }
}

static int index_of(int const index, TetriminoColor const next)
{
    switch (next)
    {
        case Tetrimino_empty:
            TEST_ASSERT_MESSAGE(false, "Received an invalid enum value.");
            return 1;

        case Tetrimino_lightBlue:
            return lightBlueSpawnIndices[index];

        case Tetrimino_darkBlue:
            return darkBlueSpawnIndices[index];

        case Tetrimino_orange:
            return orangeSpawnIndices[index];

        case Tetrimino_yellow:
            return yellowSpawnIndices[index];

        case Tetrimino_green:
            return greenSpawnIndices[index];

        case Tetrimino_red:
            return redSpawnIndices[index];

        case Tetrimino_magenta:
            return magentaSpawnIndices[index];
    }
    TEST_ASSERT_MESSAGE(false, "Received an invalid enum value.");
    return 1;
}

