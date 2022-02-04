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

void Planet_alloc (int howmany , struct Planet* planets) {
    for (int i = 0; i < howmany ; i++)
    {
        (planets+i)->id = i;
        (planets+i)->nation = i+1;
        //creating white nations
        if(i+1 > howmany) (planets+i)->nation = 0;
        
        (planets+i)->potion = 0;
        (planets+i)->population = PLANET_POPULATION;
        
        (planets+i)->rect.h = PLANET_H;
        (planets+i)->rect.w = PLANET_W;

        srand(time(0));
        while (true)
        {
            (planets+i)->x = GAME_W_S + (rand()%(GAME_W_E - GAME_W_S));
            (planets+i)->y = GAME_H_S + (rand()%(GAME_H_E - GAME_H_S));
            if(Planet_dis_checker_n(i , planets , *(planets+i))) break;
        }
    }
}