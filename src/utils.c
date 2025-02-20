#include "utils.h"

float getRandomFloat(int min, int max){
    float percentage = (float)rand() / RAND_MAX;
    return percentage * (max-min) + min;
}