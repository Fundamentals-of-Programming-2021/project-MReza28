#include "Main_includes.h"
#include "Game.h"

bool Menu_main (SDL_Renderer* renderer){
    //creatin game logo
    SDL_Texture* texturelogo;
    SDL_Rect rectlogo;
    Creattexturefrompng("IMAGES/Menu/gamelogo2.png" , &texturelogo , renderer);
    rectlogo.h = 320;
    rectlogo.w = 740;
    rectlogo.y = 50;
    rectlogo.x = 590;


    //creatin main left buttons
    struct Button bcontinue;
    struct Button bnewgame;
    struct Button bload;
    struct Button bscores;
    struct Button bexit;

    SDL_Texture* textures[3];

    Creattexturefrompng("IMAGES/Menu/bct.png" , textures , renderer);
    Creattexturefrompng("IMAGES/Menu/bcf.png" , textures+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/bcc.png" , textures+2 , renderer);
    Button_creat(&bcontinue , 100 , 500 , textures);

    Creattexturefrompng("IMAGES/Menu/bnt.png" , textures , renderer);
    Creattexturefrompng("IMAGES/Menu/bnf.png" , textures+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/bnc.png" , textures+2 , renderer);
    Button_creat(&bnewgame , 100 , 550 , textures);

    Creattexturefrompng("IMAGES/Menu/blt.png" , textures , renderer);
    Creattexturefrompng("IMAGES/Menu/blf.png" , textures+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/blc.png" , textures+2 , renderer);
    Button_creat(&bload , 100 , 600 , textures);

    Creattexturefrompng("IMAGES/Menu/bst.png" , textures , renderer);
    Creattexturefrompng("IMAGES/Menu/bsf.png" , textures+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/bsc.png" , textures+2 , renderer);
    Button_creat(&bscores , 100 , 650 , textures);

    Creattexturefrompng("IMAGES/Menu/bet.png" , textures , renderer);
    Creattexturefrompng("IMAGES/Menu/bef.png" , textures+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/bec.png" , textures+2 , renderer);
    Button_creat(&bexit , 100 , 850 , textures);

    //creat black rects
    SDL_Rect blackleft;
    blackleft.h = 500;
    blackleft.w = 300;
    blackleft.x = 100;
    blackleft.y = 500;

    int a = 254;
    while (a > -1)
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

        SDL_RenderCopy(renderer , texturelogo , NULL , &rectlogo);

        Button_render(&bcontinue , renderer);
        Button_render(&bnewgame , renderer);
        Button_render(&bload , renderer);
        Button_render(&bscores , renderer);
        Button_render(&bexit , renderer);

        Rectanglesetcolor(renderer , &blackleft , 0 , 0 , 0 , a);
        SDL_RenderCopy(renderer , NULL , NULL , &blackleft);
        a-=2;

        SDL_RenderPresent(renderer);

        SDL_Delay(1000/60);
    }
    
    /*free all buttons texture*/


    return true;
}