#include "Main_includes.h"
#include "Attack.h"

#ifdef main
#undef main
#endif

int main (int argc, char *argv[]) {
    struct Planet A[10];
    int s[10][10];
    Planet_alloc(10 , A);
    Planet_dis_finder_n(10 , A , s);

    for (int i = 0; i < 10; i++)
    {
        printf("%d %d\n" , A[i].x , A[i].y);
    }

    struct Nation* na;
    struct Spaceship x;
    Spaceship_creat(na , &A[0] , &A[1] , &x , s);
    printf("%.2lf" , x.angle);



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

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }

    SDL_Surface *texx = IMG_Load("IMAGES/a.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend , texx);

    
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
        
        // clear the window
        SDL_RenderClear(rend);
        
        Spaceship_movement(&x);
        x.rect.w = 24;
        x.rect.h = 24;
        SDL_RenderCopyEx(rend , tex , NULL , &(x.rect) , x.angle , NULL , SDL_FLIP_NONE);

        SDL_RenderPresent(rend);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }



    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}