#include "utils.h"

float getRandomFloat(int min, int max){
    float percentage = (float)rand() / RAND_MAX;
    return percentage * (max-min) + min;
}

Color getColor(int val){
    Color colorMap[] = {
        (Color){ 255, 255, 255, 255 }, // WHITE
        (Color){ 255, 255, 204, 255 },
        (Color){ 255, 255, 153, 255 },
        (Color){ 255, 255, 102, 255 },
        (Color){ 255, 204, 51, 255 },
        (Color){ 255, 153, 0, 255 },
        (Color){ 255, 128, 0, 255 },
        (Color){ 255, 102, 0, 255 },
        (Color){ 255, 77, 0, 255 },
        (Color){ 255, 51, 0, 255 }      // RED
    };

    int index = max(0, min(9, (int)log2(val)-1));
    Color c = colorMap[index];

    return c;
}