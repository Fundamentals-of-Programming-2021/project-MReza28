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
    for (int  i = 0; i < SPACESHIP_MAX; i++)
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

void Spaceship_dis_checker (struct Spaceship *A , struct Spaceship *B) {
    if(Distance_1D(A->x , A->y , B->x , B->y) < SPACESHIP_MIN_DIS && A->nation->color != B->nation->color){
        if(A->nation->potion != 3)
            A->moving = false;
        if(B->nation->potion != 3)
            B->moving = false;
    }
}

void Spaceship_movement (struct Spaceship* obj , SDL_Renderer* renderer , SDL_Texture **spaceshiptextures){
    (obj->lifetime)+=2;

    if(obj->nation->potion == 1) (obj->lifetime)+=2;
    else if(obj->nation->potion == 2) (obj->lifetime)--;

    int distancemoved = ATTAK_SPEED*(obj->lifetime);
    //movement
    obj->x = (obj->start->x) + distancemoved*((obj->end->x) - (obj->start->x))/(obj->pathlength);
    obj->y = (obj->start->y) + distancemoved*((obj->end->y) - (obj->start->y))/(obj->pathlength);

    obj->rect.x = obj->x - SPACESHIP_W/2;
    obj->rect.y = obj->y - SPACESHIP_H/2;

    SDL_RenderCopyEx(renderer , *((spaceshiptextures+(obj->nation->color)-1) + 7*(obj->nation->armytexture)) , NULL ,  &(obj->rect) , obj->angle , NULL , SDL_FLIP_NONE);

    /*adding rendercopy for potions*/
    if(obj->nation->potion != 0 && obj->nation->potion<4){
        SDL_RenderCopyEx(renderer , *(spaceshiptextures + 3 + 7*(obj->nation->armytexture) + (obj->nation->potion)) , NULL ,  &(obj->rect) , obj->angle , NULL , SDL_FLIP_NONE);
    }

    if(distancemoved > obj->pathlength - obj->end->rect.w/2 + 5){
        obj->moving = false;
        if(obj->nation == obj->end->nation){
            obj->end->population++;
        }
        else{
            if(obj->end->population == 0){
                (obj->end->population)++;
                obj->end->nation = obj->nation;
                obj->end->trigered = false;
            }
            else{
                if(obj->nation->potion == 3){
                    if(obj->end->population == 0){
                        (obj->end->population)++;
                        obj->end->nation = obj->nation;
                        obj->end->trigered = false;
                    }
                    else if(obj->end->population == 1){
                        (obj->end->population)--;
                        obj->end->nation = obj->nation;
                        obj->end->trigered = false;
                    }
                    else{
                        (obj->end->population)-=2;
                    }
                }
                else {
                    (obj->end->population)--;
                }
            }
        }
    }
}

void Spaceship_render_n (struct Spaceship* obj , SDL_Renderer* renderer , SDL_Texture **spaceshiptextures){
    for(int i = 0 ; i < SPACESHIP_MAX ; i++) {
        if((obj+i)->moving){
            Spaceship_movement(obj+i , renderer , spaceshiptextures);
        }
    }
}