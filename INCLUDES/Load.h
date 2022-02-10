#include "Main_includes.h"
#include "Game.h"

int Load_Game (SDL_Renderer* renderer , char* fileaddress) {
    long long int counter = 1;
    int score;
    bool win;
    srand(time(0));

    FILE* Load = fopen(fileaddress , "r");
    char username[NAME_MAX_L];
    fscanf(Load , "%s" , username);

    int howmanynations , howmanyplanets , howmanyvoidplanets , playercolor , playerspaceshiptype;
    fscanf(Load , "%d %d %d %d %d" , 
        &howmanynations ,
        &howmanyplanets ,
        &howmanyvoidplanets ,
        &playercolor ,
        &playerspaceshiptype
    );


    //creating backgrounfd
    SDL_Texture* background;
    Creattexturefrompng("IMAGES/background.jpg" , &background , renderer);
    
    
    //creating nations
    struct Nation Nations[NATION_MAX];
    for(int i = 0 ; i < NATION_MAX ; i++){
        fscanf(Load , "%d %d %d %d %d %d %d\n" ,
            &(Nations[i].alive) ,
            &(Nations[i].armytexture) ,
            &(Nations[i].color) ,
            &(Nations[i].id) ,
            &(Nations[i].name) ,
            &(Nations[i].potion) ,
            &(Nations[i].potiontime)
        );
    }


    char usernames[NAME_MAX][NAME_MAX_L] = {"you" , "LetMeMakeNewOne" , "mrb82228" , "Dream" , " DUDE0011" , "StrongAI" , "BOT05" , "YouShallDie" , "ARASH" , "HolyFatherJose"};
    strcpy(usernames[0] , username);

    Nations[1].armytexture = playerspaceshiptype;

    //creating planets
    struct Planet Planets[PLANET_MAX];
    for(int i = 0 ; i < howmanyplanets + howmanyvoidplanets ; i++) {
        int temp;
        fscanf(Load , "%lf %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n" ,
            &(Planets[i].angle) ,
            &(Planets[i].id) ,
            &temp , //(Planets[i].nation->id)

            &(Planets[i].population) ,
            &(Planets[i].typeoftexture) ,

            &(Planets[i].x) ,
            &(Planets[i].y) ,

            &(Planets[i].rect.x) ,
            &(Planets[i].rect.y) ,
            &(Planets[i].rect.w) ,
            &(Planets[i].rect.h) ,

            &(Planets[i].poprect.x) ,
            &(Planets[i].poprect.y) ,
            
            &(Planets[i].potrect.x) ,
            &(Planets[i].potrect.y) ,

            &(Planets[i].namrect.x) ,
            &(Planets[i].namrect.y)
        );
        Planets[i].trigered = false;
        Planets[i].mouseon = false;
        (Planets[i].nation) = (Nations+temp);
    }


    SDL_Surface* Planetssurfaces[PLANET_TYPES + PLANET_TYPES_V+ 1] = {
        IMG_Load("IMAGES/Planets/a1.png") , IMG_Load("IMAGES/Planets/a2.png") , IMG_Load("IMAGES/Planets/a3.png") , IMG_Load("IMAGES/Planets/a4.png") , IMG_Load("IMAGES/Planets/a5.png") , IMG_Load("IMAGES/Planets/a6.png") ,
        IMG_Load("IMAGES/Planets/p1.png") , IMG_Load("IMAGES/Planets/p2.png") , IMG_Load("IMAGES/Planets/p3.png") , IMG_Load("IMAGES/Planets/p4.png") , IMG_Load("IMAGES/Planets/p5.png") , IMG_Load("IMAGES/Planets/p6.png") ,
        IMG_Load("IMAGES/Planets/p7.png") , IMG_Load("IMAGES/Planets/p8.png") , IMG_Load("IMAGES/Planets/p9.png") , IMG_Load("IMAGES/Planets/p10.png") , IMG_Load("IMAGES/Planets/p11.png") , IMG_Load("IMAGES/Planets/p12.png") ,
        IMG_Load("IMAGES/Planets/cab.png")
    };
    SDL_Texture* Planetstextures[PLANET_TYPES + PLANET_TYPES_V + 1];
    for (int i = 0; i < PLANET_TYPES + PLANET_TYPES_V + 1 ; i++)
    {
        Planetstextures[i] = SDL_CreateTextureFromSurface(renderer , Planetssurfaces[i]);
    }
    for (int i = 0; i < PLANET_TYPES + PLANET_TYPES_V + 1 ; i++)
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

    fscanf(Load , "%d" , &index_spaceships);

    for(int i = 0 ; i < index_spaceships ; i++){
        int temp[3];
        fscanf(Load , "%lf %d %d %d %d %d %d %d %d %d %d %d %d\n" ,
            &(Spaceships[i].angle) ,
            &(Spaceships[i].lifetime) ,

            &temp[0] , //(Spaceships[i].start->id) ,
            &temp[1] , //(Spaceships[i].end->id) ,
            &temp[2] , //(Spaceships[i].nation->id) ,

            &(Spaceships[i].pathlength) ,
            &(Spaceships[i].typeoftexture) ,

            &(Spaceships[i].rect.x) ,
            &(Spaceships[i].rect.y) ,
            &(Spaceships[i].rect.w) , 
            &(Spaceships[i].rect.h) ,

            &(Spaceships[i].x) ,
            &(Spaceships[i].y)
        );
        Spaceships[i].moving = true;
        Spaceships[i].nation = (Nations+temp[2]);
        Spaceships[i].start = (Planets+temp[0]);
        Spaceships[i].end = (Planets+temp[1]);
    }


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
    

    
    //creating attacka
    struct Attack Attacks[ATTACK_MAX];
    int index_attacks = 0;
    Attack_alloc(Attacks);

    fscanf(Load , "%d" , &index_attacks);

    for(int i = 0 ; i < index_attacks ; i++){
        int temp[3];
        fscanf(Load , "%d %d %d %d %d %d\n" ,
            &temp[0] ,  //(Attacks[i].start->id) ,
            &temp[1] ,  //(Attacks[i].end->id) ,
            &temp[2] ,  //(Attacks[i].nation->id) ,
            &(Attacks[i].population) ,
            &(Attacks[i].countdown)
        );
        Attacks[i].attacking = true;
        Attacks[i].nation = (Nations+temp[2]);
        Attacks[i].start = (Planets+temp[0]);
        Attacks[i].end = (Planets+temp[1]);
    }

    fclose(Load);

    //creating potins
    struct Potion Potions[POTION_MAX];
    int index_potions = 0;
    Potion_alloc(Potions);

    SDL_Surface* Potionssurface[5] = {
        IMG_Load("IMAGES/Potions/fast.png") , IMG_Load("IMAGES/Potions/slow.png") , IMG_Load("IMAGES/Potions/strong.png") , IMG_Load("IMAGES/Potions/fastp.png") , IMG_Load("IMAGES/Potions/cab.png")
    };
    SDL_Texture* Potionstexture[5];
    for (int i = 0; i < 5; i++)
    {
        Potionstexture[i] = SDL_CreateTextureFromSurface(renderer ,Potionssurface[i]);
        SDL_FreeSurface(Potionssurface[i]);
    }


    //creatin fonts
    TTF_Font* Populationfont = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 20);
    TTF_Font* charfont = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 14);





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
        int mousex , mousey;
        //quit handeling
        if (event.type == SDL_QUIT) return MNEG;
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
                if(!blackingscreen(renderer)){
                    return MNEG;
                }
                int k = Game_pause(renderer , username , score);
                if(k == 0){
                    TTF_CloseFont(Populationfont);
                    TTF_CloseFont(charfont);
                    for (int i = 0; i < PLANET_TYPES + PLANET_TYPES_V + 1 ; i++){
                        SDL_DestroyTexture(Planetstextures[i]);
                    }
                    SDL_DestroyTexture(background);
                    for (int i = 0; i < SPACESHIP_TYPES*7 ; i++){
                        SDL_DestroyTexture(Spaceshipstexture[i]);
                    }
                    for(int i = 0 ; i < 5 ; i++) {
                        SDL_DestroyTexture(Potionstexture[i]);
                    }
                    return MPOS;
                }

                else if(k == MNEG){
                    return MNEG;
                }
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

        for (size_t i = 0; i < movingships_n; i++)
        {
            for (int j = 0; j < movingships_n; j++)
            {
                Spaceship_dis_checker(Spaceships + movingships[i] , Spaceships + movingships[j]);
            }
        }

        //increasing population of planets
        if(counter%POPULATION_SPEED == 0) {
            for (int i = 0; i < howmanyplanets ; i++)
            {
                if(Planets[i].population < POPULATION_CAB && Planets[i].nation->alive){
                    Planets[i].population++;
                    if(Planets[i].nation->potion == 4){
                        Planets[i].population++;
                    }
                }
                else if(Planets[i].nation->potion == 5){
                    Planets[i].population++;
                }
            }
        }

        //nations population handling
        for (int i = 0; i < NATION_MAX; i++)
        {
            if(Nations[i].alive){
                Nations[i].population = 0;
            }
        }
        
        for (int i = 0; i < SPACESHIP_MAX; i++)
        {
            if(Spaceships[i].moving){
                Nations[Spaceships[i].nation->id].population++;
            }
        }
        for (int i = 0; i < ATTACK_MAX; i++)
        {
            if(Attacks[i].attacking){
                Nations[Attacks[i].nation->id].population += Attacks[i].population;
            }
        }
        for (int i = 0; i < howmanyplanets; i++)
        {
            Nations[Planets[i].nation->id].population += Planets[i].population;
        }
        
        for (int i = 1; i < 5; i++)
        {
            if(Nations[i].population == 0){
                Nations[i].alive = false;
            }
        }
        
        



        //handelinh potions
        if(counter%60==0){
            for (int i = 1 ; i < howmanynations+1 ; i++){
                if((Nations+i)->potiontime > 0){
                    (Nations+i)->potiontime--;
                    if((Nations+i)->potiontime == 0) {
                        (Nations+i)->potion = 0;
                    }
                }
            }
            //cerating potion
            if(rand()%POTION_PROB == 0) {
                Potion_Creat(Potions , &index_potions , Planets , howmanyplanets);
            }
        }


        Potion_handling(Potions , Spaceships , movingships , movingships_n);
        


        //GAME ENDING
        if(!Nations[1].alive){
            win = false;
            score = (howmanynations-5)*10;
            Game_done(username , score);
            blackingscreen(renderer);
            break;
        }
        else if(!Nations[2].alive && !Nations[3].alive && !Nations[4].alive){
            win = true;
            score = (howmanynations-1)*(20+ (20*1800)/counter);
            Game_done(username , score);
            blackingscreen(renderer);
            break;
        }




        //attack handeling
        for(int i = 0 ; i < ATTACK_MAX ; i++) Attack_handling(Attacks+i , &index_spaceships , Spaceships , Planetsdistances);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer , background , NULL , NULL);

        Spaceship_render_n(Spaceships , renderer , Spaceshipstexture);

        Potion_render(renderer , Potions , Potionstexture);

        Planet_render_n(Planets , renderer , Planetstextures , howmanyplanets+howmanyvoidplanets , Populationfont , charfont , colors , usernames);


        SDL_RenderPresent(renderer);
        counter++;

        SDL_Delay(1000/60);
    }


    //Destroying datas
    TTF_CloseFont(Populationfont);
    TTF_CloseFont(charfont);

    for (int i = 0; i < PLANET_TYPES + PLANET_TYPES_V + 1 ; i++){
        SDL_DestroyTexture(Planetstextures[i]);
    }
    SDL_DestroyTexture(background);
    for (int i = 0; i < SPACESHIP_TYPES*7 ; i++){
        SDL_DestroyTexture(Spaceshipstexture[i]);
    }
    for(int i = 0 ; i < 5 ; i++) {
        SDL_DestroyTexture(Potionstexture[i]);
    }


    //win or lose
    TTF_Font* gamedonefont = TTF_OpenFont("IMAGES/Fonts/calibri.ttf" , 50);

    SDL_Texture* numtex;
    SDL_Texture* texttex;
    SDL_Color textcolor = TEXT_COLOR;

    numbertotexture(score , gamedonefont , textcolor , &numtex , renderer);
    if(win) texttotexture("YOU WON" , gamedonefont , textcolor , &texttex , renderer);
    else texttotexture("GAME OVER" , gamedonefont , textcolor , &texttex , renderer);

    SDL_Rect scccc;
    SDL_Rect title;

    SDL_QueryTexture(numtex , NULL , NULL , &scccc.w , &scccc.h);
    SDL_QueryTexture(texttex , NULL , NULL , &title.w , &title.h);

    scccc.x = 960 - scccc.w/2;
    scccc.y = 700;
    title.x = 960 - title.w/2;
    title.y = 400;

    blackleftcount = 254;

    while (blackleftcount > 0)
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer , numtex , NULL , &scccc);
        SDL_RenderCopy(renderer , texttex , NULL , &title);

        //blackscreen
        if(blackleftcount > -1){
            Rectanglesetcolor(renderer , &blackleft , 0 , 0 , 0 , blackleftcount);
            SDL_RenderCopy(renderer , NULL , NULL , &blackleft);
            blackleftcount-=3;
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(2000);
    blackingscreen(renderer);
    
    SDL_DestroyTexture(numtex);
    SDL_DestroyTexture(texttex);
    TTF_CloseFont(gamedonefont);
    return MPOS;
}