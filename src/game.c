#include "game.h"

//-----------------------------------------------------------
//  SHIFTS
//-----------------------------------------------------------

int shiftLeft(Grid* grid){
    for(int i = 0;i<grid->n;i++){
        int col = 0;

        for(int j = 0;j<grid->m;j++){
            if((grid->ptr)[i][j] != 0){
                int aux = (grid->ptr)[i][j];
                (grid->ptr)[i][j] = 0;
                (grid->ptr)[i][col] = aux;
                col++;
            }
        }
    }

    return 1;
}

int shiftRight(Grid* grid){
    for(int i = 0;i<grid->n;i++){
        int col = grid->m-1;

        for(int j = grid->m-1;j>=0;j--){
            if((grid->ptr)[i][j] != 0){
                int aux = (grid->ptr)[i][j];
                (grid->ptr)[i][j] = 0;
                (grid->ptr)[i][col] = aux;
                col--;
            }
        }
    }

    return 1;
}

int shiftUp(Grid* grid){
    for(int j = 0;j<grid->m;j++){
        int row = 0;

        for(int i = 0;i<grid->n;i++){
            if((grid->ptr)[i][j] != 0){
                int aux = (grid->ptr)[i][j];
                (grid->ptr)[i][j] = 0;
                (grid->ptr)[row][j] = aux;
                row++;
            }
        }
    }

    return 1;
}

int shiftDown(Grid* grid){
    for(int j = 0;j<grid->m;j++){
        int row = grid->n-1;

        for(int i = grid->n-1;i>=0;i--){
            if((grid->ptr)[i][j] != 0){
                int aux = (grid->ptr)[i][j];
                (grid->ptr)[i][j] = 0;
                (grid->ptr)[row][j] = aux;
                row--;
            }
        }
    }

    return 1;
}

int shiftGrid(Grid* grid, Move move){
    switch (move)
    {
        case LEFT:
            shiftLeft(grid);
            break;
        
        case RIGHT:
            shiftRight(grid);
            break;

        case UP:
            shiftUp(grid);
            break;
        
        case DOWN:
            shiftDown(grid);
            break;
        
        default:
            break;
    }

    return 1;
}

//-----------------------------------------------------------
//  MERGES
//-----------------------------------------------------------

int mergeLeft(Grid* grid){
    for(int i = 0;i<grid->n;i++){
        int* row = grid->ptr[i];

        for(int j = 0;j<grid->m-1;j++){
            if(row[j] == row[j+1]){
                row[j] *= 2;
                row[j+1] = 0;
            }
        }
    }

    return 1;
}

int mergeRight(Grid* grid){
    for(int i = 0;i<grid->n;i++){
        int* row = grid->ptr[i];

        for(int j = grid->m-1; j>0;j--){
            if(row[j] == row[j-1]){
                row[j] *= 2;
                row[j-1] = 0;
            }
        }
    }

    return 1;
}

int mergeUp(Grid* grid){
    for(int j = 0;j<grid->m;j++){

        for(int i = 0;i<grid->n-1;i++){
            if(grid->ptr[i][j] == grid->ptr[i+1][j]){
                grid->ptr[i][j] *= 2;
                grid->ptr[i+1][j] = 0;
            }
        }
    }

    return 1;
}

int mergeDown(Grid* grid){
    for(int j = 0;j<grid->m;j++){

        for(int i = grid->n-1; i>0;i--){
            if(grid->ptr[i][j] == grid->ptr[i-1][j]){
                grid->ptr[i][j] *= 2;
                grid->ptr[i-1][j] = 0;
            }
        }
    }

    return 1;
}

int mergeGrid(Grid* grid, Move move){
    switch (move)
    {
        case LEFT:
            mergeLeft(grid);
            break;
        
        case RIGHT:
            mergeRight(grid);
            break;

        case UP:
            mergeUp(grid);
            break;
        
        case DOWN:
            mergeDown(grid);
            break;
        
        default:
            break;
    }
    
    return 1;
}

//-----------------------------------------------------------
//  UPDATE
//-----------------------------------------------------------

Move getMove(){
    if(IsKeyPressed(KEY_UP)) return UP;
    if(IsKeyPressed(KEY_RIGHT)) return RIGHT;
    if(IsKeyPressed(KEY_DOWN)) return DOWN;
    if(IsKeyPressed(KEY_LEFT)) return LEFT;
    else return NONE;
}

int updateGrid(Grid* grid){
    Move move = getMove();

    if(move != NONE){
        shiftGrid(grid, move);
        mergeGrid(grid, move);
        shiftGrid(grid, move);

        fillRandomCell(grid);
    }

    return 1;
}