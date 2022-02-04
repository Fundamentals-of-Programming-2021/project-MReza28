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
    int pathlength;

    double angle;

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

void Spaceship_creat (struct Nation* nation , struct Planet* start , struct Planet* end , struct Spaceship* spaceship , int distances[PLANET_MAX][PLANET_MAX]) {
    spaceship->moving = true;

    spaceship->nation = nation;
    spaceship->typeoftexture = nation->armytexture;
    
    spaceship->lifetime = 0;
    spaceship->start = start;
    spaceship->end = end;
    spaceship->pathlength = distances[start->id][end->id];
    
    spaceship->angle = atan2((double)((end->x)-(start->x)) , (double)((start->y)-(end->y))) * 180.0 / M_PI ;
}

void Spaceship_movement (struct Spaceship* obj){
    (obj->lifetime)++;
    int distancemoved = ATTAK_SPEED*(obj->lifetime);
    //movement
    obj->x = (obj->start->x) + distancemoved*((obj->end->x) - (obj->start->x))/(obj->pathlength);
    obj->y = (obj->start->y) + distancemoved*((obj->end->y) - (obj->start->y))/(obj->pathlength);

    obj->rect.x = obj->x;
    obj->rect.y = obj->y;
}