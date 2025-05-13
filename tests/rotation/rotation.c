#include "rotation.h"

#include "../../src/game/gamesettings.h"
#include "../../src/tetrimino/tetrimino.h"
#include "../../src/tetrimino/rotation.h"

#include "../utilities/utilities.h"

#include "../unity/unity.h"

#define ROTATION_STEPS 4

extern void clear_playfield(GameData *game);
extern void place_tetrimino(GameData *game);
extern void rotate_tetrimino(GameData *game);
[[nodiscard]] extern int spawnpoint_for(TetriminoColor const color);

static int const lightBlueRotationIndices[ROTATION_STEPS][SQUARES_PER_TETRIMINO] = {
    { 215, 205, 195, 185 },
    { 193, 194, 195, 196 },
    { 215, 205, 195, 185 },
    { 193, 194, 195, 196 },
};
static int const darkBlueRotationIndices[ROTATION_STEPS][SQUARES_PER_TETRIMINO] = {
    { 174, 184, 194, 195 },
    { 183, 184, 185, 175 },
    { 173, 174, 184, 194 },
    { 183, 184, 185, 193 },
};
static int const orangeRotationIndices[ROTATION_STEPS][SQUARES_PER_TETRIMINO] = {
    { 194, 184, 174, 175 },
    { 183, 184, 185, 173 },
    { 174, 184, 194, 193 },
    { 183, 184, 185, 195 },
};
static int const yellowRotationIndices[ROTATION_STEPS][SQUARES_PER_TETRIMINO] = {
    { 194, 195, 184, 185 },
    { 194, 195, 184, 185 },
    { 194, 195, 184, 185 },
    { 194, 195, 184, 185 },
};
static int const greenRotationIndices[ROTATION_STEPS][SQUARES_PER_TETRIMINO] = {
    { 194, 204, 195, 185 },
    { 194, 195, 183, 184 },
    { 194, 204, 195, 185 },
    { 194, 195, 183, 184 },
};
static int const redRotationIndices[ROTATION_STEPS][SQUARES_PER_TETRIMINO] = {
    { 194, 195, 205, 184 },
    { 193, 194, 184, 185 },
    { 194, 195, 205, 184 },
    { 193, 194, 184, 185 },
};
static int const magentaRotationIndices[ROTATION_STEPS][SQUARES_PER_TETRIMINO] = {
    { 174, 184, 185, 194 },
    { 183, 184, 185, 174 },
    { 183, 184, 194, 174 },
    { 183, 184, 185, 194 },
};

void rotate_light_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_lightBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = 0; i < ROTATION_STEPS; ++i)
    {
        rotate_tetrimino(&game);
        TEST_ASSERT(correct_spaces_occupied(&game, lightBlueRotationIndices[i]));
    }
}

void rotate_dark_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_darkBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = 0; i < ROTATION_STEPS; ++i)
    {
        rotate_tetrimino(&game);
        TEST_ASSERT(correct_spaces_occupied(&game, darkBlueRotationIndices[i]));
    }
}

void rotate_orange_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_orange;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = 0; i < ROTATION_STEPS; ++i)
    {
        rotate_tetrimino(&game);
        TEST_ASSERT(correct_spaces_occupied(&game, orangeRotationIndices[i]));
    }
}

void rotate_yellow_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_yellow;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = 0; i < ROTATION_STEPS; ++i)
    {
        rotate_tetrimino(&game);
        TEST_ASSERT(correct_spaces_occupied(&game, yellowRotationIndices[i]));
    }
}

void rotate_green_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_green;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = 0; i < ROTATION_STEPS; ++i)
    {
        rotate_tetrimino(&game);
        TEST_ASSERT(correct_spaces_occupied(&game, greenRotationIndices[i]));
    }
}

void rotate_red_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_red;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = 0; i < ROTATION_STEPS; ++i)
    {
        rotate_tetrimino(&game);
        TEST_ASSERT(correct_spaces_occupied(&game, redRotationIndices[i]));
    }
}

void rotate_magenta_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_magenta;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = 0; i < ROTATION_STEPS; ++i)
    {
        rotate_tetrimino(&game);
        TEST_ASSERT(correct_spaces_occupied(&game, magentaRotationIndices[i]));
    }
}

