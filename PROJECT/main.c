#include "Main_includes.h"
#include "Menu.h"

#ifdef main
#undef main
#endif

int main (int argc, char *argv[]) {
    bool Running = true;

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
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
    TTF_Init();
    /*if(Running){
        Running = Menu_start(rend);
    }*/





    /*TTF_Font * font = TTF_OpenFont("Arial.ttf", 30);
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
    }*/


    /*if(Running){
        Running = Menu_main(rend);
    }*/

    if(Running) {
        Running = Game_start(rend , 4 , 6 , 2);
    }


    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}