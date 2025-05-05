#ifndef TETRIS_MOVEMENT_H
#define TETRIS_MOVEMENT_H

#include "tetrimino.h"
#include "../game/game.h"

#include <stdatomic.h>

void apply_changes(GameData *game, MovementData const *data);
bool gravity_down(GameData *game);
void indices_for(Tetrimino const *tetrimino, int indices[]);
[[nodiscard]] bool is_self(int const target, int const sourceIndices[]);
void move_tetrimino(GameData *game, atomic_int *command);

#endif

