#ifndef TETRIS_MOVE_DOWN_H
#define TETRIS_MOVE_DOWN_H

#include "../game/game.h"

[[nodiscard]] bool gravity_down(GameData *game);
void move_tetrimino_down(GameData *game);

#endif

