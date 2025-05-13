#ifndef TETRIS_TETRIMINO_H
#define TETRIS_TETRIMINO_H

typedef enum Orientation
{
    North,
    South,
    East,
    West,
} Orientation;

typedef enum TetriminoColor
{
    Tetrimino_empty,
    Tetrimino_lightBlue,
    Tetrimino_darkBlue,
    Tetrimino_orange,
    Tetrimino_yellow,
    Tetrimino_green,
    Tetrimino_red,
    Tetrimino_magenta,
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
//   [ ][ ][*][ ]
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
//   [ ][*]
//   [ ][ ]
//
//
// Green
//
//      [*][ ]
//   [ ][ ]
//
//
// Red
//
//   [ ][*]
//      [ ][ ]
//
//
// Magenta
//
//      [ ]
//   [ ][*][ ]

//  Playfield
//  21 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  20 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  19 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  18 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  17 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  16 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  15 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  14 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  13 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  12 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  11 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//  10 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   9 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   8 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   7 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   6 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   5 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   4 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   3 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   2 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   1 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
//   0 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }

#endif

