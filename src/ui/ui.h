#ifndef TETRIS_GAME_UI_H
#define TETRIS_GAME_UI_H

#include <curses.h>

typedef struct GameData GameData;

typedef struct GameUI
{
    WINDOW *playfieldWindow;
    WINDOW *previewWindow;
} GameUI;

void draw_playfield(GameData *game);
void exit_game(int const code);
void initialize_ui(GameData *game);
void set_preview(GameData *game);
void show_game_over(GameData *game);

void initialize_colors(void);
void initialize_game_windows(GameUI *ui);
void clear_preview(WINDOW *previewWindow);


#endif

