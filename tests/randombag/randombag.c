#include "randombag.h"

#include "../game/gamesettings.h"
#include "../../src/game/game.h"
#include "../../src/game/gamesettings.h"
#include "../../src/tetriminos/tetrimino.h"

#include "unity.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void confirm_bag_was_emptied(bool resultsBag[])
{
    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        TEST_ASSERT(true == resultsBag[i]);
    }
}

void empty_test_bag(TetriminoColor testBag[], bool resultsBag[])
{
    Tetrimino result;

    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        result = make_random_tetrimino(testBag);
        int index = ((int)result.type) - 1;

        TEST_ASSERT(false == resultsBag[index]);

        resultsBag[index] = true;
    }
}

void prep_results_bag_for_testing(bool resultsBag[])
{
    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        resultsBag[i] = false;
    }
}

void random_bag_produces_complete_set(void)
{
    TetriminoColor testBag[TETRIMINO_COUNT];
    bool resultsBag[TETRIMINO_COUNT];

    srand((unsigned int)time(NULL));
    reset_bag(testBag);

    for (int i = 0; i < 100; ++i)
    {
        prep_results_bag_for_testing(resultsBag);
        empty_test_bag(testBag, resultsBag);
        confirm_bag_was_emptied(resultsBag);
    }
}

