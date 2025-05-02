#ifndef TETRIS_GAME_RUNNER_H
#define TETRIS_GAME_RUNNER_H

#include "gamesettings.h"
#include "../ui/ui.h"
#include "../tetrimino/tetrimino.h"

typedef struct GameData
{
    GameUI ui;
    Tetrimino currentTetrimino;
    Tetrimino nextTetrimino;
    TetriminoColor randomBag[TETRIMINO_COUNT];
    TetriminoColor playfield[PLAYFIELD_SIZE];
} GameData;

typedef enum Command
{
    Command_doNothing,
    Command_moveDown,
    Command_moveLeft,
    Command_moveRight,
    Command_rotate,
} Command;

void play_tetris(void);

#endif

