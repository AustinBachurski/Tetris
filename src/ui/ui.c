#include "ui.h"

#include "colors.h"
#include "../game/game.h"
#include "../game/gamesettings.h"
#include "../tetrimino/tetrimino.h"

#include <curses.h>

#include <signal.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <time.h>

#define ANIMATION_COLOR 8
#define ANIMATION_STEPS 3
#define NANOSECONDS_FOR_50_MILLISECONDS (50 * 1000000)

static void animation_step(GameUI *ui, int const row, int const step);
static void cleanup_and_exit(int code);
static void clear_preview(WINDOW *previewWindow);
static void initialize_colors(void);
static void initialize_game_windows(GameUI *ui);

extern void clear_playfield(GameData *game);
extern void initialize_game(GameData *game);

void animate_lines(GameData *game, int const rows[], int const size)
{
    struct timespec const delay = { 0, NANOSECONDS_FOR_50_MILLISECONDS };

    for (int step = 0; step < ANIMATION_STEPS; ++step)
    {
        for (int i = 0; i < size; ++i)
        {
            animation_step(&game->ui, rows[i] / PLAYFIELD_COLUMNS, step);
        }

        wrefresh(game->ui.playfieldWindow);
        nanosleep(&delay, NULL);
    }
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
}

bool play_again(GameData *game, InputHandles *input)
{
    mvwprintw(game->ui.playfieldWindow, 0, 4, "  Game Over!  ");
    wrefresh(game->ui.playfieldWindow);

    clear_preview(game->ui.previewWindow);
    mvwprintw(game->ui.previewWindow, 2, 3, "Play");
    mvwprintw(game->ui.previewWindow, 3, 3, "Again");
    mvwprintw(game->ui.previewWindow, 4, 3, "(y/n)?");
    wrefresh(game->ui.previewWindow);

    Command choice = Command_doNothing;

    while (true)
    {
        while (!choice)
        {
            choice = (Command)atomic_load_explicit(&input->command,
                                                   memory_order_acquire);
        }

        if (Command_quit == choice)
        {
            return false;
        }

        if (Command_playAgain == choice)
        {
            return true;
        }

        atomic_store_explicit(&input->command,
                              (int) Command_doNothing,
                              memory_order_release);

        choice = Command_doNothing;
    }

    return false;
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
            mvwprintw(game->ui.previewWindow, 2, 2, "        ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_lightBlue));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_darkBlue:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_darkBlue));
            mvwprintw(game->ui.previewWindow, 2, 3, "  ");
            mvwprintw(game->ui.previewWindow, 3, 3, "      ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_darkBlue));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_orange:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_orange));
            mvwprintw(game->ui.previewWindow, 2, 7, "  ");
            mvwprintw(game->ui.previewWindow, 3, 3, "      ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_orange));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_yellow:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_yellow));
            mvwprintw(game->ui.previewWindow, 2, 4, "    ");
            mvwprintw(game->ui.previewWindow, 3, 4, "    ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_yellow));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_red:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_red));
            mvwprintw(game->ui.previewWindow, 2, 3, "    ");
            mvwprintw(game->ui.previewWindow, 3, 5, "    ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_red));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_green:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_green));
            mvwprintw(game->ui.previewWindow, 2, 5, "    ");
            mvwprintw(game->ui.previewWindow, 3, 3, "    ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_green));
            wrefresh(game->ui.previewWindow);
            return;

        case Tetrimino_magenta:
            wattron(game->ui.previewWindow, COLOR_PAIR(Tetrimino_magenta));
            mvwprintw(game->ui.previewWindow, 2, 5, "  ");
            mvwprintw(game->ui.previewWindow, 3, 3, "      ");
            wattroff(game->ui.previewWindow, COLOR_PAIR(Tetrimino_magenta));
            wrefresh(game->ui.previewWindow);
            return;
    }
}

void update_screen(GameData *game)
{
    int screenRow = PLAYFIELD_WINDOW_ROWS;
    int screenColumn = 0;
    TetriminoColor currentCell = Tetrimino_empty;

    for (int row = 0; row < PLAYFIELD_WINDOW_SIZE; row += PLAYFIELD_COLUMNS)
    {
        screenRow = PLAYFIELD_WINDOW_ROWS - (row / PLAYFIELD_COLUMNS);
        screenColumn = 1;

        for (int column = row % PLAYFIELD_COLUMNS;
                column < PLAYFIELD_COLUMNS; ++column)
        {
            currentCell = game->playfield[row + column];

            wattron(game->ui.playfieldWindow, COLOR_PAIR(currentCell));
            mvwprintw(game->ui.playfieldWindow, screenRow, screenColumn, "  ");
            wattroff(game->ui.playfieldWindow, COLOR_PAIR(currentCell));
            screenColumn += 2;
        }
    }

    mvwprintw(game->ui.scoreWindow, 1, 2, "%07d", game->score);
    mvwprintw(game->ui.linesWindow, 1, 4, "%03d", game->lines);
    mvwprintw(game->ui.levelWindow, 1, 3, "%02d", game->level);

    wrefresh(game->ui.playfieldWindow);
    wrefresh(game->ui.scoreWindow);
    wrefresh(game->ui.linesWindow);
    wrefresh(game->ui.levelWindow);
}

static void animation_step(GameUI *ui, int const row, int const step)
{
    int const screenRow = PLAYFIELD_WINDOW_ROWS - row;

    switch (step)
    {
        case 0:
        {
            wattron(ui->playfieldWindow, COLOR_PAIR(ANIMATION_COLOR));
            mvwprintw(ui->playfieldWindow, screenRow, 1, "                    ");
            wattroff(ui->playfieldWindow, COLOR_PAIR(ANIMATION_COLOR));
            return;
        }

        case 1:
        {
            mvwprintw(ui->playfieldWindow, screenRow, 1, "====================");
            return;
        }

        case 2:
        {
            mvwprintw(ui->playfieldWindow, screenRow, 1, "--------------------");
            return;
        }

    }
}

static void cleanup_and_exit(int code)
{
    endwin();
    exit(code);
}

static void clear_preview(WINDOW *previewWindow)
{
    wattron(previewWindow, COLOR_PAIR(Tetrimino_empty));
    mvwprintw(previewWindow, 2, 1, "          ");
    mvwprintw(previewWindow, 3, 1, "          ");
    wattroff(previewWindow, COLOR_PAIR(Tetrimino_empty));
}

static void initialize_colors(void)
{
    init_pair(Tetrimino_empty,     COLOR_BLACK, COLOR_BLACK);
    init_pair(Tetrimino_lightBlue, COLOR_BLACK, CUSTOM_COLOR_LIGHTBLUE);
    init_pair(Tetrimino_darkBlue,  COLOR_BLACK, CUSTOM_COLOR_DARKBLUE);
    init_pair(Tetrimino_orange,    COLOR_BLACK, CUSTOM_COLOR_ORANGE);
    init_pair(Tetrimino_yellow,    COLOR_BLACK, CUSTOM_COLOR_YELLOW);
    init_pair(Tetrimino_green,     COLOR_BLACK, CUSTOM_COLOR_GREEN);
    init_pair(Tetrimino_red,       COLOR_BLACK, CUSTOM_COLOR_RED);
    init_pair(Tetrimino_magenta,   COLOR_BLACK, CUSTOM_COLOR_MAGENTA);
    init_pair(ANIMATION_COLOR,     COLOR_BLACK, COLOR_WHITE);
}

static void initialize_game_windows(GameUI *ui)
{
    ui->playfieldWindow = newwin(PLAYFIELD_WINDOW_ROWS + WINDOW_BORDER,
                           PLAYFIELD_WINDOW_COLUMNS + WINDOW_BORDER,
                           PLAYFIELD_PLACEMENT_ROW,
                           PLAYFIELD_PLACEMENT_COLUMN);
    box(ui->playfieldWindow, 0, 0);

    ui->previewWindow = newwin(PREVIEW_ROWS + WINDOW_BORDER,
                               PREVIEW_WINDOW_COLUMNS + WINDOW_BORDER,
                               PREVIEW_PLACEMENT_ROW,
                               PREVIEW_PLACEMENT_COLUMN);
    box(ui->previewWindow, 0, 0);
    mvwprintw(ui->previewWindow, 0, 4, "Next");

    ui->scoreWindow = newwin(SCORE_ROWS + WINDOW_BORDER,
                             SCORE_COLUMNS + WINDOW_BORDER,
                             SCORE_PLACEMENT_ROW,
                             SCORE_PLACEMENT_COLUMN);
    box(ui->scoreWindow, 0, 0);
    mvwprintw(ui->scoreWindow, 0, 3, "Score");
    mvwprintw(ui->scoreWindow, 1, 2, "0000000");
    
    ui->linesWindow = newwin(LINES_ROWS + WINDOW_BORDER,
                             LINES_COLUMNS + WINDOW_BORDER,
                             LINES_PLACEMENT_ROW,
                             LINES_PLACEMENT_COLUMN);
    box(ui->linesWindow, 0, 0);
    mvwprintw(ui->linesWindow, 0, 3, "Lines");
    mvwprintw(ui->linesWindow, 1, 4, "000");
    
    ui->levelWindow = newwin(LEVEL_ROWS + WINDOW_BORDER,
                             LEVEL_COLUMNS + WINDOW_BORDER,
                             LEVEL_PLACEMENT_ROW,
                             LEVEL_PLACEMENT_COLUMN);
    box(ui->levelWindow, 0, 0);
    mvwprintw(ui->levelWindow, 0, 2, "Level");
    mvwprintw(ui->levelWindow, 1, 3, "000");
    
    refresh();
    wrefresh(ui->scoreWindow);
    wrefresh(ui->linesWindow);
    wrefresh(ui->levelWindow);
}

