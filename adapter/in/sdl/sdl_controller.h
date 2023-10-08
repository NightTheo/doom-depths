
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_SDL_CONTROLLER_H
#define DOOMDEPTHS_SDL_CONTROLLER_H

#include "SDL_ttf.h"
#include "in/sdl/pages/town/sdl_town_controller.h"

typedef struct SDL_IHM SDL_IHM;
struct SDL_IHM {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    TownWindow town_window;
};

#endif //DOOMDEPTHS_SDL_CONTROLLER_H
