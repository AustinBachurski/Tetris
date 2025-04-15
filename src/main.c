#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>


#define ROWS    20
#define COLUMNS 10
#define TETRIMINO_COUNT 7
#define SPAWN_LOCATION 4

#define TEXT_COLUMNS (COLUMNS * 2)
#define PLAYFIELD_OFFSET_ROWS 15
#define PLAYFIELD_OFFSET_COLUMNS 45

static void finish(int _);

typedef enum 
{
    Tetrimino_empty     = 0,
    Tetrimino_lightBlue = 1,
    Tetrimino_darkBlue  = 2,
    Tetrimino_orange    = 3,
    Tetrimino_yellow    = 4,
    Tetrimino_green     = 5,
    Tetrimino_red       = 6,
    Tetrimino_magenta   = 7,

} TetriminoColor;

typedef enum
{
    Facing_up,
    Facing_down,
    Facing_right,
    Facing_left,

} Orientation;

TetriminoColor playfield[ROWS][COLUMNS] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

typedef struct
{
    int centroid;
    TetriminoColor type;
    Orientation orientation;

} Tetrimino;

void spawn_tetrimino(Tetrimino *current)
{
    switch (current->type)
    {
        case Tetrimino_empty:
            // TODO: Should never happen - how to handle error?
            return;

        case Tetrimino_lightBlue:
            playfield[0][3] = current->type;
            playfield[0][4] = current->type;
            playfield[0][5] = current->type;
            playfield[0][6] = current->type;
            return;

        case Tetrimino_darkBlue:
            [[fallthrough]];
        case Tetrimino_orange:
            [[fallthrough]];
        case Tetrimino_magenta:
            playfield[0][3] = current->type;
            playfield[0][4] = current->type;
            playfield[0][5] = current->type;
            return;

        case Tetrimino_yellow:
            [[fallthrough]];
        case Tetrimino_red:
            playfield[0][4] = current->type;
            playfield[0][5] = current->type;
            return;

        case Tetrimino_green:
            playfield[0][3] = current->type;
            playfield[0][4] = current->type;
            return;
    }
}

void init_windows(WINDOW *windows[ROWS])
{
    for (int i = 0; i < ROWS; ++i)
    {
        windows[i] = newwin(1,
                            TEXT_COLUMNS,
                            PLAYFIELD_OFFSET_ROWS + i,
                            PLAYFIELD_OFFSET_COLUMNS);
        wrefresh(windows[i]);
    }
}

void init_colors()
{
    init_pair(Tetrimino_empty,     COLOR_BLACK, COLOR_BLACK);
    init_pair(Tetrimino_lightBlue, COLOR_BLACK, 51);
    init_pair(Tetrimino_darkBlue,  COLOR_BLACK, 57);
    init_pair(Tetrimino_orange,    COLOR_BLACK, 208);
    init_pair(Tetrimino_yellow,    COLOR_BLACK, 190);
    init_pair(Tetrimino_green,     COLOR_BLACK, 46);
    init_pair(Tetrimino_red,       COLOR_BLACK, 196);
    init_pair(Tetrimino_magenta,   COLOR_BLACK, 171);
}

void update_screen(WINDOW *windows[ROWS])
{
    int insertion = 0;

    for (int row = 0; row < ROWS; ++row)
    {
        insertion = 0;

        for (int column = 0; column < COLUMNS; ++column)
        {
            WINDOW *window = windows[row];

            wattron(window, COLOR_PAIR(playfield[row][column]));
            mvwprintw(window, 0, insertion++, " ");
            mvwprintw(window, 0, insertion++, " ");
            wattroff(window, COLOR_PAIR(playfield[row][column]));
            wrefresh(window);
            refresh();
        }
    }
}

TetriminoColor last_one(TetriminoColor bag[])
{
    TetriminoColor selection = Tetrimino_empty;

    for (int i = 0; i < TETRIMINO_COUNT; ++i)
    {
        if (bag[i] != Tetrimino_empty)
        {
            if (selection == Tetrimino_empty)
            {
                selection = bag[i];
            }
            else
            {
                return Tetrimino_empty;
            }
        }
    }

    return selection;
}

void reset_bag(TetriminoColor bag[])
{
    bag[0] = Tetrimino_empty;
    bag[0] = Tetrimino_lightBlue;
    bag[1] = Tetrimino_darkBlue;
    bag[2] = Tetrimino_orange;
    bag[3] = Tetrimino_yellow;
    bag[4] = Tetrimino_green;
    bag[5] = Tetrimino_red;
    bag[6] = Tetrimino_magenta;
}

TetriminoColor get_next_tetrimino(TetriminoColor bag[])
{
    TetriminoColor selection = last_one(bag);

    if (selection)
    {
        reset_bag(bag);
        return selection;
    }
    
    int index = rand() % (TETRIMINO_COUNT - 1);

    while (bag[index] == Tetrimino_empty)
    {
        index = rand() % (TETRIMINO_COUNT - 1);
    }

    selection = bag[index];
    bag[index] = Tetrimino_empty;
    
    return selection;
}

int main(void)
{
    srand(time(NULL));
    TetriminoColor bag[7] = {
        Tetrimino_lightBlue,
        Tetrimino_darkBlue,
        Tetrimino_orange,
        Tetrimino_yellow,
        Tetrimino_green,
        Tetrimino_red,
        Tetrimino_magenta,
    };

    signal(SIGINT, finish);

    initscr();
    start_color();
    noecho();

    if (COLORS < 256) {
        endwin();
        printw("256-color mode not supported.");
        getch();
        finish(1);
    }
    
    // Playfield Border
    WINDOW *playfieldBorder = newwin(ROWS + 2,
                                     TEXT_COLUMNS + 2,
                                     PLAYFIELD_OFFSET_ROWS - 1,
                                     PLAYFIELD_OFFSET_COLUMNS - 1);
    box(playfieldBorder, 0, 0);
    refresh();
    wrefresh(playfieldBorder);

    // Playfield Init
    WINDOW *windows[ROWS];
    init_windows(windows);
    init_colors();

    Tetrimino current = { SPAWN_LOCATION, get_next_tetrimino(bag), Facing_up };
    //Tetrimino next = { SPAWN_LOCATION, get_next_tetrimino(bag), Facing_up };

    spawn_tetrimino(&current);

    // Game Loop
    //while(true)
    //{
        update_screen(windows);
        refresh();
        getch();

    //}

    finish(0);
}

static void finish([[maybe_unused]] int _)
{
    endwin();
    exit(0);
}
