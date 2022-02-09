#include "Main_includes.h"
#include "Distance.h"

//first Nation is white and the last is void

struct Nation
{
    int id;
    bool alive;
    int color;
    int armytexture;
    int potion;
    int potiontime;
    int population;
    int name;
};

void Nation_alloc (struct Nation* nations , int howmanynations , int basecolor) {
    srand(time(0));
    (nations)->id = 0;
    (nations)->name = -1;
    (nations)->color = 0;
    (nations)->armytexture = 0;
    (nations)->potion = 0;
    (nations)->potiontime = 0;
    (nations)->population = 0;
    (nations)->alive = false;

    
    for (int i = 1 ; i < NATION_MAX - 1 ; i++) {
        if (i<howmanynations+1) (nations+i)->alive = true;
        else (nations+i)->alive = false;
        
        (nations+i)->id = i;
        (nations+i)->color = (i+basecolor-1)%4;
        if((nations+i)->color == 0) (nations+i)->color = 4;
        (nations+i)->armytexture = rand()%3;
        (nations+i)->potion = 0;
        (nations+i)->potiontime = 0;
        (nations+i)->population = 0;
        (nations+i)->name = rand()%(NAME_MAX-1) + 1;
    }

    (nations+1)->name = 0;

    (nations + NATION_MAX - 1)->id = 0;
    (nations + NATION_MAX - 1)->name = -1;
    (nations + NATION_MAX - 1)->color = -1;
    (nations + NATION_MAX - 1)->armytexture = 0;
    (nations + NATION_MAX - 1)->potion = 0;
    (nations + NATION_MAX - 1)->potiontime = 0;
    (nations + NATION_MAX - 1)->alive = false;
    (nations + NATION_MAX - 1)->population = -1;
}
