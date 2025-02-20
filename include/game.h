#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "grid.h"

typedef enum Move{
    NONE,
    UP,
    RIGHT,
    DOWN,
    LEFT
} Move;

//-----------------------------------------------------------
//  SHIFTS
//-----------------------------------------------------------

int shiftLeft(Grid* grid);
int shiftRight(Grid* grid);
int shiftUp(Grid* grid);
int shiftDown(Grid* grid);

int shiftGrid(Grid* grid, Move move);

//-----------------------------------------------------------
//  SHIFTS
//-----------------------------------------------------------

//-----------------------------------------------------------
//  MERGES
//-----------------------------------------------------------

int mergeLeft(Grid* grid);
int mergeRight(Grid* grid);
int mergeUp(Grid* grid);
int mergeDown(Grid* grid);

int mergeGrid(Grid* grid, Move move);

//-----------------------------------------------------------
//  MERGES
//-----------------------------------------------------------

int updateGrid(Grid* grid);

#endif