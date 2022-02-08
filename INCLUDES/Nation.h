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
};

void Nation_alloc (struct Nation* nations , int howmanynations , int basecolor) {
    (nations)->id = 0;
    (nations)->color = 0;
    (nations)->armytexture = 0;
    (nations)->potion = 0;
    (nations)->potiontime = 0;
    nations->alive = false;

    
    for (int i = 1 ; i < NATION_MAX - 1 ; i++) {
        if (i<howmanynations+1) (nations+i)->alive = true;
        else (nations+i)->alive = false;
        
        (nations+i)->id = i;
        (nations+i)->color = (i+basecolor-1)%4 + 1;
        (nations+i)->armytexture = 0;
        (nations+i)->potion = 0;
        (nations+i)->potiontime = 0;
    }

    (nations + NATION_MAX - 1)->id = 0;
    (nations + NATION_MAX - 1)->color = -1;
    (nations + NATION_MAX - 1)->armytexture = 0;
    (nations + NATION_MAX - 1)->potion = 0;
    (nations + NATION_MAX - 1)->potiontime = 0;
    (nations + NATION_MAX - 1)->alive = false;
}
