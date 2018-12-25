#ifndef BUBBLE_GAME_OVER_H
#define BUBBLE_GAME_OVER_H
#include <SDL/SDL.h>

class GameOver {
public:
    GameOver(SDL_Surface *screen);
    int wait_action(SDL_Surface *screen);
private:
    SDL_Surface *wallpaper, *bubbleg, *bubbleb, *rejouer, *quitter;
    SDL_Rect position_wallpaper, position_bubbleg, position_bubbleb, position_rejouer, position_quitter;
    SDL_Event event;
    int continuer = 2, i = 0, green = 0, j = 0, blue = 0;
    bool walk = false, walk2=false;
    bool click_exit(int x, int y);
    bool click_play(int x, int y);
};


#endif //BUBBLE_GAME_OVER_H
