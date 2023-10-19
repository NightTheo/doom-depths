
//
// Created by Theo OMNES on 19/10/2023.
//

#ifndef DOOMDEPTHS_SPRITE_SHEET_H
#define DOOMDEPTHS_SPRITE_SHEET_H

#include <SDL_render.h>

typedef struct {
    SDL_Texture *texture;
    uint16_t columns;
    uint16_t rows;
} SpriteSheet;

#endif //DOOMDEPTHS_SPRITE_SHEET_H
