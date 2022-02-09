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