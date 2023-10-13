
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_SDL_CONTROLLER_H
#define DOOMDEPTHS_SDL_CONTROLLER_H

#include "SDL_ttf.h"
#include "in/sdl/pages/pages.h"

typedef struct SDL_IHM {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    CurrentPage current_page;
    Page page;
} SDL_IHM;

#endif //DOOMDEPTHS_SDL_CONTROLLER_H
