#include "Main_includes.h"
#include "Premenu.h"

bool Game_pause () {

}

bool Game_start (SDL_Renderer* renderer , int howmanynations , int howmanyplanets , int howmanyvoidplanets , int playerspaceshiptype , int playercolor , char* username , bool load , char* fileadress) {
    long long int counter = 0;
    
    //creating backgrounfd
    SDL_Texture* background;
    Creattexturefrompng("IMAGES/background.jpg" , &background , renderer);
    
    
    //creating nations
    struct Nation Nations[NATION_MAX];
    Nation_alloc(Nations , howmanynations , playercolor);
    char usernames[NAME_MAX][NAME_MAX_L] = {"you" , "LetMeMakeNewOne" , "mrb82228" , "Dream" , " DUDE0011" , "StrongAI" , "BOT05" , "YouShallDie" , "ARASH" , "HolyFatherJose"};
    strcpy(usernames[0] , username);

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
    int trigered = -1;
    


    //font colors
    SDL_Color colors[5] = {TEXT_COLOR , {255,0,0} , {0,150,255} , {0,255,0} , {255,255,0}};




    //creating distances
    int Planetsdistances[PLANET_MAX][PLANET_MAX];
    Planet_dis_finder_n(howmanyplanets , Planets , Planetsdistances);
    
    

    
    //creatin splaceships
    struct Spaceship Spaceships[SPACESHIP_MAX];
    int index_spaceships = 0;
    Spaceship_alloc(Spaceships);

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
    }
    for (int i = 0; i < SPACESHIP_TYPES*7 ; i++)
    {
        SDL_FreeSurface(Spaceshipssurface[i]);
    }

    


    
    //creating attacka
    struct Attack Attacks[ATTACK_MAX];
    int index_attacks = 0;
    Attack_alloc(Attacks);

    

    //creatin fonts
    TTF_Font* Populationfont = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 20);
    TTF_Font* charfont = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 14);



    /*if(load) {
        Loadgame(fileadress , &howmanynations , &howmanyplanets , &howmanyvoidplanets , &index_spaceships , &index_attacks , &playercolor , &playerspaceshiptype , Nations , Planets , Spaceships , Attacks);
        Planet_dis_finder_n(howmanyplanets , Planets , Planetsdistances);
    }*/

    
    
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

        int mouseon = -1;
        for(int i = 0 ; i < howmanyplanets ; i++) {
            if(Planet_mouseon(mousex , mousey , (Planets+i))){
                mouseon = i;
            }
        }

        if(event.type == SDL_MOUSEBUTTONDOWN){
            if((mouseon != -1) && trigered != mouseon && event.button.button == SDL_BUTTON_LEFT){
                if(trigered == -1 && (Planets+mouseon)->nation->color == playercolor) {
                    (Planets+mouseon)->trigered = true;
                    trigered = mouseon;
                }
                else {
                    Attack_creat(Attacks+index_attacks , Planets+trigered , Planets+mouseon);
                    index_attacks++;
                    index_attacks%=ATTACK_MAX;
                    (Planets+trigered)->trigered = false;
                    trigered = -1;
                }
            }
            else if (event.button.button == SDL_BUTTON_LEFT){
                (Planets+trigered)->trigered = false;
                trigered = -1;
            }
            else if(event.button.button == SDL_BUTTON_RIGHT){
                break;
            }
        }

        int movingships[SPACESHIP_MAX];
        int movingships_n = 0;

        //spaceships creash handling
        for (int i = 0; i < SPACESHIP_MAX; i++)
        {
            if(Spaceships[i].moving){
                movingships[movingships_n] = i;
                movingships_n++;
            }
        }

        //increasing population of planets
        if(counter%POPULATION_SPEED == 0) {
            for (int i = 0; i < howmanyplanets ; i++)
            {
                if(Planets[i].population < POPULATION_CAB && Planets[i].nation->alive){
                    Planets[i].population++;
                }
            }
        }
        
        for (size_t i = 0; i < movingships_n; i++)
        {
            for (int j = 0; j < movingships_n; j++)
            {
                Spaceship_dis_checker(Spaceships + movingships[i] , Spaceships + movingships[j]);
            }
        }
        

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer , background , NULL , NULL);
        
        for(int i = 0 ; i < ATTACK_MAX ; i++) Attack_handling(Attacks+i , &index_spaceships , Spaceships , Planetsdistances);

        Spaceship_render_n(Spaceships , renderer , Spaceshipstexture);

        Planet_render_n(Planets , renderer , Planetstextures , howmanyplanets+howmanyvoidplanets , Populationfont , charfont , colors , usernames);


        SDL_RenderPresent(renderer);
        counter++;

        SDL_Delay(1000/60);
    }
    

    //Savegame("DATA/hello.txt" , howmanynations , howmanyplanets , howmanyvoidplanets ,index_spaceships , index_attacks , playercolor , playerspaceshiptype , Nations , Planets , Spaceships , Attacks);



    //Destroying datas
    TTF_CloseFont(Populationfont);
    TTF_CloseFont(charfont);

    for (int i = 0; i < PLANET_TYPES + PLANET_TYPES_V ; i++){
        SDL_DestroyTexture(Planetstextures[i]);
    }
    SDL_DestroyTexture(background);
    for (int i = 0; i < SPACESHIP_TYPES*7 ; i++){
        SDL_DestroyTexture(Spaceshipstexture[i]);
    }

    return true;
}