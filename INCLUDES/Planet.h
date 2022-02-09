#include "Main_includes.h"
#include "Nation.h"

struct Planet {
    int id;
    struct Nation* nation;
    SDL_Rect rect;
    SDL_Rect poprect;
    SDL_Rect potrect;
    SDL_Rect namrect;

    int x;
    int y;
    double angle;

    bool mouseon;
    bool trigered;

    int population;
    int typeoftexture;
};

int Planet_dis_finder (struct Planet A , struct Planet B){
    return Distance_2D(A.x , A.y , B.x , B.y);
}

void Planet_dis_finder_n (int howmany , struct Planet* planets , int distances[PLANET_MAX][PLANET_MAX]) {
    for(int i = 0 ; i < howmany ; i++){
        for (int j = 0 ; j < howmany ; j++)
        {
            distances[i][j] = Planet_dis_finder( (*(planets+i)) , (*(planets + j)) );
        }
    }
}

bool Planet_dis_checker (struct Planet A , struct Planet B){
    if(Planet_dis_finder(A ,B) < PLANET_MIN_DIS){
        return false;
    }
    return true;
}

bool Planet_dis_checker_n (int howmany , struct Planet* A , struct Planet B){
    for (int i = 0; i < howmany; i++)
    {
        if(!Planet_dis_checker(*(A+i) , B)){
            return false;
        }
    }
    return true;
}

void Planet_alloc (int howmanyplayable , int howmanynations , int howmanyvoidplanets , struct Planet* planets , struct Nation* nations) {
    srand(time(0));
    for (int i = 0 ; i < howmanyplayable + howmanyvoidplanets ; i++)
    {
        (planets+i)->id = i;
        (planets+i)->typeoftexture = PLANET_TYPES_V + rand()%PLANET_TYPES;

        //creating white planets and void planets
        if(i < howmanynations) (planets+i)->nation = (nations+i+1);
        else if(i < howmanyplayable) (planets+i)->nation = nations;
        else {
            (planets+i)->nation = (nations + NATION_MAX-1);
            (planets+i)->typeoftexture = rand()%PLANET_TYPES_V;
        }

        (planets+i)->population = PLANET_POPULATION;
        (planets+i)->angle = (rand()%360);
        /*can add a random rotation speed*/
        
        //random planet size
        (planets+i)->rect.h = PLANET_MIN_R + ((rand())%(PLANET_MAX_R - PLANET_MIN_R));
        //not random planet size
        //(planets+i)->rect.h = PLANET_MIN_R;
        (planets+i)->rect.w = (planets+i)->rect.h;


        (planets+i)->trigered = false;
        (planets+i)->mouseon = false;

        while (true)
        {
            (planets+i)->x = GAME_W_S + (rand()%(GAME_W_E - GAME_W_S));
            (planets+i)->y = GAME_H_S + (rand()%(GAME_H_E - GAME_H_S));
            if(Planet_dis_checker_n(i , planets , *(planets+i))) break;
        }

        (planets+i)->rect.x = (planets+i)->x - ((planets+i)->rect.h)/2;
        (planets+i)->rect.y = (planets+i)->y - ((planets+i)->rect.h)/2;
        //adding place of text
        (planets+i)->poprect.x = (planets+i)->rect.x + (planets+i)->rect.w + 5;
        (planets+i)->poprect.y = (planets+i)->rect.y + 7;
        //adding potion time
        (planets+i)->potrect.x = (planets+i)->poprect.x;
        (planets+i)->potrect.y = (planets+i)->poprect.y + (planets+i)->rect.w - 27;
        //adding namrects
        (planets+i)->namrect.x = (planets+i)->poprect.x + 5;
        (planets+i)->namrect.y = ((planets+i)->poprect.y + (planets+i)->potrect.y)/2 + 3;

        /*check if alghoritem last long try another pattern fro the brginning*/
    }
}

bool Planet_mouseon (int x , int y , struct Planet* planet){
    if(Distance_2D(x , y , planet->x , planet->y) < (planet->rect.h)/2 + 1){
        planet->mouseon = true;
        return true;
    }
    planet->mouseon = false;
    return false;
}

void Planet_render (struct Planet* obj , SDL_Renderer* renderer , SDL_Texture **planettextures , TTF_Font* popfont , TTF_Font* charfont , SDL_Color* colors , char usernames[NAME_MAX][NAME_MAX_L]) {
    SDL_RenderCopyEx(renderer , *(planettextures + obj->typeoftexture) /*adding color of nation*/ , NULL , &(obj->rect) , obj->angle , NULL , SDL_FLIP_NONE);
    obj->angle += PLANET_ROTATION_SPEED;
    if(obj->nation->potion == 4){
        obj->angle += 2*PLANET_ROTATION_SPEED;
    }

    if(obj->angle > 360) obj->angle-=360.0;
    

    if(obj->mouseon) {
        SDL_Texture* bordertexture;
        SDL_Rect borderrect;
        Creattexturefrompng("IMAGES/planetborder.png" , &bordertexture , renderer);
        borderrect.w = obj->rect.w + 20;
        borderrect.h = obj->rect.h + 20;
        borderrect.x = obj->rect.x - 10;
        borderrect.y = obj->rect.y - 10;
        SDL_RenderCopyEx(renderer , bordertexture , NULL , &borderrect , obj->angle , NULL , SDL_FLIP_NONE);
        SDL_DestroyTexture(bordertexture);
    }

    if(obj->trigered) {
        SDL_Texture* bordertexture;
        SDL_Rect borderrect;
        Creattexturefrompng("IMAGES/planettrigered.png" , &bordertexture , renderer);
        borderrect.w = obj->rect.w + 20;
        borderrect.h = obj->rect.h + 20;
        borderrect.x = obj->rect.x - 10;
        borderrect.y = obj->rect.y - 10;
        SDL_RenderCopyEx(renderer , bordertexture , NULL , &borderrect , obj->angle , NULL , SDL_FLIP_NONE);
        SDL_DestroyTexture(bordertexture);
    }

    if(obj->nation->potion == 5) {
        SDL_RenderCopy(renderer , *(planettextures+18) , NULL , &(obj->rect));
    }

    
    //font
    if(obj->nation->color != -1){
        SDL_Texture* fonttexture;
        numbertotexture(obj->population , popfont , *(colors + (obj->nation->color)) , &fonttexture , renderer);
        SDL_QueryTexture(fonttexture , NULL , NULL , &(obj->poprect.w) , &(obj->poprect.h) );
        SDL_RenderCopy(renderer , fonttexture , NULL , &(obj->poprect));
        SDL_DestroyTexture(fonttexture);
        
        if(obj->nation->potiontime != 0) {
            numbertotexture(obj->nation->potiontime , popfont , *(colors + (obj->nation->color)) , &fonttexture , renderer);
            SDL_QueryTexture(fonttexture , NULL , NULL , &(obj->potrect.w) , &(obj->potrect.h) );
            SDL_RenderCopy(renderer , fonttexture , NULL , &(obj->potrect));
            SDL_DestroyTexture(fonttexture);
        }

        if(obj->nation->name != -1){
            texttotexture(usernames[obj->nation->name] , charfont , *(colors + (obj->nation->color)) , &fonttexture , renderer);
            SDL_QueryTexture(fonttexture , NULL , NULL , &(obj->namrect.w) , &(obj->namrect.h) );
            SDL_RenderCopy(renderer , fonttexture , NULL , &(obj->namrect));
            SDL_DestroyTexture(fonttexture);
        }
    }



    /*adding potion effect*/
}

void Planet_render_n (struct Planet* planets , SDL_Renderer* renderer , SDL_Texture **planettextures , int howmanyplanetstotal , TTF_Font* popfont , TTF_Font* charfont , SDL_Color* colors , char usernames[NAME_MAX][NAME_MAX_L]) {
    for (int i = 0; i < howmanyplanetstotal; i++)
    {
        Planet_render(planets+i , renderer , planettextures , popfont , charfont , colors , usernames);
    }
}