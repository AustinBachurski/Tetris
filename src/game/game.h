#ifndef TETRIS_GAME_RUNNER_H
#define TETRIS_GAME_RUNNER_H

#include "../ui/gameui.h"
#include "../tetriminos/tetrimino.h"

#define PLAYFIELD_SIZE (PLAYFIELD_ROWS * PLAYFIELD_COLUMNS)
#define PREVIEW_SIZE (PREVIEW_ROWS * PREVIEW_COLUMNS)


typedef struct
{
    GameUI ui;
    Tetrimino currentTetrimino;
    Tetrimino nextTetrimino;
    TetriminoColor randomBag[TETRIMINO_COUNT];
    TetriminoColor playfield[PLAYFIELD_ROWS * PLAYFIELD_COLUMNS];
    TetriminoColor preview[PREVIEW_ROWS * PREVIEW_COLUMNS];
} Game;

int rungame(void);
void initialize_game(Game *game);

void clear_playfield(Game *game);
void clear_preview(Game *game);
void reset_bag(TetriminoColor bag[]);
void spawn_tetrimino(Game *game);
void show_preview(Game *game);

#endif

