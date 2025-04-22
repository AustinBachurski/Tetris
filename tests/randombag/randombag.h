#ifndef TETRIS_TESTS_RANDOMBAG_H
#define TETRIS_TESTS_RANDOMBAG_H

#include "../tetriminos/tetrimino.h"

#include <stdbool.h>


void confirm_bag_was_emptied(bool resultsBag[]);
void empty_test_bag(TetriminoColor testBag[], bool resultsBag[]);
void prep_results_bag_for_testing(bool resultsBag[]);
void random_bag_produces_complete_set(void);

#endif

