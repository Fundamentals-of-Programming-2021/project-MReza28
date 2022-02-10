#include "Main_includes.h"
#include "Attack.h"

struct Button {
    bool show;
    SDL_Rect rect;
    SDL_Texture* texture[3];
    //0:normal  1:mouse on button  2:mouse clicked
    int state;
};

void Rectanglesetcolor (SDL_Renderer* renderer , SDL_Rect* rect , Uint8 r , Uint8 g , Uint8 b , Uint8 a){
    SDL_SetRenderDrawColor(renderer , r , g , b , a);
    SDL_RenderFillRect(renderer , rect);
    SDL_SetRenderDrawColor(renderer , 0 , 0 , 0 , 255);
}

void Button_creat (struct Button* button , int x , int y , SDL_Texture* texture[3]){
    button->show = true;
    SDL_QueryTexture(texture[0] , NULL , NULL , &(button->rect.w) , &(button->rect.h));
    for (int i = 0; i < 3; i++)
    {
        button->texture[i] = texture[i];
    }
    
    button->rect.x = x;
    button->rect.y = y;
    button->state = 0;
}

void Button_render (struct Button* button , SDL_Renderer* renderer){
    if(button->show) SDL_RenderCopy(renderer , (button->texture[button->state]) , NULL , &button->rect);
}

bool Button_mouseon (int x , int y , struct Button* button) {
    if(button->rect.x-1 < x && (button->rect.x + button->rect.w)+1 > x){
        if(button->rect.y-1 < y && (button->rect.y + button->rect.h)+1 > y){
            button->state = 1;
            return true;
        }
    }
    button->state = 0;
    return false;
}

bool blackingscreen (SDL_Renderer* renderer){
    SDL_Rect blackrect;
    blackrect.x = 0;
    blackrect.y = 0;
    blackrect.w = 1920;
    blackrect.h = 1080;
    for (int i = 0; i < 30; i++)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        int mousex , mousey;
        //quit handeling
        if (event.type == SDL_QUIT) return false;

        Rectanglesetcolor(renderer , &blackrect , 0 , 0 , 0 , 21);
        SDL_RenderCopy(renderer , NULL , NULL , &blackrect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
    return true;
}




void Savegame (
    char* fileadress , int hnation , int hplanet , int hvplanet , int sindex , int aindex ,
    int playercolor ,int playerspaceshiptype , struct Nation* nations ,
    struct Planet* planets , struct Spaceship* spaceships , struct Attack* attacks
)
{
    FILE* saveslot = fopen(fileadress , "w");
    fprintf(saveslot , "%d %d %d %d %d\n" , hnation , hplanet , hvplanet , playercolor , playerspaceshiptype);
    fprintf(saveslot , "%d %d\n" , sindex , aindex );
    
    for(int i = 0 ; i < NATION_MAX ; i++) {
        fprintf(saveslot , "%d %d %d %d %d %d\n" , (nations+i)->alive , (nations+i)->armytexture , (nations+i)->color , (nations+i)->id , (nations+i)->potion , (nations+i)->potiontime);
    }

    for(int i = 0 ; i < hplanet + hvplanet ; i++) {
        fprintf(saveslot , "%lf %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n" ,
            (planets+i)->angle , (planets+i)->id /*, (planets+i)->mouseon */, (planets+i)->nation->id , 
            (planets+i)->poprect.x , (planets+i)->poprect.y , (planets+i)->poprect.w , (planets+i)->poprect.h ,
            (planets+i)->population , (planets+i)->rect.x , (planets+i)->rect.y , (planets+i)->rect.w , (planets+i)->rect.h ,
            /*(planets+i)->trigered ,*/ (planets+i)->typeoftexture , (planets+i)->x , (planets+i)->y
        );
    }

    for(int i = 0 ; i < SPACESHIP_MAX ; i++) {
        if( (spaceships+i)->moving ) 
        {
            fprintf(saveslot , "%d %lf %d %d %d %d %d %d %d %d %d %d %d %d\n" ,
                i , (spaceships+i)->angle , (spaceships+i)->end->id , (spaceships+i)->lifetime ,
                (spaceships+i)->nation->id , (spaceships+i)->pathlength ,
                (spaceships+i)->rect.x , (spaceships+i)->rect.y , (spaceships+i)->rect.w , (spaceships+i)->rect.h ,
                (spaceships+i)->start->id , (spaceships+i)->typeoftexture , (spaceships+i)->x , (spaceships+i)->y
            );
        }
    }
    
    fprintf(saveslot ,"%d\n" , 501);

    for (int i = 0 ; i < ATTACK_MAX ; i++)
    {
        if((attacks+i)->attacking){
            fprintf(saveslot , "%d %d %d %d %d %d\n" ,
                i , (attacks+i)->countdown , (attacks+i)->end->id , (attacks+i)->nation->id ,
                (attacks+i)->population , (attacks+i)->start->id
            );
        }
    }

    fprintf(saveslot ,"%d" , 502);

    fclose(saveslot);
}

void Loadgame (
    char* fileadress , int* hnation , int* hplanet , int* hvplanet , int* sindex , int* aindex ,
    int* playercolor ,int* playerspaceshiptype , struct Nation* nations ,
    struct Planet* planets , struct Spaceship* spaceships , struct Attack* attacks
    )
{
    FILE* saveslot = fopen(fileadress , "r");
    fscanf(saveslot , "%d %d %d %d %d" , hnation , hplanet , hvplanet , playercolor , playerspaceshiptype);
    fscanf(saveslot , "%d %d" , sindex , aindex );

    for(int i = 0 ; i < NATION_MAX ; i++) {
        fscanf(saveslot , "%d %d %d %d %d %d" , &((nations+i)->alive) , &((nations+i)->armytexture) , &((nations+i)->color) , &((nations+i)->id) , &((nations+i)->potion) , &((nations+i)->potiontime));
    }

    for(int i = 0 ; i < *hplanet + *hvplanet ; i++) {
        int tempnation;
        fscanf(saveslot , "%lf %d %d %d %d %d %d %d %d %d %d %d %d %d %d" ,
            &(planets+i)->angle , &(planets+i)->id , /*&(planets+i)->mouseon ,*/ &tempnation , 
            &((planets+i)->poprect.x) , &(planets+i)->poprect.y , &(planets+i)->poprect.w , &(planets+i)->poprect.h ,
            &((planets+i)->population) , &(planets+i)->rect.x , &(planets+i)->rect.y , &(planets+i)->rect.w , &(planets+i)->rect.h ,
            /*&(planets+i)->trigered ,*/ &(planets+i)->typeoftexture , &(planets+i)->x , &(planets+i)->y
        );
        (planets+i)->nation = (nations+tempnation);
    }

    while(true) {
        int i;
        fscanf(saveslot , "%d" , &i);
        if(i==501) break;

        int startid , endid , nationid;

        fscanf(saveslot , "%f %d %d %d %d %d %d %d %d %d %d %d %d" ,
                &(spaceships+i)->angle , &endid , &(spaceships+i)->lifetime ,
                &nationid , &(spaceships+i)->pathlength ,
                &(spaceships+i)->rect.x , &(spaceships+i)->rect.y , &(spaceships+i)->rect.w , &(spaceships+i)->rect.h ,
                &startid , &(spaceships+i)->typeoftexture , &(spaceships+i)->x , &(spaceships+i)->y
        );
        (spaceships+i)->start = planets+startid;
        (spaceships+i)->end = planets+endid;
        (spaceships+i)->nation = nations+nationid;
        (spaceships+i)->moving = true;
    }
    
    while (true)
    {
        int i;
        fscanf(saveslot , "%d" , &i);
        if(i==502) break;

        int startid , endid , nationid;
        if((attacks+i)->attacking){
            fscanf(saveslot , "%d %d %d %d %d" ,
                &((attacks+i)->countdown) , &endid , &nationid ,
                &((attacks+i)->population) , &startid
            );
        }
        (attacks+i)->start = planets+startid;
        (attacks+i)->end = planets+endid;
        (attacks+i)->nation = nations+nationid;
        (attacks+i)->attacking = true;
    }
    
    fclose(saveslot);
}





void Exrtactingscore (char names[SCsaves][NAME_MAX_L] , int scores[SCsaves]) {
    FILE* fscores = fopen("DATA/scores/scores.txt" , "r");
    scores[0] = 0;
    for (int i = 0; i < SCsaves; i++)
    {
        fscanf(fscores , "%[^\n]" , names[i+1]);
        if(names[i+1][0] == '`') break;
        fscanf(fscores , "%d%*c" , &scores[i+1]);
        scores[0]++;
    }
    fclose(fscores);
}

void Extractingcontinue () {

}

void Extractingsaves () {

}

void Extractingmaps () {

}






bool Menu_start (SDL_Renderer* renderer ) {

    int timecounter;
    SDL_Texture* textures[5];
    
    Creattexturefrompng("IMAGES/Menu/shariflogo.png" , &textures[0] , renderer);
    Creattexturefrompng("IMAGES/Menu/celogo.png" , &textures[1] , renderer);
    Creattexturefrompng("IMAGES/Menu/sdllogo.png" , &textures[2] , renderer);
    Creattexturefrompng("IMAGES/Menu/vscodelogo.png" , &textures[3] , renderer);
    Creattexturefrompng("IMAGES/Menu/gamelogo2.png" , &textures[4] , renderer);
    
    SDL_Rect rects[6];

    rects[0].h = 500;
    rects[1].h = 500;
    rects[0].w = 500;
    rects[1].w = 500;

    rects[0].y = 250;
    rects[1].y = 250;
    rects[0].x = 250;
    rects[1].x = 250 + 500 + 420;

    rects[2].h = 350;
    rects[3].h = 350;
    rects[2].w = 550;
    rects[3].w = 550;

    rects[2].y = 250 + 75;
    rects[3].y = 250 + 75;
    rects[2].x = 200;
    rects[3].x = 200 + 550 + 420;

    rects[4].h = 320;
    rects[4].w = 740;

    rects[4].y = 50;
    rects[4].x = 590;

    rects[5].h = 1080;
    rects[5].w = 1920;
    rects[5].x = 0;
    rects[5].y = 0;

    int a = 0;

    while (a < 650)
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

        SDL_RenderCopy(renderer , textures[0] , NULL , (rects+0) );
        SDL_RenderCopy(renderer , textures[1] , NULL , (rects+1) );
        
        if(a<255) Rectanglesetcolor(renderer , rects+5 , 0 , 0 , 0 , 255-a);
        else if(a>394) Rectanglesetcolor(renderer , rects+5 , 0 , 0 , 0 , a-395);
        
        SDL_RenderCopy(renderer , NULL , NULL , rects+5);

        a+=2;

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
    a = 0;
    SDL_Delay(500);
    while (a < 650)
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

        SDL_RenderCopy(renderer , textures[2] , NULL , (rects+2) );
        SDL_RenderCopy(renderer , textures[3] , NULL , (rects+3) );
        
        if(a<255) Rectanglesetcolor(renderer , rects+5 , 0 , 0 , 0 , 255-a);
        else if(a>394) Rectanglesetcolor(renderer , rects+5 , 0 , 0 , 0 , a-395);
        
        SDL_RenderCopy(renderer , NULL , NULL , rects+5);

        a+=2;

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
    a = 0;
    SDL_Delay(500);
    while (a < 256)
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

        SDL_RenderCopy(renderer , textures[4] , NULL , (rects+4) );
        
        if(a<255) Rectanglesetcolor(renderer , rects+5 , 0 , 0 , 0 , 255-a);

        SDL_RenderCopy(renderer , NULL , NULL , rects+5);

        a+=2;

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
    
    for (int i = 0; i < 5; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }
    
    return true;
}