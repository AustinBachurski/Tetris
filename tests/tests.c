#include "unity/unity.h"

#include "placement/placement.h"
#include "randombag/randombag.h"
#include "rotation/rotation.h"
#include "movement/movement.h"

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

    RUN_TEST(gravity_for_light_blue_tetrimino);
    RUN_TEST(gravity_for_dark_blue_tetrimino);
    RUN_TEST(gravity_for_orange_tetrimino);
    RUN_TEST(gravity_for_yellow_tetrimino);
    RUN_TEST(gravity_for_green_tetrimino);
    RUN_TEST(gravity_for_red_tetrimino);
    RUN_TEST(gravity_for_magenta_tetrimino);

    RUN_TEST(movedown_for_light_blue_tetrimino);
    RUN_TEST(movedown_for_dark_blue_tetrimino);
    RUN_TEST(movedown_for_orange_tetrimino);
    RUN_TEST(movedown_for_yellow_tetrimino);
    RUN_TEST(movedown_for_green_tetrimino);
    RUN_TEST(movedown_for_red_tetrimino);
    RUN_TEST(movedown_for_magenta_tetrimino);

    RUN_TEST(moveleft_for_light_blue_tetrimino);
    RUN_TEST(moveleft_for_dark_blue_tetrimino);
    RUN_TEST(moveleft_for_orange_tetrimino);
    RUN_TEST(moveleft_for_yellow_tetrimino);
    RUN_TEST(moveleft_for_green_tetrimino);
    RUN_TEST(moveleft_for_red_tetrimino);
    RUN_TEST(moveleft_for_magenta_tetrimino);

    RUN_TEST(moveright_for_light_blue_tetrimino);
    RUN_TEST(moveright_for_dark_blue_tetrimino);
    RUN_TEST(moveright_for_orange_tetrimino);
    RUN_TEST(moveright_for_yellow_tetrimino);
    RUN_TEST(moveright_for_green_tetrimino);
    RUN_TEST(moveright_for_red_tetrimino);
    RUN_TEST(moveright_for_magenta_tetrimino);

    return UNITY_END();
}

