#include "Main_includes.h"
#include "Planet.h"

struct Spaceship {
    bool moving;
    
    struct Nation* nation;
    int typeoftexture;
    SDL_Rect rect;
    
    int lifetime;
    struct Planet* start;
    struct Planet* end;
    int x;
    int y;
};

void Spaceship_alloc (struct Spaceship* spaceships) {
    for (int  i = 0; i < SPACESHIP_POPUALTON; i++)
    {
        (spaceships+i)->rect.h = SPACESHIP_H;
        (spaceships+i)->rect.w = SPACESHIP_W;
        (spaceships+i)->moving = false;
    }
}

void Spaceship_creat (struct Nation* nation , struct Planet* start , struct Planet* end , struct Spaceship* spaceship) {
    spaceship->moving = true;

    spaceship->nation = nation;
    spaceship->typeoftexture = nation->armytexture;
    
    spaceship->lifetime = 0;
    spaceship->start = start;
    spaceship->end = end;
}