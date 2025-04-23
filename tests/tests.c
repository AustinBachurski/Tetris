#include "unity/unity.h"

#include "playfield/gameover.h"
#include "tetrimino/movedown.h"
#include "tetrimino/moveleft.h"
#include "randombag/randombag.h"
#include "playfield/spawntetrimino.h"

void setUp(void)
{ }

void tearDown(void)
{ }

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(random_bag_produces_complete_set);

    RUN_TEST(spawn_light_blue_tetrimino);
    RUN_TEST(spawn_dark_blue_tetrimino);
    RUN_TEST(spawn_orange_tetrimino);
    RUN_TEST(spawn_yellow_tetrimino);
    RUN_TEST(spawn_green_tetrimino);
    RUN_TEST(spawn_red_tetrimino);
    RUN_TEST(spawn_magenta_tetrimino);

    RUN_TEST(move_light_blue_tetrimino_down);
    RUN_TEST(move_dark_blue_tetrimino_down);
    RUN_TEST(move_orange_tetrimino_down);
    RUN_TEST(move_yellow_tetrimino_down);
    RUN_TEST(move_green_tetrimino_down);
    RUN_TEST(move_red_tetrimino_down);
    RUN_TEST(move_magenta_tetrimino_down);

    RUN_TEST(move_light_blue_tetrimino_left);

    RUN_TEST(game_over);

    return UNITY_END();
}

