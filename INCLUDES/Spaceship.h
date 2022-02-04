#include "Main_includes.h"
#include "Planet.h"

struct Spaceship {
    bool moving;
    
    struct Nation nation;
    int typeoftexture;
    SDL_Rect rect;
    
    int lifetime;
    struct Planet* start;
    struct Planet* end;
    int x;
    int y;
};

void Spaceship_alloc (struct Spaceship* spaceships , int howmany) {
    spaceships;
}

void Spaceship_creat (struct Nation nation , struct Planet* start , struct Planet* end , struct Spaceship* spaceship) {
    spaceship->moving = true;

    spaceship->nation = nation;
    spaceship->typeoftexture = nation.armytexture;
    
    spaceship->lifetime = 0;
    spaceship->start = start;
    spaceship->end = end;

}