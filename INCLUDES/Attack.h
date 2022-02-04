#include "Main_includes.h"
#include "Spaceship.h"

struct Attack
{
    bool attacking;
    
    int population;
    int reamingpopulation;

    struct Nation* nation;
    struct Planet* start;
    struct Planet* end;
};
