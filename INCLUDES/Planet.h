#include "Main_includes.h"
#include "Nation.h"

struct Planet {
    int id;
    int nation;
    int potion;
    SDL_Rect rect;
    
    int x;
    int y;
    int state;

    int population;
};