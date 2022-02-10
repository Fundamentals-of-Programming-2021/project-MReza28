#include "Main_includes.h"
#include "Load.h"

bool Menu_continue (SDL_Renderer* renderer) {
    
}

bool Menu_newgame (SDL_Renderer* renderer) {
    srand(time(0));
    //font
    SDL_Color Textcolor = TEXT_COLOR;
    TTF_Font* Maintext = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 40);
    TTF_Font* Othertext = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 24);
    TTF_Font* numbertext = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 60);
    char Username[NAME_MAX_L] = {'\0'};
    int Indexusername = 0;




    //rects
    SDL_Rect NG[5];
    //username
    NG[0].y = 200;
    //username text upper
    NG[1].y = 150;
    SDL_Texture* Username_up;
    texttotexture("Type Your Name To Start Game" , Othertext , Textcolor , &Username_up , renderer);
    SDL_QueryTexture(Username_up , NULL , NULL , &NG[1].w , &NG[1].h);
    NG[1].x = 1920/2 - NG[1].w/2;
    //spaceship place
    NG[4].w = 240;
    NG[4].h = NG[4].w;
    NG[4].y = 320+200 - NG[4].w/2;
    NG[4].x = 960 - NG[4].w/2;



    


    //buttons
    struct Button bstart;
    SDL_Texture* starttex[3];
    Creattexturefrompng("IMAGES/Menu/bstartt.png" , starttex , renderer);
    Creattexturefrompng("IMAGES/Menu/bstartf.png" , starttex+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/bstartc.png" , starttex+2 , renderer);
    Button_creat(&bstart , 1920/2 - 64 , 900 , starttex);

    struct Button barrows[8];
    int yzero = 320;
    int yone = 400;

    SDL_Texture* arrowstex[12];
    Creattexturefrompng("IMAGES/Menu/upt.png" , arrowstex , renderer);
    Creattexturefrompng("IMAGES/Menu/upf.png" , arrowstex+1 , renderer);
    Creattexturefrompng("IMAGES/Menu/upc.png" , arrowstex+2 , renderer);

    Creattexturefrompng("IMAGES/Menu/rightt.png" , arrowstex+3 , renderer);
    Creattexturefrompng("IMAGES/Menu/rightf.png" , arrowstex+4 , renderer);
    Creattexturefrompng("IMAGES/Menu/rightc.png" , arrowstex+5 , renderer);

    Creattexturefrompng("IMAGES/Menu/downt.png" , arrowstex+6 , renderer);
    Creattexturefrompng("IMAGES/Menu/downf.png" , arrowstex+7 , renderer);
    Creattexturefrompng("IMAGES/Menu/downc.png" , arrowstex+8 , renderer);

    Creattexturefrompng("IMAGES/Menu/leftt.png" , arrowstex+9 , renderer);
    Creattexturefrompng("IMAGES/Menu/leftf.png" , arrowstex+10 , renderer);
    Creattexturefrompng("IMAGES/Menu/leftc.png" , arrowstex+11 , renderer);

    Button_creat(barrows , 480-36 , yzero , arrowstex);
    Button_creat(barrows+1 , 480-36 , yzero+yone , arrowstex+6);

    Button_creat(barrows+2 , 960-36 , yzero , arrowstex);
    Button_creat(barrows+3 , 960-36 , yzero+yone , arrowstex+6);
    Button_creat(barrows+4 , 960- yone/2 -18 , (yzero+yzero+yone)/2-18 , arrowstex+9);
    Button_creat(barrows+5 , 960+ yone/2 -18 , (yzero+yzero+yone)/2-18 , arrowstex+3);

    Button_creat(barrows+6 , 480+960-36 , yzero , arrowstex);
    Button_creat(barrows+7 , 480+960-36 , yzero+yone , arrowstex+6);

    



    //spaceship creat
    SDL_Surface* Spaceshipssurface[SPACESHIP_TYPES*7] = {
        IMG_Load("IMAGES/Spaceships/1R.png") , IMG_Load("IMAGES/Spaceships/1B.png") , IMG_Load("IMAGES/Spaceships/1G.png") , IMG_Load("IMAGES/Spaceships/1Y.png") ,
        IMG_Load("IMAGES/Spaceships/1Speed.png") , IMG_Load("IMAGES/Spaceships/1Slow.png") , IMG_Load("IMAGES/Spaceships/1strong.png") ,
        IMG_Load("IMAGES/Spaceships/2R.png") , IMG_Load("IMAGES/Spaceships/2B.png") , IMG_Load("IMAGES/Spaceships/2G.png") , IMG_Load("IMAGES/Spaceships/2Y.png") ,
        IMG_Load("IMAGES/Spaceships/2Speed.png") , IMG_Load("IMAGES/Spaceships/2Slow.png") , IMG_Load("IMAGES/Spaceships/2strong.png") ,
        IMG_Load("IMAGES/Spaceships/3R.png") , IMG_Load("IMAGES/Spaceships/3B.png") , IMG_Load("IMAGES/Spaceships/3G.png") , IMG_Load("IMAGES/Spaceships/3Y.png") ,
        IMG_Load("IMAGES/Spaceships/3Speed.png") , IMG_Load("IMAGES/Spaceships/3Slow.png") , IMG_Load("IMAGES/Spaceships/3strong.png")
    };
    SDL_Texture* Spaceshipstexture[SPACESHIP_TYPES*7];
    for (int i = 0; i < SPACESHIP_TYPES*7; i++)
    {
        Spaceshipstexture[i] = SDL_CreateTextureFromSurface(renderer , Spaceshipssurface[i]);
        SDL_FreeSurface(Spaceshipssurface[i]);
    }





    //variables
    int nations = 2;
    int planets = 5;
    int color = 0;
    int spstype = 0;


    //blackscreen
    SDL_Rect blackleft;
    blackleft.h = 1080;
    blackleft.w = 1920;
    blackleft.x = 0;
    blackleft.y = 0;
    int blackleftcount = 254;





    while (true)
    {
        bool breakint = false;
        SDL_Event event;
        SDL_PollEvent(&event);
        //mouse handling
        int mousex , mousey;
        Uint32 mouseb; 
        mouseb = SDL_GetMouseState(&mousex , &mousey);


        if(event.type == SDL_QUIT){
            return false;
        }
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            if(!blackingscreen(renderer)){
                    return false;
            }
            break;
        }
        //key handling
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE){
            if(Indexusername > 0){
                Username[Indexusername-1] = '\0';
                Indexusername--;
            }
        }
        else if(event.type == SDL_TEXTINPUT){
            if (Indexusername < NAME_MAX_L-1) {
                Username[Indexusername] = event.text.text[0];
                Indexusername++;
            }
        }

        int mouseon = 0;

        for (int i = 0; i < 8; i++)
        {
            if(Button_mouseon(mousex , mousey , barrows+i)) mouseon=i+1;
        }
        if(Button_mouseon(mousex , mousey , &bstart)) mouseon=9;

        if(event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN){

            switch (mouseon)
            {
            
            case 1:{
                nations++;
                nations%=4;
                break;
            }

            case 2:{
                nations--;
                if(nations<0){
                    nations=3;
                }
                if(nations+1 > planets) {
                    planets= nations+1;
                }
                break;
            }

            case 3:{
                color++;
                color%=4;
                break;
            }

            case 4:{
                color--;
                if(color<0){
                    color=3;
                }
                break;
            }

            case 5:{
                spstype++;
                spstype%=3;
                break;
            }

            case 6:{
                spstype--;
                if(spstype<0){
                    spstype=2;
                }
                break;
            }
            
            case 7:{
                planets++;
                if(planets > 10){
                    planets=nations+1;
                }
                break;
            }

            case 8:{
                planets--;
                if(planets<nations+1){
                    planets=10;
                }
                break;
            }

            case 9:{
                if(Username[0] != '\0'){
                    if(!blackingscreen(renderer)){
                        return false;
                    }
                    int k = Game_start(renderer , nations+1 , planets , 0 , spstype , color+1 , Username);
                    if(k == MNEG){
                        
                        return false;
                    }
                    else if(k == MPOS){
                        
                        breakint = true;
                    }
                }
                break;
            }
            
            }
        }

        if(breakint) break;




        SDL_RenderClear(renderer);

      
      
        //nation and etc creat
        SDL_Texture* ntex;
        SDL_Texture* ptex;

        numbertotexture(nations+1 , numbertext , Textcolor , &ntex , renderer);
        numbertotexture(planets , numbertext , Textcolor , &ptex , renderer);

        SDL_QueryTexture(ntex , NULL , NULL , &NG[2].w , &NG[2].h);
        SDL_QueryTexture(ptex , NULL , NULL , &NG[3].w , &NG[3].h);
        NG[2].x = 480 - NG[2].w/2;
        NG[3].x = 960+480 - NG[3].w/2;
        NG[2].y = (yzero+yzero+yone)/2 + 18 - NG[2].h/2;
        NG[3].y = (yzero+yzero+yone)/2 + 18 - NG[3].h/2;

        SDL_RenderCopy(renderer , ntex , NULL , &NG[2]);
        SDL_RenderCopy(renderer , ptex , NULL , &NG[3]);
        SDL_RenderCopy(renderer , Spaceshipstexture[7*spstype + color] , NULL , &NG[4]);
        
        SDL_DestroyTexture(ntex);
        SDL_DestroyTexture(ptex);


      
        //text username
        SDL_Texture* tusername;
        texttotexture(Username , Maintext , Textcolor , &tusername , renderer);
        SDL_QueryTexture(tusername , NULL , NULL , &(NG[0].w) , &(NG[0].h));
        NG[0].x = 1920/2 - NG[0].w/2;

        SDL_RenderCopy(renderer , tusername , NULL , &NG[0]);
        SDL_RenderCopy(renderer , Username_up , NULL , &NG[1]);
        SDL_DestroyTexture(tusername);

        Button_render(&bstart , renderer);

        for(int i = 0 ; i < 8 ; i++){
            Button_render(barrows+i , renderer);
        }




        //blackscreen
        if(blackleftcount > -1){
            Rectanglesetcolor(renderer , &blackleft , 0 , 0 , 0 , blackleftcount);
            SDL_RenderCopy(renderer , NULL , NULL , &blackleft);
            blackleftcount-=2;
        }

        SDL_RenderPresent(renderer);
    }





    //destoying
    TTF_CloseFont(Maintext);
    TTF_CloseFont(Othertext);
    TTF_CloseFont(numbertext);

    SDL_DestroyTexture(Username_up);
    for (int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(starttex[i]);
    }
    for (int i = 0; i < 12; i++)
    {
        SDL_DestroyTexture(arrowstex[i]);
    }
    for (int i = 0; i < SPACESHIP_TYPES*7 ; i++){
        SDL_DestroyTexture(Spaceshipstexture[i]);
    }
    
    
    return true;
}

bool Menu_score (SDL_Renderer* renderer , char SCnames[SCsaves][NAME_MAX_L] , int SCscores[SCsaves]) {
    int sorted[10];
    SCsort(SCscores , sorted);
    
    //font
    TTF_Font* Scoresfont = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 24);

    SDL_Rect renames[10];
    SDL_Rect rescores[10];

    SDL_Texture* tnames[10];
    SDL_Texture* tscores[10];

    SDL_Color textcolor = TEXT_COLOR;
    for (int i = 0; i < 10; i++)
    {
        texttotexture(SCnames[sorted[i]] , Scoresfont , textcolor , &tnames[i] , renderer);
        SDL_QueryTexture(tnames[i] , NULL , NULL , &(renames[i].w) , &(renames[i].h));
        numbertotexture(SCscores[sorted[i]] , Scoresfont , textcolor , &tscores[i] , renderer);
        SDL_QueryTexture(tscores[i] , NULL , NULL , &(rescores[i].w) , &(rescores[i].h));
        renames[i].x = 300;
        renames[i].y = i*50 + 400;
        rescores[i].x = 1920 - 300 - rescores[i].w;
        rescores[i].y = i*50 + 400;
    }

    //blackscreen
    SDL_Rect blackleft;
    blackleft.h = 1080;
    blackleft.w = 1920;
    blackleft.x = 0;
    blackleft.y = 0;
    int blackleftcount = 254;

    while (true)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT){
            return false;
        }
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            if(!blackingscreen(renderer)){
                return false;
            }
            break;
        }
        
        SDL_RenderClear(renderer);

        for (int i = 0; i < 10; i++)
        {
            SDL_RenderCopy(renderer , tnames[i] , NULL , &renames[i]);
            SDL_RenderCopy(renderer , tscores[i] , NULL , &rescores[i]);
        }

        //blackscreen
        if(blackleftcount > -1){
            Rectanglesetcolor(renderer , &blackleft , 0 , 0 , 0 , blackleftcount);
            SDL_RenderCopy(renderer , NULL , NULL , &blackleft);
            blackleftcount-=2;
        }

        SDL_RenderPresent(renderer);
    }


    //free textures
    for(int i = 0 ; i < 10 ; i++){
        SDL_DestroyTexture(tnames[i]);
        SDL_DestroyTexture(tscores[i]);
    }
    TTF_CloseFont(Scoresfont);

    return true;
}

bool Menu_load (SDL_Renderer* renderer) {

}