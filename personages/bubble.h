#ifndef BUBBLE_BUBBLE_H
#define BUBBLE_BUBBLE_H
#include <SDL/SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL/SDL_mixer.h>
#include "ennemy.h"
#include "bulle.h"



class Bubble {
public:
    Bubble(SDL_Surface *screen);
    int wait_action(SDL_Surface *screen);
private:
    SDL_Surface *map = nullptr, *bubble = nullptr;
    SDL_Rect position_map, position_bubble;
    Mix_Chunk *plup = NULL, *death = NULL;
    Ennemy en, wa, re, wi;
    void shoot(SDL_Surface *screen);
    char** tableau;
    Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);
    SDL_Event event;
    int continuer = 1, fire=0, w = 0, health = 3, actual, next, delay = 500;
    bool touched = false;
    bulle bulle;
    bool walk = false, is_jumping = false;
    std::string dir = "r";
};


#endif //BUBBLE_BUBBLE_H
