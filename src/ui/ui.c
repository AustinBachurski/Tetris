#include "ui.h"

#include "colors.h"
#include "../game/gamesettings.h"
#include "../game/game.h"
#include "../tetriminos/tetrimino.h"

#include <signal.h>
#include <stdlib.h>

static void cleanup_and_exit(int code)
{
    endwin();
    exit(code);
}

void draw_playfield(GameData *game)
{
    int screenRow = 0;
    int screenColumn = 0;

    for (int row = 0; row < PLAYFIELD_SIZE; row += PLAYFIELD_COLUMNS)
    {
        screenRow = row / PLAYFIELD_COLUMNS + 1;
        screenColumn = 1;

        for (int column = row % PLAYFIELD_COLUMNS;
                column < PLAYFIELD_COLUMNS; ++column)
        {
            wattron(game->ui.playfieldWindow,
                    COLOR_PAIR(game->playfield[row + column]));
            mvwprintw(game->ui.playfieldWindow, screenRow, screenColumn, "  ");
            wattroff(game->ui.playfieldWindow,
                     COLOR_PAIR(game->playfield[row + column]));
            screenColumn += 2;
        }
    }

    wrefresh(game->ui.playfieldWindow);
}

void exit_game(int code)
{
    cleanup_and_exit(code);
}

void initialize_ui(GameData *game)
{
    signal(SIGINT, cleanup_and_exit);

    initscr();
    curs_set(0);
    start_color();
    noecho();

    if (COLORS < 256)
    {
        endwin();
        printw("256-color mode not supported.");
        getch();
        exit_game(1);
    }
    
    initialize_colors();
    initialize_game_windows(&game->ui);
    clear_playfield(game);
}

void set_preview(GameData *game)
{
    clear_preview(game->ui.previewWindow);

    switch (game->nextTetrimino.type)
    {
        case Tetrimino_empty:
            // TODO: Should never happen.
            return;

        case Tetrimino_lightBlue:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_lightBlue));
            mvwprintw(game->ui.previewWindow, 2, 3, "        ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_lightBlue));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_darkBlue:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_darkBlue));
            mvwprintw(game->ui.previewWindow, 2, 4, "  ");
            mvwprintw(game->ui.previewWindow, 3, 4, "      ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_darkBlue));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_orange:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_orange));
            mvwprintw(game->ui.previewWindow, 2, 8, "  ");
            mvwprintw(game->ui.previewWindow, 3, 4, "      ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_orange));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_yellow:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_yellow));
            mvwprintw(game->ui.previewWindow, 2, 5, "    ");
            mvwprintw(game->ui.previewWindow, 3, 5, "    ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_yellow));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_red:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_red));
            mvwprintw(game->ui.previewWindow, 2, 4, "    ");
            mvwprintw(game->ui.previewWindow, 3, 6, "    ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_red));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_green:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_green));
            mvwprintw(game->ui.previewWindow, 2, 6, "    ");
            mvwprintw(game->ui.previewWindow, 3, 4, "    ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_green));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_magenta:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_magenta));
            mvwprintw(game->ui.previewWindow, 2, 6, "  ");
            mvwprintw(game->ui.previewWindow, 3, 4, "      ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_magenta));
            wrefresh(game->ui.previewWindow);
            return;
    }
}

void show_game_over(GameData *game)
{
    mvwprintw(game->ui.playfieldWindow, 0, 4, "  Game Over!  ");
    wrefresh(game->ui.playfieldWindow);

    clear_preview(game->ui.previewWindow);
    mvwprintw(game->ui.previewWindow, 2, 1, " Play Again");
    mvwprintw(game->ui.previewWindow, 3, 1, "   (y/n)?");
    wrefresh(game->ui.previewWindow);

    char choice = (char)getch();

    while (choice != 'y' && choice != 'n')
    {
        choice = (char)getch();
    }

    if ('n' == choice)
    {
        exit_game(0);
    }

    initialize_game(game);
}

void initialize_colors(void)
{
    init_pair(Tetrimino_empty,     COLOR_BLACK, COLOR_BLACK);
    init_pair(Tetrimino_lightBlue, COLOR_BLACK, CUSTOM_COLOR_LIGHTBLUE);
    init_pair(Tetrimino_darkBlue,  COLOR_BLACK, CUSTOM_COLOR_DARKBLUE);
    init_pair(Tetrimino_orange,    COLOR_BLACK, CUSTOM_COLOR_ORANGE);
    init_pair(Tetrimino_yellow,    COLOR_BLACK, CUSTOM_COLOR_YELLOW);
    init_pair(Tetrimino_green,     COLOR_BLACK, CUSTOM_COLOR_GREEN);
    init_pair(Tetrimino_red,       COLOR_BLACK, CUSTOM_COLOR_RED);
    init_pair(Tetrimino_magenta,   COLOR_BLACK, CUSTOM_COLOR_MAGENTA);
}

void initialize_game_windows(GameUI *ui)
{
    ui->playfieldWindow = newwin(PLAYFIELD_ROWS + WINDOW_BORDER,
                           PLAYFIELD_WINDOW_COLUMNS + WINDOW_BORDER,
                           PLAYFIELD_PLACEMENT_ROW,
                           PLAYFIELD_PLACEMENT_COLUMN);
    box(ui->playfieldWindow, 0, 0);

    ui->previewWindow = newwin(PREVIEW_ROWS + WINDOW_BORDER,
                               PREVIEW_WINDOW_COLUMNS + WINDOW_BORDER,
                               PREVIEW_PLACEMENT_ROW,
                               PREVIEW_PLACEMENT_COLUMN);
    box(ui->previewWindow, 0, 0);
    mvwprintw(ui->previewWindow, 0, 5, "Next");
    
    refresh();
}

void clear_preview(WINDOW *previewWindow)
{
    wattron(previewWindow, COLOR_PAIR(Tetrimino_empty));
    mvwprintw(previewWindow, 2, 1, "            ");
    mvwprintw(previewWindow, 3, 1, "            ");
    wattroff(previewWindow, COLOR_PAIR(Tetrimino_empty));
}

