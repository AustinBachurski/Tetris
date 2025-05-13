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

    place_tetrimino(&game);

    TEST_ASSERT(correct_spaces_occupied(&game, lightBlueSpawnIndices));
}

void place_dark_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_darkBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    TEST_ASSERT(correct_spaces_occupied(&game, darkBlueSpawnIndices));
}

void place_orange_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_orange;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    TEST_ASSERT(correct_spaces_occupied(&game, orangeSpawnIndices));
}

void place_yellow_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_yellow;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    TEST_ASSERT(correct_spaces_occupied(&game, yellowSpawnIndices));
}

void place_green_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_green;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    TEST_ASSERT(correct_spaces_occupied(&game, greenSpawnIndices));
}

void place_red_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_red;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    TEST_ASSERT(correct_spaces_occupied(&game, redSpawnIndices));
}

void place_magenta_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_magenta;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    TEST_ASSERT(correct_spaces_occupied(&game, magentaSpawnIndices));
}

