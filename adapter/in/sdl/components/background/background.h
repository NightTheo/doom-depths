
//
// Created by Theo OMNES on 21/10/2023.
//

#ifndef DOOMDEPTHS_BACKGROUND_H
#define DOOMDEPTHS_BACKGROUND_H

#include <SDL_render.h>

typedef struct Background {
    SDL_Texture *texture;
    SDL_Rect rect;
} Background;

typedef struct BackgroundResult {
    SDL_bool success;
    Background background;
} BackgroundResult;

BackgroundResult create_background(SDL_Renderer *renderer, const char *path);

void draw_background(SDL_Renderer *renderer, SDL_Rect zone, Background background);

#endif //DOOMDEPTHS_BACKGROUND_H
