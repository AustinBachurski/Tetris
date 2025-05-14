#include "movement.h"

#include "../../src/tetrimino/tetrimino.h"
#include "../../src/tetrimino/moveright.h"

#include "../unity/unity.h"

#define COLUMNS_TO_MOVE_LIGHTBLUE 3
#define COLUMNS_TO_MOVE_OTHERS 4

extern void clear_playfield(GameData *game);
extern void place_tetrimino(GameData *game);
[[nodiscard]] extern int spawnpoint_for(TetriminoColor const color);

static char const *moveFailed = "Tetrimino did not move when it should've.";
static char const *movedInError = "Tetrimino moved when it shouldn't have.";

void moveright_for_light_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_lightBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = 0; i < COLUMNS_TO_MOVE_LIGHTBLUE; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_right(&game);

        TEST_ASSERT_MESSAGE(
            (++location) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_right(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);
}

void moveright_for_dark_blue_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_darkBlue;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = 0; i < COLUMNS_TO_MOVE_OTHERS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_right(&game);

        TEST_ASSERT_MESSAGE(
            (++location) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_right(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);
}

void moveright_for_orange_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_orange;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = 0; i < COLUMNS_TO_MOVE_OTHERS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_right(&game);

        TEST_ASSERT_MESSAGE(
            (++location) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_right(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);
}

void moveright_for_yellow_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_yellow;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = 0; i < COLUMNS_TO_MOVE_OTHERS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_right(&game);

        TEST_ASSERT_MESSAGE(
            (++location) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_right(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);
}

void moveright_for_green_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_green;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = 0; i < COLUMNS_TO_MOVE_OTHERS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_right(&game);

        TEST_ASSERT_MESSAGE(
            (++location) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_right(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);
}

void moveright_for_red_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_red;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = 0; i < COLUMNS_TO_MOVE_OTHERS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_right(&game);

        TEST_ASSERT_MESSAGE(
            (++location) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_right(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);
}

void moveright_for_magenta_tetrimino(void)
{
    GameData game;
    clear_playfield(&game);
    TetriminoColor const color = Tetrimino_magenta;
    game.currentTetrimino = (Tetrimino){ spawnpoint_for(color), color, North };

    place_tetrimino(&game);

    int location = game.currentTetrimino.centroid;

    for (int i = 0; i < COLUMNS_TO_MOVE_OTHERS; ++i)
    {
        TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                            movedInError);

        move_tetrimino_right(&game);

        TEST_ASSERT_MESSAGE(
            (++location) == game.currentTetrimino.centroid,
            moveFailed);
    }

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);

    move_tetrimino_right(&game);

    TEST_ASSERT_MESSAGE(location == game.currentTetrimino.centroid,
                        movedInError);
}

