#include "Main_includes.h"
#include "Defines.h"

int Distance_1D (int x1 , int y1 , int x2 , int y2){
    return abs(x1-x2) + abs(y1-y2);
}

int Distance_2D (int x1 , int y1 , int x2 , int y2){
    double res = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2); 
    return (int)sqrt(res);
}

void numbertotexture (int number , TTF_Font* popfont , SDL_Color color , SDL_Texture** texture , SDL_Renderer* renderer) {
    char numbers[5];
    itoa(number , numbers , 10);
    SDL_Surface* fontsurf = TTF_RenderText_Blended(popfont , numbers , color);
    *texture = SDL_CreateTextureFromSurface(renderer , fontsurf);
    SDL_FreeSurface(fontsurf);
}

void texttotexture (char* name , TTF_Font* popfont , SDL_Color color , SDL_Texture** texture , SDL_Renderer* renderer) {
    SDL_Surface* fontsurf = TTF_RenderText_Blended(popfont , name , color);
    *texture = SDL_CreateTextureFromSurface(renderer , fontsurf);
    SDL_FreeSurface(fontsurf);
}

void Creattexturefrompng (char* address , SDL_Texture** texture , SDL_Renderer* renderer){
    SDL_Surface* surf = IMG_Load(address);
    *texture = SDL_CreateTextureFromSurface(renderer , surf);
    SDL_FreeSurface(surf);
}

void SCsort (int SCscores[SCsaves] , int SCmax[10]) {
    for (int i = 0; i < 10; i++)
    {
        int max = -50000;
        int maxplace;
        for (int j = 1; j <= SCscores[0]; j++)
        {   
            if(max < SCscores[j]){
                bool check = false;
                for (int k = 0; k < i; k++)
                {
                    if(j == SCmax[k]) check = true;
                }
                if(check) continue;

                max = SCscores[j];
                maxplace = j;
            }
        }
        SCmax[i] = maxplace;
    }
}