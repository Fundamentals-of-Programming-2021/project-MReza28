#include "Main_includes.h"
#include "Distance.h"

//first Nation is white and the last is void

struct Nation
{
    bool alive;
    int color;
    int armytexture;
    int potion;
    int potiontime;
};

void Nation_alloc (struct Nation* nations , int howmanynations) {
    for (int i = 0 ; i < NATION_MAX ; i++) {
        if (i<howmanynations+1) (nations+i)->alive = true;
        else (nations+i)->alive = false;

        (nations+i)->color = i;
        (nations+i)->armytexture = 0;
        (nations+i)->potion = 0;
        (nations+i)->potiontime = 0;
    }
    
    (nations+NATION_MAX-1)->color = -1;
    (nations+NATION_MAX-1)->alive = false;
    nations->alive = false;
}
