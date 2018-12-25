#include "bubble.h"
#define vitesse 4
#define size 40
typedef	uint8_t		u8;


Bubble::Bubble(SDL_Surface *screen) : en("ennemy", 100,65,screen), wa("whale",460,65,screen), re("ressort", 150, 245, screen),
wi("witch", 420, 245, screen){
    plup = Mix_LoadWAV( "resources/sound/shoot.wav" );
    death = Mix_LoadWAV( "resources/sound/death.wav");
    map = SDL_LoadBMP("resources/images/map.bmp");
    bubble = SDL_LoadBMP("resources/images/bubble.bmp");
    position_map.x = 0;
    position_map.y = 0;
    position_bubble.x = 100;
    position_bubble.y = 435;
    SDL_BlitSurface(map, nullptr, screen, &position_map);
    SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
    SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
    SDL_Flip(screen);

    tableau = static_cast<char **>(malloc(800 * sizeof(char*)));

    for(int i = 0; i < 800; i++)
    {
        tableau[i] = static_cast<char *>(malloc(500 * sizeof(char)));
    }
    Uint32 couleurNoire;
    couleurNoire = SDL_MapRGB(screen->format, 0, 0, 0);
    for(int j = 0; j < 500 ; j++) // on parcour tout notre tableau 2d
    {
        for(int i = 0; i < 800 ; i++)
        {
            tableau[i][j] = obtenirPixel(map, i, j) == couleurNoire;
        }
    }
}

int Bubble::wait_action(SDL_Surface *screen) {
    while (continuer == 1) {
        if(tableau[position_bubble.x][position_bubble.y+41]==1 && tableau[position_bubble.x+size][position_bubble.y+41]==1){
            position_bubble.y +=2;
        }
        if (tableau[position_bubble.x][position_bubble.y +size+1] != 1 || tableau[position_bubble.x+size][position_bubble.y +size+1] != 1){
            is_jumping = false;
        }
        SDL_Delay(16);
        SDL_BlitSurface(map, nullptr, screen, &position_map);
        SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
        SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
        next = SDL_GetTicks();
        if(next-actual > 2000){
            touched = false;
        }
        if (!touched) {
            if (en.collision2(position_bubble) || wa.collision2(position_bubble) ||
            re.collision2(position_bubble) || wi.collision2(position_bubble)) {
                actual = SDL_GetTicks();
                touched = true;
                health -= 1;
                Mix_PlayChannel(-1, death, 0);
                bubble = SDL_LoadBMP("resources/images/bubble_dead.bmp");
                SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                SDL_Delay(delay);
                SDL_Flip(screen);
                SDL_BlitSurface(map, nullptr, screen, &position_map);
                SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                bubble = SDL_LoadBMP("resources/images/bubble2_dead.bmp");
                SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                SDL_BlitSurface(map, nullptr, screen, &position_map);
                SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                SDL_Flip(screen);
                SDL_Delay(delay);
                bubble = SDL_LoadBMP("resources/images/bubble3_dead.bmp");
                SDL_BlitSurface(map, nullptr, screen, &position_map);
                SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                SDL_Flip(screen);
                SDL_Delay(delay);
                bubble = SDL_LoadBMP("resources/images/bubble4_dead.bmp");
                SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                SDL_BlitSurface(map, nullptr, screen, &position_map);
                SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                SDL_Flip(screen);
                SDL_Delay(delay);
                bubble = SDL_LoadBMP("resources/images/pouf.bmp");
                SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                SDL_BlitSurface(map, nullptr, screen, &position_map);
                SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                SDL_Flip(screen);
                SDL_Delay(delay);
                bubble = SDL_LoadBMP("resources/images/pouf2.bmp");
                SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                SDL_BlitSurface(map, nullptr, screen, &position_map);
                SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                SDL_Flip(screen);
                SDL_Delay(200);
                position_bubble.x = 100;
                position_bubble.y = 435;
                bubble = SDL_LoadBMP("resources/images/bubble.bmp");
                if (health == 0)
                    return 2;
            }
        }
        if(position_bubble.y>450){
            position_bubble.y = 4;
        }
        if(position_bubble.y<3){
            position_bubble.y = 459;
        }
        if(en.collision(bulle.rec[fire])) {
            en.kill();
            bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
        }
        if(wa.collision(bulle.rec[fire])) {
            wa.kill();
            bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
        }
        if(re.collision(bulle.rec[fire])) {
            re.kill();
            bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
        }
        if(wi.collision(bulle.rec[fire])) {
            wi.kill();
            bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
        }
        en.display(screen);
        wa.display(screen);
        re.display(screen);
        wi.display(screen);
        SDL_Flip(screen);
        SDL_PollEvent(&event);
        u8 *pKeys = SDL_GetKeyState(nullptr);
                    if(pKeys[SDLK_ESCAPE]){
                        continuer = 0;
                    }
                    if (pKeys[SDLK_d]) {
                        if (tableau[position_bubble.x + size][position_bubble.y + 35] == 1) {
                            if (walk) {
                                bubble = SDL_LoadBMP("resources/images/bubble.bmp");
                                w++;
                                if (w % 10 == 0)
                                    walk = false;
                            } else {
                                bubble = SDL_LoadBMP("resources/images/bubble_walking.bmp");
                                w++;
                                if (w % 10 == 0)
                                    walk = true;
                            }
                            position_bubble.x += vitesse;
                            dir = "r";
                        }
                    }
                    if(pKeys[SDLK_a]) {
                        if (tableau[position_bubble.x][position_bubble.y + 30] == 1) {
                            if (walk) {
                                bubble = SDL_LoadBMP("resources/images/bubble2.bmp");
                                w++;
                                if (w % 10 == 0)
                                    walk = false;
                            } else {
                                bubble = SDL_LoadBMP("resources/images/bubble2_walking.bmp");
                                w++;
                                if (w % 10 == 0)
                                    walk = true;
                            }
                            position_bubble.x -= vitesse;
                            dir = "l";
                        }
                    }
                    if(pKeys[SDLK_SPACE]) {
                        if (tableau[position_bubble.x][position_bubble.y - 1] == 1 &&
                            tableau[position_bubble.x + size][position_bubble.y - 1] == 1 &&
                            tableau[position_bubble.x][position_bubble.y +size+1] != 1 && !is_jumping) {
                            position_bubble.y -= 70;
                            while(tableau[position_bubble.x][position_bubble.y - 1] == 1 ||
                               tableau[position_bubble.x + size][position_bubble.y - 1] == 1 ||
                               tableau[position_bubble.x][position_bubble.y +size+1] != 1){
                                position_bubble.y += 2;
                            }
                            is_jumping = true;
                        }
                    }
                    if (pKeys[SDLK_f]) {
                        shoot(screen);
                        /*
                        if (dir == "l"){
                            bulle = SDL_LoadBMP("resources/images/bulle.bmp");
                            bubble = SDL_LoadBMP("resources/images/bubble_shooting2.bmp");
                            position_bulle.x = position_bubble.x - 4;
                            position_bulle.y = position_bubble.y + 15;
                            SDL_BlitSurface(map, nullptr, screen, &position_map);
                            SDL_BlitSurface(bulle, nullptr, screen, &position_bulle);
                            SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                            SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                            SDL_Flip(screen);
                        }*/
                    }
                }
}

void Bubble::shoot(SDL_Surface *screen) {
    //On joue le son
    Mix_PlayChannel(-1, plup, 0);
    fire+=1;
    if(fire=21){
        fire = 0;
    }
    if (dir == "r") {
        bulle.tab[fire] = SDL_LoadBMP("resources/images/bulle.bmp");
        bubble = SDL_LoadBMP("resources/images/bubble_shooting.bmp");
        bulle.rec[fire].x = position_bubble.x + size - 4;
        bulle.rec[fire].y = position_bubble.y + 15;
        SDL_BlitSurface(map, nullptr, screen, &position_map);
        SDL_SetColorKey(bulle.tab[fire], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[fire]->format, 0, 0, 0));
        SDL_BlitSurface(bulle.tab[fire], nullptr, screen, &bulle.rec[fire]);
        SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
        SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
        en.display(screen);
        wa.display(screen);
        re.display(screen);
        wi.display(screen);
        SDL_Flip(screen);
        for (int i = 0; i <= fire; i++) {
            SDL_SetColorKey(bulle.tab[i], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[i]->format, 0, 0, 0));
            SDL_BlitSurface(bulle.tab[i], nullptr, screen, &bulle.rec[i]);
            SDL_Flip(screen);
        }
        SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
        SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
        SDL_Flip(screen);
        SDL_Delay(100);
        bulle.tab[fire] = SDL_LoadBMP("resources/images/bulle2.bmp");
        bulle.rec[fire].x += 10;
        bulle.rec[fire].y -= 4;
        SDL_BlitSurface(map, nullptr, screen, &position_map);
        SDL_SetColorKey(bulle.tab[fire], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[fire]->format, 0, 0, 0));
        SDL_BlitSurface(bulle.tab[fire], nullptr, screen, &bulle.rec[fire]);
        SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
        SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
        en.display(screen);
        wa.display(screen);
        re.display(screen);
        wi.display(screen);
        SDL_Flip(screen);
        for (int i = 0; i <= fire; i++) {
            SDL_SetColorKey(bulle.tab[i], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[i]->format, 0, 0, 0));
            SDL_BlitSurface(bulle.tab[i], nullptr, screen, &bulle.rec[i]);
            SDL_Flip(screen);
        }
        SDL_Delay(100);
        bulle.tab[fire] = SDL_LoadBMP("resources/images/bulle3.bmp");
        bulle.rec[fire].x += 10;
        bulle.rec[fire].y -= 4;
        SDL_BlitSurface(map, nullptr, screen, &position_map);
        SDL_SetColorKey(bulle.tab[fire], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[fire]->format, 0, 0, 0));
        SDL_BlitSurface(bulle.tab[fire], nullptr, screen, &bulle.rec[fire]);
        SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
        SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
        en.display(screen);
        wa.display(screen);
        re.display(screen);
        wi.display(screen);
        SDL_Flip(screen);
        for (int i = 0; i <= fire; i++) {
            SDL_SetColorKey(bulle.tab[i], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[i]->format, 0, 0, 0));
            SDL_BlitSurface(bulle.tab[i], nullptr, screen, &bulle.rec[i]);
            SDL_Flip(screen);
        }
        SDL_Delay(100);
        bulle.tab[fire] = SDL_LoadBMP("resources/images/bulle4.bmp");
        bulle.rec[fire].x += 10;
        bulle.rec[fire].y -= 4;
        for (int i = 0; i <= fire; i++) {
            SDL_SetColorKey(bulle.tab[i], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[i]->format, 0, 0, 0));
            SDL_BlitSurface(bulle.tab[i], nullptr, screen, &bulle.rec[i]);
            SDL_Flip(screen);
        }
        SDL_BlitSurface(map, nullptr, screen, &position_map);
        SDL_SetColorKey(bulle.tab[fire], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[fire]->format, 0, 0, 0));
        SDL_BlitSurface(bulle.tab[fire], nullptr, screen, &bulle.rec[fire]);
        SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
        SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
        en.display(screen);
        wa.display(screen);
        re.display(screen);
        wi.display(screen);
        SDL_Flip(screen);
        for (int i = 0; i < 20; i++) {
            SDL_Delay(16);
            if (en.collision(bulle.rec[fire])) {
                en.kill();
                bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
            }
            if (wa.collision(bulle.rec[fire])) {
                wa.kill();
                bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
            }
            if (re.collision(bulle.rec[fire])) {
                re.kill();
                bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
            }
            if (wi.collision(bulle.rec[fire])) {
                wi.kill();
                bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
            }
            bulle.rec[fire].x += 10;
            SDL_BlitSurface(map, nullptr, screen, &position_map);
            for (int i = 0; i <= fire; i++) {
                SDL_SetColorKey(bulle.tab[i], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[i]->format, 0, 0, 0));
                SDL_BlitSurface(bulle.tab[i], nullptr, screen, &bulle.rec[i]);
                SDL_Flip(screen);
            }
            SDL_BlitSurface(map, nullptr, screen, &position_map);
            SDL_SetColorKey(bulle.tab[fire], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[fire]->format, 0, 0, 0));
            SDL_BlitSurface(bulle.tab[fire], nullptr, screen, &bulle.rec[fire]);
            SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
            SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
            en.display(screen);
            wa.display(screen);
            re.display(screen);
            wi.display(screen);
            SDL_Flip(screen);
        }
    }
        while(bulle.rec[fire].y>0){
            SDL_Delay(16);
            if(en.collision(bulle.rec[fire])) {
                en.kill();
                bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
            }
            if(wa.collision(bulle.rec[fire])) {
                wa.kill();
                bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
            }
            if(re.collision(bulle.rec[fire])) {
                re.kill();
                bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
            }
            if(wi.collision(bulle.rec[fire])) {
                wi.kill();
                bulle.tab[fire] = SDL_LoadBMP("resources/images/ennemy_bulle.bmp");
            }
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            EXIT_SUCCESS;
                            SDL_Quit();
                        case SDLK_d:
                            if (walk) {
                                bubble = SDL_LoadBMP("resources/images/bubble.bmp");
                                walk = false;
                            } else {
                                bubble = SDL_LoadBMP("resources/images/bubble_walking.bmp");
                                walk = true;
                            }
                            position_bubble.x += vitesse;
                            SDL_BlitSurface(map, nullptr, screen, &position_map);
                            SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                            SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                            SDL_Flip(screen);
                            dir = "r";
                            break;
                        case SDLK_f:
                            shoot(screen);
                        case SDLK_a:
                            if (walk) {
                                bubble = SDL_LoadBMP("resources/images/bubble2.bmp");
                                walk = false;
                            } else {
                                bubble = SDL_LoadBMP("resources/images/bubble2_walking.bmp");
                                walk = true;
                            }
                            position_bubble.x -= vitesse;
                            SDL_BlitSurface(map, nullptr, screen, &position_map);
                            SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
                            SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
                            SDL_Flip(screen);
                            dir = "l";
                            break;
                    }
            }
            bulle.rec[fire].y -= 3;
            SDL_BlitSurface(map, nullptr, screen, &position_map);
            for (int i = 0; i <= fire; i++) {
                SDL_SetColorKey(bulle.tab[i], SDL_SRCCOLORKEY, SDL_MapRGB(bulle.tab[i]->format, 0, 0, 0));
                SDL_BlitSurface(bulle.tab[i], nullptr, screen, &bulle.rec[i]);
                SDL_Flip(screen);
            }
            SDL_SetColorKey(bubble, SDL_SRCCOLORKEY, SDL_MapRGB(bubble->format, 0, 0, 0));
            SDL_BlitSurface(bubble, nullptr, screen, &position_bubble);
            en.display(screen);
            wa.display(screen);
            re.display(screen);
            wi.display(screen);
            SDL_Flip(screen);
        }
}

Uint32 Bubble::obtenirPixel(SDL_Surface *surface, int x, int y)
{
    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    /* Ici p est l'adresse du pixel que l'on veut connaitre */
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;

            /*Ne devrait pas arriver, mais évite les erreurs*/
        default:
            return 0;
    }
}
