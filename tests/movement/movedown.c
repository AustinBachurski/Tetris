#include "movement.h"

#include "../../src/game/gamesettings.h"
#include "../../src/tetrimino/tetrimino.h"
#include "../../src/tetrimino/movedown.h"

#include "../unity/unity.h"

#define SPAWN_ROW_LIGHTBLUE 1
#define SPAWN_ROW_OTHERS 2

extern void clear_playfield(GameData *game);
extern void place_tetrimino(GameData *game);
[[nodiscard]] extern int spawnpoint_for(TetriminoColor const color);

static char const *moveFailed = "Tetrimino did not move when it should've.";
static char const *movedInError = "Tetrimino moved when it shouldn't have.";

void movedown_for_light_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_lightBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = SPAWN_ROW_LIGHTBLUE; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_down(&game);

        TEST_ASSERT_MESSAGE(
            (location -= PLAYFIELD_COLUMNS) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_down(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid, moveFailed);
}

void movedown_for_dark_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_darkBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_down(&game);

        TEST_ASSERT_MESSAGE(
            (location -= PLAYFIELD_COLUMNS) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_down(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid, moveFailed);
}

void movedown_for_orange_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_orange;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_down(&game);

        TEST_ASSERT_MESSAGE(
            (location -= PLAYFIELD_COLUMNS) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_down(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid, moveFailed);
}

void movedown_for_yellow_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_yellow;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_down(&game);

        TEST_ASSERT_MESSAGE(
            (location -= PLAYFIELD_COLUMNS) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_down(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid, moveFailed);
}

void movedown_for_green_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_green;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_down(&game);

        TEST_ASSERT_MESSAGE(
            (location -= PLAYFIELD_COLUMNS) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_down(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid, moveFailed);
}

void movedown_for_red_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_red;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_down(&game);

        TEST_ASSERT_MESSAGE(
            (location -= PLAYFIELD_COLUMNS) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_down(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid, moveFailed);
}

void movedown_for_magenta_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_magenta;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = SPAWN_ROW_OTHERS; i < PLAYFIELD_WINDOW_ROWS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_down(&game);

        TEST_ASSERT_MESSAGE(
            (location -= PLAYFIELD_COLUMNS) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_down(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid, moveFailed);
}

