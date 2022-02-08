#include "Main_includes.h"
#include "Game.h"

bool Menu_continue (SDL_Renderer* renderer) {
    
}

bool Menu_newgame (SDL_Renderer* renderer) {
    //font
    SDL_Color Textcolor = TEXT_COLOR;
    TTF_Font* Maintext = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 40);
    TTF_Font* Othertext = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 24);
    char Username[NAME_MAX_L] = {'\0'};
    int Indexusername = 0;


    //rects
    SDL_Rect NG[5];
    //username
    NG[0].y = 200;
    //username text upper
    NG[1].y = 150;
    SDL_Texture* Username_up;
    texttotexture("Type Your Name" , Othertext , Textcolor , &Username_up , renderer);
    SDL_QueryTexture(Username_up , NULL , NULL , &NG[1].w , &NG[1].h);
    NG[1].x = 1920/2 - NG[1].w/2;

    


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
            blackingscreen(renderer);
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

        SDL_RenderClear(renderer);


        //text username
        SDL_Texture* tusername;
        texttotexture(Username , Maintext , Textcolor , &tusername , renderer);
        SDL_QueryTexture(tusername , NULL , NULL , &(NG[0].w) , &(NG[0].h));
        NG[0].x = 1920/2 - NG[0].w/2;
        SDL_RenderCopy(renderer , tusername , NULL , &NG[0]);
        SDL_RenderCopy(renderer , Username_up , NULL , &NG[1]);
        SDL_DestroyTexture(tusername);





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
    SDL_DestroyTexture(Username_up);
    return true;
}

bool Menu_score (SDL_Renderer* renderer , char SCnames[10][NAME_MAX_L] , int SCscores[10]) {
    //font
    TTF_Font* Scoresfont = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 24);

    SDL_Rect renames[10];
    SDL_Rect rescores[10];

    SDL_Texture* tnames[10];
    SDL_Texture* tscores[10];

    SDL_Color textcolor = TEXT_COLOR;
    for (int i = 0; i < 10; i++)
    {
        texttotexture(SCnames[i] , Scoresfont , textcolor , &tnames[i] , renderer);
        SDL_QueryTexture(tnames[i] , NULL , NULL , &(renames[i].w) , &(renames[i].h));
        numbertotexture(SCscores[i] , Scoresfont , textcolor , &tscores[i] , renderer);
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
            blackingscreen(renderer);
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