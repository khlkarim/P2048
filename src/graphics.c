#include "graphics.h"

//-----------------------------------------------------------
//  DRAW GRID
//-----------------------------------------------------------

int drawGrid(Grid* grid){
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
            
            if(grid->ptr[i][j] != 0)
            {
                DrawRectangle(posX+3, posY+3, cellWidth-6, cellHeight-6, getColor(val));
                DrawText(str, posX + cellWidth/2 - MeasureText(str, fontSize)/2, posY + cellHeight/2 - fontSize/2, fontSize, BLACK);
            }
        }
    }

    return 1;
}
