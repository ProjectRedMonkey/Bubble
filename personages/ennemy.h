#ifndef BUBBLE_ENNEMY_H
#define BUBBLE_ENNEMY_H

#include <SDL/SDL.h>
#include <stdio.h>
#include <iostream>
#include "bulle.h"


class Ennemy {
public:
    Ennemy(std::string st, double x, double y, SDL_Surface *screen);
    void display(SDL_Surface *screen);
    bool collision(SDL_Rect bulle);
    bool collision2(SDL_Rect bulle);
    void kill();
private:
    SDL_Surface *ennemi= nullptr;
    SDL_Rect position_ennemi;
    bool walk = false;
    std::string str;
    int i = 0;
    int j = 0;
    bool col = false;
    bool alive = true;
};


#endif //BUBBLE_ENNEMY_H
