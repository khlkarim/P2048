#ifndef GRID_H
#define GRID_H

#include "utils.h"

#include <stdbool.h>

typedef struct Grid{
    int n;
    int m;
    int** ptr;
} Grid;

Grid* createGrid(int n, int m);
void printMatrix(Grid* grid);
void freeGrid(Grid** grid);
int fillRandomCell(Grid* grid);

#endif