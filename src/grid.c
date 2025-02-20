#include "grid.h"

Grid* createGrid(int n, int m){
    Grid* grid = (Grid*)malloc(sizeof(Grid));

    grid->n = n;
    grid->m = m;

    grid->ptr = (int**)malloc(n*sizeof(int*));

    for(int i = 0;i<n;i++){
        (grid->ptr)[i] = (int*)malloc(m*sizeof(int));

        for(int j = 0;j<m;j++){
            (grid->ptr)[i][j] = 0;
        }
    }

    return grid;
}

void printMatrix(Grid* grid){
    for(int i = 0;i<grid->n;i++){
        for(int j = 0;j<grid->m;j++){
            printf("%d ", (grid->ptr)[i][j]);
        }

        printf("\n");
    }
}

void freeGrid(Grid** grid){
    for(int i = 0;i<(*grid)->n;i++){
        free(((*grid)->ptr)[i]);
    }
    free((*grid)->ptr);
    free(*grid);
    *grid = NULL;
}

int fillRandomCell(Grid* grid){
    int test = 0;

    for(int i = 0;i<grid->n;i++){
        for(int j = 0;j<grid->m;j++){
            if((grid->ptr)[i][j] == 0){
                test = 1;
                break;
            }
        }
    }

    if(test == 0) return 0;

    while(true){
        int i = GetRandomValue(0, grid->n-1);
        int j = GetRandomValue(0, grid->m-1);

        if((grid->ptr)[i][j] != 0){
            continue;
        }

        float percentage = getRandomFloat(0, 1);

        (grid->ptr)[i][j] = (percentage>0.9? 4:2);
        return 1;
    }
}