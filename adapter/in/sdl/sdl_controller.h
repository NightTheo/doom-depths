
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_SDL_CONTROLLER_H
#define DOOMDEPTHS_SDL_CONTROLLER_H

#include "SDL_ttf.h"
#include "pages/pages.h"

typedef struct SDL_IHM {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    CurrentPage current_page;
    Page page;
    uint8_t fps;
    size_t number_of_frames_from_start;
} SDL_IHM;

#endif //DOOMDEPTHS_SDL_CONTROLLER_H
