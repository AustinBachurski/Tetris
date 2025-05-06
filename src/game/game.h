#ifndef TETRIS_GAME_RUNNER_H
#define TETRIS_GAME_RUNNER_H

#include "gamesettings.h"
#include "../ui/ui.h"
#include "../tetrimino/tetrimino.h"

#include <sys/time.h>

typedef struct GameData
{
    GameUI ui;
    Tetrimino currentTetrimino;
    Tetrimino nextTetrimino;
    TetriminoColor randomBag[TETRIMINO_COUNT];
    TetriminoColor playfield[PLAYFIELD_SIZE];
    double difficulty;
    struct timeval dropTime;
} GameData;

typedef enum Command
{
    Command_doNothing,
    Command_moveDown,
    Command_moveLeft,
    Command_moveRight,
    Command_rotate,
    Command_playAgain,
    Command_quit,
} Command;

typedef struct MovementData
{
    Tetrimino target;
    int sourceIndices[SQUARES_PER_TETRIMINO];
    int targetIndices[SQUARES_PER_TETRIMINO];
} MovementData;

void play_tetris(void);

#endif

