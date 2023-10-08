
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL.h"
#include "padding.h"

void padding_rect(SDL_Rect *rect, Padding p) {
    rect->w += 2 * p.horizontal;
    rect->h += 2 * p.vertical;
}