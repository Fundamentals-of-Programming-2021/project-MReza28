#include "Main_includes.h"
#include "Premenu.h"

bool Game_start (SDL_Renderer* renderer , int howmanynations , int howmanyplanets , int howmanyvoidplanets) {
    //creating backgrounfd
    SDL_Texture* background;
    Creattexturefrompng("IMAGES/background.jpg" , &background , renderer);
    
    
    //creating nations
    struct Nation Nations[NATION_MAX];
    Nation_alloc(Nations , howmanynations);

    
    
    //creating planets
    struct Planet Planets[PLANET_MAX];
    Planet_alloc(howmanyplanets , howmanynations , howmanyvoidplanets , Planets , Nations);

    SDL_Surface* Planetssurfaces[18] = {
        IMG_Load("IMAGES/Planets/a1.png") , IMG_Load("IMAGES/Planets/a2.png") , IMG_Load("IMAGES/Planets/a3.png") , IMG_Load("IMAGES/Planets/a4.png") , IMG_Load("IMAGES/Planets/a5.png") , IMG_Load("IMAGES/Planets/a6.png") ,
        IMG_Load("IMAGES/Planets/p1.png") , IMG_Load("IMAGES/Planets/p2.png") , IMG_Load("IMAGES/Planets/p3.png") , IMG_Load("IMAGES/Planets/p4.png") , IMG_Load("IMAGES/Planets/p5.png") , IMG_Load("IMAGES/Planets/p6.png") ,
        IMG_Load("IMAGES/Planets/p7.png") , IMG_Load("IMAGES/Planets/p8.png") , IMG_Load("IMAGES/Planets/p9.png") , IMG_Load("IMAGES/Planets/p10.png") , IMG_Load("IMAGES/Planets/p11.png") , IMG_Load("IMAGES/Planets/p12.png")
    };
    SDL_Texture* Planetstextures[PLANET_TYPES + PLANET_TYPES_V];
    for (int i = 0; i < PLANET_TYPES + PLANET_TYPES_V ; i++)
    {
        Planetstextures[i] = SDL_CreateTextureFromSurface(renderer , Planetssurfaces[i]);
    }
    for (int i = 0; i < PLANET_TYPES + PLANET_TYPES_V; i++)
    {
        SDL_FreeSurface(Planetssurfaces[i]);
    }
    

    //creating distances
    int Planetsdistances[PLANET_MAX][PLANET_MAX];
    Planet_dis_finder_n(howmanyplanets , Planets , Planetsdistances);

    
    
    //creatin splaceships
    struct Spaceship Spaceships[SPACESHIP_MAX];
    int index_spaceships;
    Spaceship_alloc(Spaceships);

    
    
    //creating attacka
    struct Attack Attacks[ATTACK_MAX];
    int index_attacks;
    Attack_alloc(Attacks);

    

    //creatin fonts
    TTF_Font* Populationfont = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 20);
    
    
    
    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return false;
            }
        }
        
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer , background , NULL , NULL);
        Planet_render_n(Planets , renderer , Planetstextures , howmanyplanets+howmanyvoidplanets , Populationfont);

        SDL_RenderPresent(renderer);
    }
    




    //Destroyin datas
    TTF_CloseFont(Populationfont);

    return true;
}