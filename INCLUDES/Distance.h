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
    SDL_Surface* fontsurf = TTF_RenderText_Solid(popfont , numbers , color);
    *texture = SDL_CreateTextureFromSurface(renderer , fontsurf);
    SDL_FreeSurface(fontsurf);
}