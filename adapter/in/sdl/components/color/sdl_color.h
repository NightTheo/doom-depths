
//
// Created by Theo OMNES on 08/10/2023.
//

#ifndef DOOMDEPTHS_SDL_COLOR_H
#define DOOMDEPTHS_SDL_COLOR_H

#include "SDL2/SDL_pixels.h"

typedef enum {
    SDL_WHITE,
    SDL_RED,
    SDL_MIDDLE_RED,
    SDL_DARK_RED,
    SDL_GREEN,
    SDL_BLUE,
    SDL_TRANSPARENT,
} SDL_COLOR;

SDL_Color get_color(SDL_COLOR color);

#endif //DOOMDEPTHS_SDL_COLOR_H
