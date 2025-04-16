#include "gameui.h"
#include "colors.h"


static void cleanup_and_exit(int code)
{
    endwin();
    exit(code);
}

void initialize_ui(GameUI *ui)
{
    signal(SIGINT, cleanup_and_exit);

    initscr();
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
    initialize_borders(ui);
    initialize_playable_space(ui);
}

void update_screen(GameUI *ui)
{
    for (int i = 0; i < PLAYFIELD_ROWS; ++i)
    {
        wrefresh(ui->playfieldWindows[i]);
    }

    for (int i = 0; i < PREVIEW_ROWS; ++i)
    {
        wrefresh(ui->previewWindows[i]);
    }
}

void exit_game(int code)
{
    cleanup_and_exit(code);
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

void initialize_borders(GameUI *ui)
{
    ui->playfieldBorder = newwin(PLAYFIELD_ROWS + 2,
                                 PLAYFIELD_TEXT_COLUMNS + 2,
                                 PLAYFIELD_OFFSET_ROWS - 1,
                                 PLAYFIELD_OFFSET_COLUMNS - 1);
    box(ui->playfieldBorder, 0, 0);
    wrefresh(ui->playfieldBorder);

    ui->previewBorder = newwin(PREVIEW_ROWS + 2,
                               PREVIEW_TEXT_COLUMNS + 2,
                               PREVIEW_OFFSET_ROWS - 1,
                               PREVIEW_OFFSET_COLUMNS - 1);
    box(ui->previewBorder, 0, 0);
    mvwprintw(ui->previewBorder, 0, 5, "Next");
    wrefresh(ui->previewBorder);
}

void initialize_playable_space(GameUI *ui)
{
    for (int i = 0; i < PLAYFIELD_ROWS; ++i)
    {
        ui->playfieldWindows[i] = newwin(1,
                                         PLAYFIELD_TEXT_COLUMNS,
                                         PLAYFIELD_OFFSET_ROWS + i,
                                         PLAYFIELD_OFFSET_COLUMNS);
        //wrefresh(ui->playfieldWindows[i]);
    }

    for (int i = 0; i < PREVIEW_ROWS; ++i)
    {
        ui->previewWindows[i] = newwin(1,
                                       PREVIEW_TEXT_COLUMNS,
                                       PREVIEW_OFFSET_ROWS,
                                       PREVIEW_OFFSET_COLUMNS);
        //wrefresh(ui->previewWindows[i]);
    }
}

