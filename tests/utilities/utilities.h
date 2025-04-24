#ifndef TETRIS_TESTS_UTILITIES_H
#define TETRIS_TESTS_UTILITIES_H

#include "../../src/game/game.h"

[[nodiscard]] bool correct_spaces_occupied(GameData* game, int const indices[]);
void shift_indices_down(int indices[]);

#endif

