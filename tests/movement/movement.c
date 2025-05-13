#include "movement.h"

#include "../../src/game/gamesettings.h"
#include "../../src/tetrimino/tetrimino.h"
#include "../../src/tetrimino/movement.h"

#include "../unity/unity.h"

#define SPAWN_ROW_LIGHTBLUE 1
#define SPAWN_ROW_OTHERS 2

extern void clear_playfield(GameData *game);
extern void place_tetrimino(GameData *game);
[[nodiscard]] extern int spawnpoint_for(TetriminoColor const color);

static char const *inBoundsFail = "Gravity returned false prematurely.";
static char const *outOfBounds = "Gravity out of bounds..";

void gravity_for_light_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_lightBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = SPAWN_ROW_LIGHTBLUE; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(gravity_down(&game), inBoundsFail);
    }

    TEST_ASSERT_MESSAGE(!gravity_down(&game), outOfBounds);
}

void gravity_for_dark_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_darkBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(gravity_down(&game), inBoundsFail);
    }

    TEST_ASSERT_MESSAGE(!gravity_down(&game), outOfBounds);
}

void gravity_for_orange_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_orange;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(gravity_down(&game), inBoundsFail);
    }

    TEST_ASSERT_MESSAGE(!gravity_down(&game), outOfBounds);
}

void gravity_for_yellow_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_yellow;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(gravity_down(&game), inBoundsFail);
    }

    TEST_ASSERT_MESSAGE(!gravity_down(&game), outOfBounds);
}

void gravity_for_green_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_green;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(gravity_down(&game), inBoundsFail);
    }

    TEST_ASSERT_MESSAGE(!gravity_down(&game), outOfBounds);
}

void gravity_for_red_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_red;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(gravity_down(&game), inBoundsFail);
    }

    TEST_ASSERT_MESSAGE(!gravity_down(&game), outOfBounds);
}

void gravity_for_magenta_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_magenta;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(gravity_down(&game), inBoundsFail);
    }

    TEST_ASSERT_MESSAGE(!gravity_down(&game), outOfBounds);
}

