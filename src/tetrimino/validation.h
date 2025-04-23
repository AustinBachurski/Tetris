#ifndef TETRIS_MOVEMENT_VALIDATION_H
#define TETRIS_MOVEMENT_VALIDATION_H

#include "tetrimino.h"

#include <stdbool.h>

bool valid_move(TetriminoColor playfield[],
                int indices[],
                bool (*is_self)(int[], int));

#endif

