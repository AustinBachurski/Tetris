#include "unity/unity.h"

#include "randombag/randombag.h"
#include "playfield/spawntetrimino.h"
#include "playfield/gameover.h"

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

    // TODO: RUN_TEST(move_tetrimino_down);
    // TODO: RUN_TEST(move_is_valid);

    RUN_TEST(game_over);

    return UNITY_END();
}

