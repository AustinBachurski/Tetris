#ifndef TETRIS_GAME_UI_H
#define TETRIS_GAME_UI_H

#include <curses.h>
#include <stdatomic.h>

typedef struct GameData GameData;
typedef struct InputHandles InputHandles;

typedef struct GameUI
{
    WINDOW *playfieldWindow;
    WINDOW *scoreWindow;
    WINDOW *linesWindow;
    WINDOW *previewWindow;
    WINDOW *levelWindow;
} GameUI;

void animate_lines(GameData *game, int const rows[], int const size);
void exit_game(int const code);
void initialize_ui(GameData *game);
[[nodiscard]] bool play_again(GameData *game, InputHandles *input);
void set_preview(GameData *game);
void update_screen(GameData *game);

#endif

