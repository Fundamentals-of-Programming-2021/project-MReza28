#include "Main_includes.h"
#include "Menuparts.h"


bool Menu_main (SDL_Renderer* renderer){
    //creating game logo
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
    struct Button bloadmap;
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

    Creattexturefrompng("IMAGES/Menu/blmt.png" , textures , renderer);
    Creattexturefrompng("IMAGES/Menu/blmf.png" , textures+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/blmc.png" , textures+2 , renderer);
    Button_creat(&bloadmap , 98 , 650 , textures);

    Creattexturefrompng("IMAGES/Menu/bst.png" , textures , renderer);
    Creattexturefrompng("IMAGES/Menu/bsf.png" , textures+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/bsc.png" , textures+2 , renderer);
    Button_creat(&bscores , 100 , 700 , textures);

    Creattexturefrompng("IMAGES/Menu/bet.png" , textures , renderer);
    Creattexturefrompng("IMAGES/Menu/bef.png" , textures+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/bec.png" , textures+2 , renderer);
    Button_creat(&bexit , 100 , 900 , textures);



    //creat black rects
    SDL_Rect blackleft;
    int blackleftcount = 254;

    SDL_Rect blackup;
    int blackupcount = -1;


    
    ////exeracting datas


    //extracting scores
    char SCnames[10][NAME_MAX_L];
    int SCscores[10];
    Exrtactingscore(SCnames , SCscores);

    blackup.h = 400;
    blackup.w = 1000;
    blackup.x = 500;
    blackup.y = 50;

    blackleft.h = 500;
    blackleft.w = 300;
    blackleft.x = 100;
    blackleft.y = 500;
    //extracting continue


    //extracting saves


    //extracting maps



    while (true)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        int mousex , mousey;
        //quit handeling
        if (event.type == SDL_QUIT) return false;
        //mouse handling
        Uint32 mouseb; 
        mouseb = SDL_GetMouseState(&mousex , &mousey);

        int mouseon = 0;

        if(Button_mouseon(mousex , mousey , &bcontinue)) mouseon = 1;
        if(Button_mouseon(mousex , mousey , &bnewgame)) mouseon = 2;
        if(Button_mouseon(mousex , mousey , &bload)) mouseon = 3;
        if(Button_mouseon(mousex , mousey , &bscores)) mouseon = 4;
        if(Button_mouseon(mousex , mousey , &bexit)) mouseon = 5;
        if(Button_mouseon(mousex , mousey , &bloadmap)) mouseon = 6;
        
        if(event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN){
            //blacking screen
            if(mouseon != 0){
                if(!blackingscreen(renderer)){
                    return false;
                }
                blackleftcount = 254;
                blackupcount = 254;
            }

            switch (mouseon)
            {
            case 1:
            {
                if(Load_Game(renderer , "DATA/continue/save.txt") == MNEG) {
                    return false;
                }
                Exrtactingscore(SCnames , SCscores);
                break;
            }
            
            case 2:
            {
                if(!Menu_newgame(renderer)) {
                    return false;
                }     
                break;
            }
            
            case 3:
            {
                if(Load_Game(renderer , "DATA/games/save.txt") == MNEG) {
                    return false;
                }
                Exrtactingscore(SCnames , SCscores);
                break;
            }
            

            case 4:
            {
                if(!Menu_score(renderer , SCnames , SCscores)) {
                    return false;
                }
                Exrtactingscore(SCnames , SCscores);
                break;
            }

            case 5:
            {
                return false; 
                break;
            }

            case 6:
                if(Load_Game(renderer , "DATA/maps/save.txt") == MNEG) {
                    return false;
                }
                Exrtactingscore(SCnames , SCscores);
                break;
            }

                blackup.h = 400;
                blackup.w = 1000;
                blackup.x = 500;
                blackup.y = 50;

                blackleft.h = 500;
                blackleft.w = 300;
                blackleft.x = 100;
                blackleft.y = 500;
        }
        
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer , texturelogo , NULL , &rectlogo);

        Button_render(&bcontinue , renderer);
        Button_render(&bnewgame , renderer);
        Button_render(&bload , renderer);
        Button_render(&bscores , renderer);
        Button_render(&bexit , renderer);
        Button_render(&bloadmap , renderer);

        //blackscreen
        if(blackleftcount > -1){
            Rectanglesetcolor(renderer , &blackleft , 0 , 0 , 0 , blackleftcount);
            SDL_RenderCopy(renderer , NULL , NULL , &blackleft);
            if(blackupcount<0){
                blackleftcount-=2;
            }
        }

        if(blackupcount > -1){
            Rectanglesetcolor(renderer , &blackup , 0 , 0 , 0 , blackupcount);
            SDL_RenderCopy(renderer , NULL , NULL , &blackup);
            blackupcount-=4;
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(1000/60);
    }
    
    
    /*free all buttons texture*/


    return true;
}