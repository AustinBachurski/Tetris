#ifndef TETRIS_TETRIMINO_H
#define TETRIS_TETRIMINO_H

#define TETRIMINO_COUNT 7


typedef enum {
    Tetrimino_empty = 0,
    Tetrimino_lightBlue = 1,
    Tetrimino_darkBlue = 2,
    Tetrimino_orange = 3,
    Tetrimino_yellow = 4,
    Tetrimino_green = 5,
    Tetrimino_red = 6,
    Tetrimino_magenta = 7,
} TetriminoColor;

typedef enum {
    Facing_up,
    Facing_down,
    Facing_right,
    Facing_left,
} Orientation;

typedef struct {
    int centroidRow;
    int centroidColumn;
    TetriminoColor type;
    Orientation orientation;
} Tetrimino;

typedef struct {
    int row;
    int column;
} Vec2;


#endif

