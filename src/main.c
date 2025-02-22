#include <time.h>

#include "game.h"
#include "graphics.h"

//-----------------------------------------------------------
//  DRAW GRID
//-----------------------------------------------------------

int main(void){
    srand((unsigned int)time(NULL));
    SetRandomSeed((unsigned int)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2048");

    Image image = LoadImage("assets/icon.png");
    SetWindowIcon(image);
    UnloadImage(image);
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