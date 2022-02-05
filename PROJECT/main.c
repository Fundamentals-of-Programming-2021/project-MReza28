#include "Main_includes.h"
#include "Attack.h"

#ifdef main
#undef main
#endif

int main (int argc, char *argv[]) {
    struct Nation Nations[NATION_MAX];
    struct Planet Planets[PLANET_MAX];
    
    struct Spaceship Spaceships[SPACESHIP_MAX];
    Spaceship_alloc(Spaceships);
    int indexSpaceship = 0;

    struct Attack Attacks[ATTACK_MAX];
    Attack_alloc(Attacks);
    int indexAttack = 0;

    int PlanetsDistances[PLANET_MAX][PLANET_MAX];

    int n = 1;
    int p = 10;
    int v = 0;

    Planet_alloc(p , n , v , Planets , Nations);
    Planet_dis_finder_n(p , Planets , PlanetsDistances);
    Attack_creat(Attacks , (Planets) , (Planets+1) );


    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Paint.io",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_W, WINDOW_H,0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }

    SDL_Surface* surf[2] = {IMG_Load("IMAGES/a.png") , IMG_Load("IMAGES/b.png")};
    SDL_Texture* tex[2] = {SDL_CreateTextureFromSurface(rend , surf[0]) , SDL_CreateTextureFromSurface(rend , surf[1])};

    Nations->color = 0;
    (Nations+1)->color = 1;




    int close_requested = 0;
    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close_requested = 1;
            }
        }
        SDL_RenderClear(rend);

        Attack_handling(Attacks , &indexSpaceship , Spaceships , PlanetsDistances);
        
        for(int i = 0 ; i < SPACESHIP_MAX ; i++){
            Spaceship_render(&(Spaceships[i]) , rend , tex);
        }

        for(int i = 0 ; i < p ; i++){
            Planet_render((Planets+i) , rend , tex);
        }

        SDL_RenderPresent(rend);
        SDL_Delay(1000/60);
    }



    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}