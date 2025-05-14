#include "rotation.h"

#include "../../src/tetrimino/tetrimino.h"
#include "../../src/tetrimino/moveleft.h"
#include "../../src/tetrimino/moveright.h"
#include "../../src/tetrimino/rotation.h"

#include "../utilities/utilities.h"

#include "../unity/unity.h"

#define ALL_THE_WAY 10

extern void clear_playfield(GameData *game);
extern void place_tetrimino(GameData *game);
[[nodiscard]] extern int spawnpoint_for(TetriminoColor const color);

static char const *wrappedLeft = "Wrap occurred moving left.";
static char const *wrappedRight = "Wrap occurred moving right.";

void nowrap_for_light_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_lightBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);
    rotate_tetrimino(&game);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_left(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedLeft);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_right(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedRight);
}

void nowrap_for_dark_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_darkBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);
    rotate_tetrimino(&game);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_left(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedLeft);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_right(&game);
    }

    // Move piece to correct orientation for potential wrapping error.
    rotate_tetrimino(&game);
    rotate_tetrimino(&game);
    move_tetrimino_right(&game);

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedRight);
}

void nowrap_for_orange_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_orange;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);
    rotate_tetrimino(&game);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_left(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedLeft);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_right(&game);
    }

    // Move piece to correct orientation for potential wrapping error.
    rotate_tetrimino(&game);
    rotate_tetrimino(&game);
    move_tetrimino_right(&game);

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedRight);
}

void nowrap_for_yellow_tetrimino(void)
{
    // Really not possible since rotation does nothing,
    // but we'll test it anyways.

    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_yellow;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);
    rotate_tetrimino(&game);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_left(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedLeft);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_right(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedRight);
}

void nowrap_for_green_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_green;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);
    rotate_tetrimino(&game);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_left(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedLeft);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_right(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedRight);
}

void nowrap_for_red_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_red;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);
    rotate_tetrimino(&game);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_left(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedLeft);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_right(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedRight);
}

void nowrap_for_magenta_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_magenta;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);
    rotate_tetrimino(&game);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_left(&game);
    }

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedLeft);

    for (int i = 0; i < ALL_THE_WAY; ++i)
    {
        move_tetrimino_right(&game);
    }

    // Move piece to correct orientation for potential wrapping error.
    rotate_tetrimino(&game);
    rotate_tetrimino(&game);
    move_tetrimino_right(&game);

    rotate_tetrimino(&game);
    TEST_ASSERT_MESSAGE(tetrimino_has_not_wrapped(&game), wrappedRight);
}

