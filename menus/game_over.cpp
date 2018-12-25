#include "game_over.h"


bool GameOver::click_play(int x, int y)
{
    return (position_rejouer.x < x) && (position_rejouer.x + 310 > x) && (position_rejouer.y < y) && (position_rejouer.y + 62 > y);
}

bool GameOver::click_exit(int x, int y)
{
    return (position_quitter.x < x) && (position_quitter.x + 310 > x) && (position_quitter.y < y) && (position_quitter.y + 62 > y);
}

GameOver::GameOver(SDL_Surface *screen) {
    wallpaper = SDL_LoadBMP("resources/images/wallpaper.bmp");
    bubbleg = SDL_LoadBMP("resources/images/bubbleg_gameover.bmp");
    bubbleb = SDL_LoadBMP("resources/images/bubbleb_gameover.bmp");
    rejouer = SDL_LoadBMP("resources/images/rejouer.bmp");
    quitter = SDL_LoadBMP("resources/images/quitter.bmp");
    position_wallpaper.x = 0;
    position_wallpaper.y = 0;
    position_bubbleb.x = 650;
    position_bubbleb.y = 0;
    position_bubbleg.x = 50;
    position_bubbleg.y = 380;
    position_rejouer.x = 250;
    position_rejouer.y = 280;
    position_quitter.x = 240;
    position_quitter.y = 380;
    SDL_BlitSurface(wallpaper, nullptr, screen, &position_wallpaper);
    SDL_BlitSurface(bubbleb, nullptr, screen, &position_bubbleb);
    SDL_BlitSurface(bubbleg, nullptr, screen, &position_bubbleg);
    SDL_Flip(screen);
}

int GameOver::wait_action(SDL_Surface *screen){
    while (continuer == 2){
        if (i<200) {
            i++;
            position_bubbleg.y -= 2;
            if (walk){
                bubbleg = SDL_LoadBMP("resources/images/bubbleg2_gameover.bmp");
                green++;
                if(green%20==0)
                    walk = false;
            } else {
                bubbleg = SDL_LoadBMP("resources/images/bubbleg_gameover.bmp");
                green++;
                if(green%20==0)
                    walk = true;
            }
        } else {
            i++;
            position_bubbleg.y += 2;
            if (walk){
                bubbleg = SDL_LoadBMP("resources/images/bubbleg2_gameover.bmp");
                green++;
                if(green%20==0)
                    walk = false;
            } else {
                bubbleg = SDL_LoadBMP("resources/images/bubbleg_gameover.bmp");
                green++;
                if(green%20==0)
                    walk = true;
            }
            if(i==400){
                i=0;
            }
        }
        if (j<200) {
            j++;
            position_bubbleb.y += 2;
            if (walk2){
                bubbleb = SDL_LoadBMP("resources/images/bubbleb2_gameover.bmp");
                blue++;
                if(blue%20==0)
                    walk2 = false;
            } else {
                bubbleb = SDL_LoadBMP("resources/images/bubbleb_gameover.bmp");
                blue++;
                if(blue%20==0)
                    walk2 = true;
            }
        } else {
            j++;
            position_bubbleb.y -= 2;
            if (walk){
                bubbleb = SDL_LoadBMP("resources/images/bubbleb2_gameover.bmp");
                blue++;
                if(blue%20==0)
                    walk2 = false;
            } else {
                bubbleb = SDL_LoadBMP("resources/images/bubbleb_gameover.bmp");
                blue++;
                if(blue%20==0)
                    walk2 = true;
            }
            if(j==400){
                j=0;
            }
        }
        SDL_BlitSurface(wallpaper, nullptr, screen, &position_wallpaper);
        SDL_BlitSurface(bubbleb, nullptr, screen, &position_bubbleb);
        SDL_BlitSurface(bubbleg, nullptr, screen, &position_bubbleg);
        SDL_BlitSurface(rejouer, nullptr, screen, &position_rejouer);
        SDL_BlitSurface(quitter, nullptr, screen, &position_quitter);
        SDL_Flip(screen);
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                }
            case SDL_MOUSEBUTTONDOWN: {
                case SDL_BUTTON_LEFT:
                    if (click_exit(event.motion.x, event.motion.y)) {
                        continuer = 0;
                        return continuer;
                    }
                    if (click_play(event.motion.x, event.motion.y)) {
                        continuer = 1;
                        return continuer;
                     }
                    break;
            }
        }
    }
}