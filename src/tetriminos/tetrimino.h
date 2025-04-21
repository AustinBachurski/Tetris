#ifndef TETRIS_TETRIMINO_H
#define TETRIS_TETRIMINO_H

typedef enum Orientation
{
    Facing_up,
    Facing_down,
    Facing_right,
    Facing_left,
} Orientation;

typedef enum TetriminoColor
{
    Tetrimino_empty = 0,
    Tetrimino_lightBlue = 1,
    Tetrimino_darkBlue = 2,
    Tetrimino_orange = 3,
    Tetrimino_yellow = 4,
    Tetrimino_green = 5,
    Tetrimino_red = 6,
    Tetrimino_magenta = 7,
} TetriminoColor;

typedef struct Tetrimino
{
    int centroid;
    TetriminoColor type;
    Orientation orientation;
} Tetrimino;

// Tetriminos
//
// Light Blue
//
//   [ ][*][ ][ ]
//
//
// Dark Blue
//
//   [ ]
//   [ ][*][ ]
//
//
// Orange
//
//         [ ]
//   [ ][*][ ]
//
//
// Yellow
//
//   [ ][ ]
//   [*][ ]
//
//
// Green
//
//      [ ][ ]
//   [ ][*]
//
//
// Red
//
//   [ ][ ]
//      [*][ ]
//
//
// Magenta
//
//      [ ]
//   [ ][*][ ]

//  Playfield
//   0 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   1 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   2 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   3 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   4 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   5 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   6 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   7 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   8 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   9 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  10 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  11 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  12 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  13 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  14 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  15 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  16 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  17 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  18 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  19 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }


#endif

