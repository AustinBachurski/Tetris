#ifndef TETRIS_GAME_RUNNER_H
#define TETRIS_GAME_RUNNER_H

#include "gamesettings.h"
#include "../ui/ui.h"
#include "../tetriminos/tetrimino.h"


typedef struct GameData
{
    GameUI ui;
    Tetrimino currentTetrimino;
    Tetrimino nextTetrimino;
    TetriminoColor randomBag[TETRIMINO_COUNT];
    TetriminoColor playfield[PLAYFIELD_SIZE];
} GameData;

void play_tetris(void);

void clear_playfield(GameData *game);
void cycle_in_next_tetrimino(GameData *game);
TetriminoColor get_next_tetrimino(TetriminoColor bag[]);
void initialize_game(GameData *game);
TetriminoColor only_one_remains(TetriminoColor bag[]);
Tetrimino make_random_tetrimino(TetriminoColor bag[]);
void reset_bag(TetriminoColor bag[]);
void spawn_tetrimino(GameData *game);
void set_preview(GameData *game);
void wait_for_keypress(GameData *game);

#endif

/*
    Playfield
     0 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     1 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     2 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     3 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     4 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     5 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     6 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     7 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     8 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     9 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    10 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    11 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    12 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    13 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    14 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    15 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    16 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    17 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    18 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    19 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }

*/
