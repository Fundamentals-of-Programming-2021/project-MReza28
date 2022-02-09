#include "Main_includes.h"
#include "Spaceship.h"

struct Attack
{
    bool attacking;
    
    int population;
    int countdown;

    struct Nation* nation;
    struct Planet* start;
    struct Planet* end;
};

void Attack_alloc (struct Attack* attacks){
    for (int i = 0; i < ATTACK_MAX; i++)
    {
        (attacks+i)->attacking = false;

        (attacks+i)->population = 0;
        (attacks+i)->countdown = 0;
    }
}

void Attack_creat (struct Attack* attack , struct Planet* start , struct Planet* end){
    if(start->population > 0) {
        attack->attacking = true;
        
        attack->nation = start->nation;
        attack->start = start;
        attack->end = end;

        /*can also change code to attack and reduse planet popluation one by one in attaking function and also here*/

        attack->population = start->population;
        attack->countdown = 0;
        start->population = 0;
    }
}

void Attack_handling (struct Attack* attack , int* indexspaceship , struct Spaceship* spaceships , int PlanetsDistances[PLANET_MAX][PLANET_MAX]) {
    if(attack->attacking){
        if(attack->countdown < 0){
            Spaceship_creat(attack->nation , attack->start , attack->end , (spaceships + *indexspaceship) , PlanetsDistances);
            (*indexspaceship)++;
            (*indexspaceship)%=SPACESHIP_MAX;
            (attack->population)--;

            if((attack->population) == 0){
                attack->attacking = false;
            }
            else {
                attack->countdown = EXITING_COUNTER;
            }
        }
        else {
            (attack->countdown)-=2;
            
            if(attack->nation->potion == 2){
                (attack->countdown)++;
            }
            else if(attack->nation->potion == 1){
                (attack->countdown)-=2;
            }
        }
    }
}

struct Potion
{
    bool show;
    int type;
    
    int life;

    SDL_Rect prect;
    int x;
    int y;
};

void Potion_alloc (struct Potion* potions) {
    for(int i = 0 ; i < POTION_MAX ; i++){
        (potions+i)->show = false;
        (potions+i)->type = 0;
    }
}

void Potion_Creat (struct Potion* potions , int* pindex , struct Planet* planets , int howmanyplanets)
{
    (potions+*pindex)->show = true;
    (potions+*pindex)->type = rand()%5+1;
    (potions+*pindex)->life = POTION_LIFE;

    srand(time(0));
    int s , e;
    
    s = rand()%howmanyplanets;
    while(true){
        e = rand()%howmanyplanets;
        if(e!=s) break;
    }

    int place = (rand()%8) + 4;
    (potions+*pindex)->x = (planets+s)->x + (((planets+e)->x - (planets+s)->x)*place)/15;
    (potions+*pindex)->y = (planets+s)->y + (((planets+e)->y - (planets+s)->y)*place)/15;

    (potions+(*pindex))->prect.x = (potions+(*pindex))->x - 24;
    (potions+(*pindex))->prect.y = (potions+(*pindex))->y - 24;

    (potions+*pindex)->prect.w = 48;
    (potions+*pindex)->prect.h = 48;

    (*pindex)++;
    if(*pindex == POTION_MAX){
        (*pindex)%=POTION_MAX;
    }
};

void Potion_render(SDL_Renderer* renderer , struct Potion* potions , SDL_Texture** ptextures) {
    for (int i = 0; i < POTION_MAX; i++)
    {
        if((potions+i)->show) {
            SDL_RenderCopy(renderer , *(ptextures+(potions+i)->type-1) , NULL , &(potions+i)->prect);
        }
    }
}

void Potion_handling (struct Potion* potions , struct Spaceship* spacesships , int* movingsps , int howmanysps) {
    for (int i = 0; i < howmanysps; i++)
    {
        for(int j = 0 ; j < POTION_MAX ; j++){
            if( (potions+j)->show && (spacesships + *(movingsps + i))->nation->potion == 0 && Distance_1D((spacesships+(*(movingsps+i)))->x , (spacesships+(*(movingsps+i)))->y , (potions+j)->x , (potions+j)->y) < Potion_SPSH_MIN_DIS){
                (potions+j)->show = false;
                (spacesships+*(movingsps + i))->nation->potion = (potions+j)->type;
                (spacesships+*(movingsps + i))->nation->potiontime = Potion_time;
            }   
        }
    }
}