#ifndef BUBBLE_BULLE_H
#define BUBBLE_BULLE_H
#include <SDL/SDL.h>
#include <stdio.h>
#include <iostream>
#include "ennemy.h"

class bulle {
public:
    bulle();
    SDL_Surface** tab;
    SDL_Rect rec[20];
};


#endif //BUBBLE_BULLE_H
