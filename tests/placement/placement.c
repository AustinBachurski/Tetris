#include "placement.h"

#include "../../src/game/gamesettings.h"
#include "../../src/tetrimino/tetrimino.h"

#include "../utilities/utilities.h"

#include "../unity/unity.h"

extern void clear_playfield(GameData *game);
extern void place_tetrimino(GameData *game);
[[nodiscard]] extern int spawnpoint_for(TetriminoColor const color);

static int const lightBlueSpawnIndices[SQUARES_PER_TETRIMINO] = { 193, 194, 195, 196 };
static int const darkBlueSpawnIndices[SQUARES_PER_TETRIMINO] = { 183, 184, 185, 193 };
static int const orangeSpawnIndices[SQUARES_PER_TETRIMINO] = { 183, 184, 185, 195 };
static int const yellowSpawnIndices[SQUARES_PER_TETRIMINO] = { 194, 195, 184, 185 };
static int const greenSpawnIndices[SQUARES_PER_TETRIMINO] = { 194, 195, 183, 184 };
static int const redSpawnIndices[SQUARES_PER_TETRIMINO] = { 193, 194, 184, 185 };
static int const magentaSpawnIndices[SQUARES_PER_TETRIMINO] = { 183, 184, 185, 194 };

void place_light_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_lightBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    TEST_ASSERT_MESSAGE(playfield_is_empty(&game),
                        "Map spaces for light blue not empty prior to placement.");

    place_tetrimino(&game);

    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, lightBlueSpawnIndices),
                        "Map spaces for light blue incorrect after placement.");
}

void place_dark_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_darkBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    TEST_ASSERT_MESSAGE(playfield_is_empty(&game),
                        "Map spaces for dark blue not empty prior to placement.");

    place_tetrimino(&game);

    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, darkBlueSpawnIndices),
                        "Map spaces for dark blue incorrect after placement.");
}

void place_orange_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_orange;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    TEST_ASSERT_MESSAGE(playfield_is_empty(&game),
                        "Map spaces for orange not empty prior to placement.");

    place_tetrimino(&game);

    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, orangeSpawnIndices),
                        "Map spaces for orange incorrect after placement.");
}

void place_yellow_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_yellow;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    TEST_ASSERT_MESSAGE(playfield_is_empty(&game),
                        "Map spaces for yellow not empty prior to placement.");

    place_tetrimino(&game);

    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, yellowSpawnIndices),
                        "Map spaces for yellow incorrect after placement.");
}

void place_green_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_green;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    TEST_ASSERT_MESSAGE(playfield_is_empty(&game),
                        "Map spaces for green not empty prior to placement.");

    place_tetrimino(&game);

    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, greenSpawnIndices),
                        "Map spaces for green incorrect after placement.");
}

void place_red_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_red;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    TEST_ASSERT_MESSAGE(playfield_is_empty(&game),
                        "Map spaces for red not empty prior to placement.");

    place_tetrimino(&game);

    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, redSpawnIndices),
                        "Map spaces for red incorrect after placement.");
}

void place_magenta_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_magenta;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    TEST_ASSERT_MESSAGE(playfield_is_empty(&game),
                        "Map spaces for magenta not empty prior to placement.");

    place_tetrimino(&game);

    TEST_ASSERT_MESSAGE(correct_spaces_occupied(&game, magentaSpawnIndices),
                        "Map spaces for magenta incorrect after placement.");
}

