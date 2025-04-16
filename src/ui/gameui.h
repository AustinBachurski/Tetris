#ifndef TETRIS_GAME_UI_H
#define TETRIS_GAME_UI_H

#include "../tetriminos/tetrimino.h"
#include "colors.h"

#include <curses.h>
#include <signal.h>

#include <stdlib.h>

#define PLAYFIELD_ROWS 20
#define PLAYFIELD_COLUMNS 10
#define PLAYFIELD_TEXT_COLUMNS (PLAYFIELD_COLUMNS * 2)
#define PLAYFIELD_OFFSET_ROWS 15
#define PLAYFIELD_OFFSET_COLUMNS 45

#define PREVIEW_ROWS 2
#define PREVIEW_COLUMNS 6
#define PREVIEW_TEXT_COLUMNS (PREVIEW_COLUMNS * 2)
#define PREVIEW_OFFSET_ROWS 25
#define PREVIEW_OFFSET_COLUMNS 70

#define TETRIMINO_COUNT 7
#define SQUARES_PER_TETRIMINO 4


typedef struct
{
    WINDOW *playfieldWindows[PLAYFIELD_ROWS];
    WINDOW *previewWindows[PREVIEW_ROWS];
    WINDOW *playfieldBorder;
    WINDOW *previewBorder;
} GameUI;

void initialize_ui(GameUI *ui);
void update_screen(GameUI *ui);
void exit_game(int code);

void initialize_colors(void);
void initialize_borders(GameUI *ui);
void initialize_playable_space(GameUI *ui);


#endif
