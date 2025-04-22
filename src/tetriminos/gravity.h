#ifndef TETRIS_GRAVITY_H
#define TETRIS_GRAVITY_H

#include "../game/game.h"

void indicies_for_down(Tetrimino *current, int indicies[]);
[[nodiscard]] bool is_self(int indicies[], int current);
[[nodiscard]] bool move_down(GameData *game);
[[nodiscard]] bool valid_move(TetriminoColor playfield[], int indicies[]);

#endif

