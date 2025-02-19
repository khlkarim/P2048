#include "raylib.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define N 4  
#define M 4

typedef enum Move{
    NONE,
    UP,
    RIGHT,
    DOWN,
    LEFT
} Move;

typedef struct Grid{
    int n;
    int m;
    int** ptr;
} Grid;

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

float getRandomFloat(int min, int max){
    float percentage = (float)rand() / RAND_MAX;
    return percentage * (max-min) + min;
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

Move getMove(){
    if(IsKeyPressed(KEY_UP)) return UP;
    if(IsKeyPressed(KEY_RIGHT)) return RIGHT;
    if(IsKeyPressed(KEY_DOWN)) return DOWN;
    if(IsKeyPressed(KEY_LEFT)) return LEFT;
    else return NONE;
}

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
//  SHIFTS
//-----------------------------------------------------------

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
//  MERGES
//-----------------------------------------------------------

int updateGrid(Grid* grid){
    Move move = getMove();

    if(move != NONE){
        shiftGrid(grid, move);
        mergeGrid(grid, move);
        shiftGrid(grid, move);

        fillRandomCell(grid);
        printMatrix(grid);
    }

    return 1;
}

//-----------------------------------------------------------
//  DRAW GRID
//-----------------------------------------------------------

int drawGrid(Grid* grid){
    // draw n*m cells => then put grid[i][j] in the cell (i,j)

    const int cellHeight = (SCREEN_HEIGHT/grid->n);
    const int cellWidth = (SCREEN_WIDTH/grid->m);

    char str[12];

    for(int i = 0;i<grid->n;i++){
        for(int j = 0;j<grid->m;j++){
            int posX = j*cellWidth;
            int posY = i*cellHeight;
    
            int val = grid->ptr[i][j];
            snprintf(str, sizeof(str), "%d", val);
            int fontSize = 64;
            
            DrawRectangle(posX+3, posY+3, cellWidth-6, cellHeight-6, WHITE);
            DrawText(str, posX + cellWidth/2 - MeasureText(str, fontSize)/2, posY + cellHeight/2 - fontSize/2, fontSize, BLACK);
        }
    }

    return 1;
}

//-----------------------------------------------------------
//  DRAW GRID
//-----------------------------------------------------------

int main(void){
    srand((unsigned int)time(NULL));
    SetRandomSeed((unsigned int)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "p2048");
    SetTargetFPS(60);

    Grid* grid = createGrid(N, M);
    fillRandomCell(grid);
    fillRandomCell(grid);

    while(!WindowShouldClose()){
        updateGrid(grid);

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        drawGrid(grid);

        EndDrawing();
    }

    freeGrid(&grid);
    CloseWindow();
    return 0;
}

/*
2048 is played on a plain 
* 4×4 grid, 

The game 
* begins with two tiles already in the grid, 
* having a value of either 2 or 4, 

* and another such tile appears in a random empty space after each turn. 

?Tiles with a value of 2 appear 90% of the time, and tiles with a value of 4 appear 10% of the time. 

Tiles slide as far as possible in the chosen direction until they are stopped by either another tile or the edge of the grid. 

*If two tiles of the same number collide while moving, 
*they will merge into a tile with the total value of the two tiles that collided. 

!The resulting tile cannot merge with another tile again in the same move. 

Higher-scoring tiles emit a soft glow; the largest possible tile is 131,072.

If a move causes three consecutive tiles of the same value to slide together, 
!only the two tiles farthest along the direction of motion will combine. 

If all four spaces in a row or column are filled with tiles of the same value, 
a move parallel to that row/column will combine the first two and last two. 

A scoreboard on the upper-right keeps track of the user's score. 
?The user's score starts at zero, and is increased whenever two tiles combine, by the value of the new tile.

!The game is won when a tile with a value of 2048 appears on the board. 

Players can continue beyond that to reach higher scores. When the player has no legal moves (there are no empty spaces and no adjacent tiles with the same value), the game ends.
*/