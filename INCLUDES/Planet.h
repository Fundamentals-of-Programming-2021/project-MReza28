#include "Main_includes.h"
#include "Nation.h"

struct Planet {
    int id;
    struct Nation* nation;
    SDL_Rect rect;

    int x;
    int y;
    double angle;

    int population;
    int typeoftexture;
};

int Planet_dis_finder (struct Planet A , struct Planet B){
    return Distance_2D(A.x , A.y , B.x , B.y);
}

void Planet_dis_finder_n (int howmany , struct Planet* planets , int distances[PLANET_MAX][PLANET_MAX]) {
    for(int i = 0 ; i < howmany ; i++){
        for (int j = 0 ; j < howmany ; j++)
        {
            distances[i][j] = Planet_dis_finder( (*(planets+i)) , (*(planets + j)) );
        }
    }
}

bool Planet_dis_checker (struct Planet A , struct Planet B){
    if(Planet_dis_finder(A ,B) < PLANET_MIN_DIS){
        return false;
    }
    return true;
}

bool Planet_dis_checker_n (int howmany , struct Planet* A , struct Planet B){
    for (int i = 0; i < howmany; i++)
    {
        if(!Planet_dis_checker(*(A+i) , B)){
            return false;
        }
    }
    return true;
}

void Planet_alloc (int howmanyplayable , int howmanynations , int howmanyvoidplanets , struct Planet* planets , struct Nation* nations) {
    srand(time(0));
    for (int i = 0; i < howmanyplayable + howmanyvoidplanets ; i++)
    {
        (planets+i)->id = i;
        
        //creating white planets and void planets
        if(i < howmanynations) (planets+i)->nation = (nations+i+1);
        else if(i < howmanyplayable) (planets+i)->nation = nations;
        else (planets+i)->nation = (nations + NATION_MAX-1);

        (planets+i)->population = PLANET_POPULATION;
        (planets+i)->angle = (rand()%360);
        /*can add a random rotation speed*/
        (planets+i)->typeoftexture = 0;

        //random planet size
        (planets+i)->rect.h = PLANET_MIN_R + ((rand())%(PLANET_MAX_R - PLANET_MIN_R));
        //not random planet size
        //(planets+i)->rect.h = PLANET_MIN_R;
        (planets+i)->rect.w = (planets+i)->rect.h;

        while (true)
        {
            (planets+i)->x = GAME_W_S + (rand()%(GAME_W_E - GAME_W_S));
            (planets+i)->y = GAME_H_S + (rand()%(GAME_H_E - GAME_H_S));
            if(Planet_dis_checker_n(i , planets , *(planets+i))) break;
        }

        (planets+i)->rect.x = (planets+i)->x - ((planets+i)->rect.h)/2;
        (planets+i)->rect.y = (planets+i)->y - ((planets+i)->rect.h)/2;

        /*check if alghoritem last long try another pattern fro the brginning*/
    }
}

void Planet_render (struct Planet* obj , SDL_Renderer* renderer , SDL_Texture **planettextures) {
    SDL_RenderCopyEx(renderer , *(planettextures + obj->typeoftexture) /*adding color of nation*/ , NULL , &(obj->rect) , obj->angle , NULL , SDL_FLIP_NONE);
    obj->angle += PLANET_ROTATION_SPEED;
    if(obj->angle > 360) obj->angle-=360.0;
    
    /*adding potion effect*/
}