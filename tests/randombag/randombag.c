#include "randombag.h"

#include "../../src/game/gamesettings.h"
#include "../../src/tetriminos/tetrimino.h"

#include "unity.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

extern Tetrimino make_random_tetrimino(TetriminoColor bag[]);
extern void reset_bag(TetriminoColor bag[]);

static void confirm_bag_was_emptied(bool const resultsBag[]);
static void empty_test_bag(TetriminoColor testBag[], bool resultsBag[]);
static void prep_results_bag_for_testing(bool resultsBag[]);

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

static void confirm_bag_was_emptied(bool const resultsBag[])
{
    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        TEST_ASSERT_MESSAGE(resultsBag[i],
                            "Not all tetriminos were retrieved.");
    }
}

static void empty_test_bag(TetriminoColor testBag[], bool resultsBag[])
{
    Tetrimino result;

    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        result = make_random_tetrimino(testBag);
        int index = ((int)result.type) - 1;

        TEST_ASSERT_MESSAGE(!resultsBag[index],
                            "resultsBag is not all false prior to test.");

        resultsBag[index] = true;
    }
}

static void prep_results_bag_for_testing(bool resultsBag[])
{
    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        resultsBag[i] = false;
    }
}

