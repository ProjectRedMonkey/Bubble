#include "ennemy.h"
#define vitesse 4

Ennemy::Ennemy(std::string st, double x, double y, SDL_Surface *screen){
    str = st;
    ennemi = SDL_LoadBMP((std::string("resources/images/")+str+".bmp").c_str());
    position_ennemi.x = x;
    position_ennemi.y = y;
}

void Ennemy::display(SDL_Surface *screen) {
    if(!col) {
        if (i < 50) {
            position_ennemi.x += vitesse;
            i++;
            if (walk) {
                j++;
                ennemi = SDL_LoadBMP((std::string("resources/images/") + str + ".bmp").c_str());
                if (j % 10 == 0)
                    walk = false;
            } else {
                j++;
                ennemi = SDL_LoadBMP((std::string("resources/images/") + str + "_walking.bmp").c_str());
                if (j % 10 == 0)
                    walk = true;
            }
        } else {
            position_ennemi.x -= vitesse;
            i++;
            if (walk) {
                j++;
                ennemi = SDL_LoadBMP((std::string("resources/images/") + str + "2.bmp").c_str());
                if (j % 10 == 0)
                    walk = false;
            } else {
                j++;
                ennemi = SDL_LoadBMP((std::string("resources/images/") + str + "2_walking.bmp").c_str());
                if (j % 10 == 0)
                    walk = true;
            }
        }
        SDL_SetColorKey(ennemi, SDL_SRCCOLORKEY, SDL_MapRGB(ennemi->format, 0, 0, 0));
        SDL_BlitSurface(ennemi, nullptr, screen, &position_ennemi);
        if (i == 100) {
            i = 0;
        }
    }
}

bool Ennemy::collision(SDL_Rect bulle) {
    if(alive) {
        if (position_ennemi.x < bulle.x + 30 &&
            position_ennemi.x + 40 > bulle.x &&
            position_ennemi.y < bulle.y + 34 &&
            40 + position_ennemi.y > bulle.y) {
            col = true;
            return true;
        } else {
            return false;
        }
    }
}

bool Ennemy::collision2(SDL_Rect bulle) {
    if(alive) {
        if (position_ennemi.x < bulle.x + 40 &&
            position_ennemi.x + 40 > bulle.x &&
            position_ennemi.y < bulle.y + 40 &&
            40 + position_ennemi.y > bulle.y) {
            return true;
        } else {
            return false;
        }
    }
}

void Ennemy::kill() {
    SDL_FillRect(ennemi, nullptr, SDL_MapRGB(ennemi->format, 0, 0, 0));
    SDL_FreeSurface(ennemi);
    alive = false;
}