#include "unity/unity.h"

//#include "playfield/gameover.h"
//#include "tetrimino/gravity.h"
//#include "tetrimino/moveleft.h"
//#include "tetrimino/moveright.h"
#include "randombag/randombag.h"
#include "placement/placement.h"
#include "rotation/rotation.h"

void setUp(void)
{ }

void tearDown(void)
{ }

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(random_bag_produces_complete_set);

    RUN_TEST(place_light_blue_tetrimino);
    RUN_TEST(place_dark_blue_tetrimino);
    RUN_TEST(place_orange_tetrimino);
    RUN_TEST(place_yellow_tetrimino);
    RUN_TEST(place_green_tetrimino);
    RUN_TEST(place_red_tetrimino);
    RUN_TEST(place_magenta_tetrimino);

    RUN_TEST(rotate_light_blue_tetrimino);
    RUN_TEST(rotate_dark_blue_tetrimino);
    RUN_TEST(rotate_orange_tetrimino);
    RUN_TEST(rotate_yellow_tetrimino);
    RUN_TEST(rotate_green_tetrimino);
    RUN_TEST(rotate_red_tetrimino);
    RUN_TEST(rotate_magenta_tetrimino);

    // RUN_TEST(light_blue_tetrimino_gravity_down);
    // RUN_TEST(dark_blue_tetrimino_gravity_down);
    // RUN_TEST(orange_tetrimino_gravity_down);
    // RUN_TEST(yellow_tetrimino_gravity_down);
    // RUN_TEST(green_tetrimino_gravity_down);
    // RUN_TEST(red_tetrimino_gravity_down);
    // RUN_TEST(magenta_tetrimino_gravity_down);
// 
    // RUN_TEST(move_light_blue_tetrimino_left);
    // RUN_TEST(move_light_blue_tetrimino_right);
// 
    // RUN_TEST(game_over);
// 
    return UNITY_END();
}

