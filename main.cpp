#include <iostream>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "personages/ennemy.h"
#include "personages/bubble.h"
#include "menus/game_over.h"

void bubble(Mix_Music *music, SDL_Surface *screen);
void gameover(Mix_Music *over, SDL_Surface *screen);

int main( int argc, char** argv) {
    SDL_Surface *screen = nullptr;
    Mix_Music *music = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    screen = SDL_SetVideoMode(800, 500, 0, 0);
    music = Mix_LoadMUS("resources/sound/music.wav");
    bubble(music,screen);

}

void bubble(Mix_Music *music, SDL_Surface *screen){
    //Load the music
    Mix_PlayMusic(music, -1);
    Bubble bubble(screen);
    int status;
    while((status = bubble.wait_action(screen))== 1){

    }
    switch (status){
        case 0 :
            EXIT_SUCCESS;
            SDL_Quit();
            break;
        case 2:
            Mix_Music *over=nullptr;
            Mix_FreeMusic(music);
            over = Mix_LoadMUS("resources/sound/gameover.wav");
            gameover(over,screen);
            break;
    }
}

void gameover(Mix_Music *over, SDL_Surface *screen){
    GameOver gameover(screen);
    Mix_PlayMusic(over, -1);
    int status;
    while((status = gameover.wait_action(screen)) == 2){

    }
    switch (status){
        case 0:
            EXIT_SUCCESS;
            SDL_Quit();
            break;
        case 1:
            Mix_Music *music = NULL;
            music = Mix_LoadMUS("resources/sound/music.wav");
            bubble(music,screen);
    }
}