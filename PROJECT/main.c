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
    int p = 4;
    int v = 4;

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
    Nations[5].color = 0;



    TTF_Init();

    TTF_Font * font = TTF_OpenFont("Arial.ttf", 30);
    SDL_Surface *background = SDL_LoadBMP("");
    SDL_Surface *rank_s[10];
    SDL_Texture *rank[10];

    int texW[10];
    int texH[10];
    SDL_Rect jaigah[10];
    SDL_Color grey={100,100,100};
    for (int i = 0; i < 10; i++){
        rank_s[i] = TTF_RenderText_Solid(font , "salam ", grey);
        rank[i] = SDL_CreateTextureFromSurface(rend, rank_s[i]);
        texW[i] = 0;
        texH[i] = 0;
        SDL_QueryTexture(rank[0], NULL, NULL, &texW[i], &texH[i]);

        jaigah[i].x = (1000 - rank_s[i]->w) / 2;
        jaigah[i].y = 150 + 50 * i;
        jaigah[i].w = texW[i];
        jaigah[i].h = texH[i];
    }



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

        for(int i = 0 ; i < p+v ; i++){
            Planet_render((Planets+i) , rend , tex);
        }

        for (int i = 0 ; i < 10; i++){
            SDL_RenderCopy(rend, rank[i], NULL, &jaigah[i]);
        }
        
        SDL_RenderPresent(rend);
        SDL_Delay(1000/60);
    }



    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}