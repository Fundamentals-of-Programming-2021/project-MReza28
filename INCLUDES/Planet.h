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

void Planet_alloc (int howmany , struct Planet* planets) {
    
}