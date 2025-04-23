#include "movedown.h"

#include "../../src/game/game.h"

#include "../utilities/utilities.h"

#include "gamesettings.h"
#include "unity.h"

// Light blue takes up one row and spawns in row zero.
#define SINGLE_ROW_TETRIMINO_PLAYFIELD_SIZE (PLAYFIELD_ROWS - 1)

// The rest take up two rows, so the bottom is in the second row.
#define DOUBLE_ROW_TETRIMINO_PLAYFIELD_SIZE (PLAYFIELD_ROWS - 2)

extern void clear_playfield(GameData *game);
extern void spawn_tetrimino(GameData *game);
[[nodiscard]] extern bool move_down(GameData *game);

static int lightBlueMovedIndices[SQUARES_PER_TETRIMINO] = { 13, 14, 15, 16, };
static int darkBlueMovedIndices[SQUARES_PER_TETRIMINO] = { 13, 23, 24, 25, };
static int orangeMovedIndices[SQUARES_PER_TETRIMINO] = { 15, 23, 24, 25, };
static int yellowMovedIndices[SQUARES_PER_TETRIMINO] = { 14, 15, 24, 25 };
static int greenMovedIndices[SQUARES_PER_TETRIMINO] = { 14, 15, 23, 24 };
static int redMovedIndices[SQUARES_PER_TETRIMINO] = { 13, 14, 24, 25 };
static int magentaMovedIndices[SQUARES_PER_TETRIMINO] = { 14, 23, 24, 25 };

static char const *openSucceed = "Space is open, move should succeed.";
static char const *incorrectLocation = "Tetrimino was not in correct location.";
static char const *hitBottom = "Bottom of playfield, move should fail.";
static char const *newDrop = "New drop, move should succeed.";
static char const *occupiedSpace = "Space is now occupied, move_down should fail.";

void move_light_blue_tetrimino_down(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_lightBlue, Facing_up };
    spawn_tetrimino(&game);

    for (int i = 0; i < SINGLE_ROW_TETRIMINO_PLAYFIELD_SIZE; ++i)
    {
        TEST_ASSERT_MESSAGE(move_down(&game), openSucceed);

        TEST_ASSERT_MESSAGE(
            correct_spaces_occupied(&game, lightBlueMovedIndices),
            incorrectLocation);

        move_indices_down(lightBlueMovedIndices);
    }

    TEST_ASSERT_MESSAGE(!move_down(&game), hitBottom);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(move_down(&game), newDrop);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(!move_down(&game), occupiedSpace);
}

void move_dark_blue_tetrimino_down(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_darkBlue, Facing_up };
    spawn_tetrimino(&game);

    for (int i = 0; i < DOUBLE_ROW_TETRIMINO_PLAYFIELD_SIZE; ++i)
    {
        TEST_ASSERT_MESSAGE(move_down(&game), openSucceed);

        TEST_ASSERT_MESSAGE(
            correct_spaces_occupied(&game, darkBlueMovedIndices),
            incorrectLocation);

        move_indices_down(darkBlueMovedIndices);
    }

    TEST_ASSERT_MESSAGE(!move_down(&game), hitBottom);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(move_down(&game), newDrop);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(!move_down(&game), occupiedSpace);
}

void move_orange_tetrimino_down(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_orange, Facing_up };
    spawn_tetrimino(&game);

    for (int i = 0; i < DOUBLE_ROW_TETRIMINO_PLAYFIELD_SIZE; ++i)
    {
        TEST_ASSERT_MESSAGE(move_down(&game), openSucceed);

        TEST_ASSERT_MESSAGE(
            correct_spaces_occupied(&game, orangeMovedIndices),
            incorrectLocation);

        move_indices_down(orangeMovedIndices);
    }

    TEST_ASSERT_MESSAGE(!move_down(&game), hitBottom);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(move_down(&game), newDrop);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(!move_down(&game), occupiedSpace);
}

void move_yellow_tetrimino_down(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_yellow, Facing_up };
    spawn_tetrimino(&game);

    for (int i = 0; i < DOUBLE_ROW_TETRIMINO_PLAYFIELD_SIZE; ++i)
    {
        TEST_ASSERT_MESSAGE(move_down(&game), openSucceed);

        TEST_ASSERT_MESSAGE(
            correct_spaces_occupied(&game, yellowMovedIndices),
            incorrectLocation);

        move_indices_down(yellowMovedIndices);
    }

    TEST_ASSERT_MESSAGE(!move_down(&game), hitBottom);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(move_down(&game), newDrop);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(!move_down(&game), occupiedSpace);
}

void move_green_tetrimino_down(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_green, Facing_up };
    spawn_tetrimino(&game);

    for (int i = 0; i < DOUBLE_ROW_TETRIMINO_PLAYFIELD_SIZE; ++i)
    {
        TEST_ASSERT_MESSAGE(move_down(&game), openSucceed);

        TEST_ASSERT_MESSAGE(
            correct_spaces_occupied(&game, greenMovedIndices),
            incorrectLocation);

        move_indices_down(greenMovedIndices);
    }

    TEST_ASSERT_MESSAGE(!move_down(&game), hitBottom);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(move_down(&game), newDrop);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(!move_down(&game), occupiedSpace);
}

void move_red_tetrimino_down(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_red, Facing_up };
    spawn_tetrimino(&game);

    for (int i = 0; i < DOUBLE_ROW_TETRIMINO_PLAYFIELD_SIZE; ++i)
    {
        TEST_ASSERT_MESSAGE(move_down(&game), openSucceed);

        TEST_ASSERT_MESSAGE(
            correct_spaces_occupied(&game, redMovedIndices),
            incorrectLocation);

        move_indices_down(redMovedIndices);
    }

    TEST_ASSERT_MESSAGE(!move_down(&game), hitBottom);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(move_down(&game), newDrop);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(!move_down(&game), occupiedSpace);
}

void move_magenta_tetrimino_down(void)
{
    GameData game;
    clear_playfield(&game);
    game.currentTetrimino = (Tetrimino){ 0, Tetrimino_magenta, Facing_up };
    spawn_tetrimino(&game);

    for (int i = 0; i < DOUBLE_ROW_TETRIMINO_PLAYFIELD_SIZE; ++i)
    {
        TEST_ASSERT_MESSAGE(move_down(&game), openSucceed);

        TEST_ASSERT_MESSAGE(
            correct_spaces_occupied(&game, magentaMovedIndices),
            incorrectLocation);

        move_indices_down(magentaMovedIndices);
    }

    TEST_ASSERT_MESSAGE(!move_down(&game), hitBottom);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(move_down(&game), newDrop);

    spawn_tetrimino(&game);
    TEST_ASSERT_MESSAGE(!move_down(&game), occupiedSpace);
}

