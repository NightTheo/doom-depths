
//
// Created by Theo OMNES on 19/10/2023.
//

#ifndef DOOMDEPTHS_ANIMATION_H
#define DOOMDEPTHS_ANIMATION_H

#include "in/sdl/components/sprite_sheet/sprite_sheet.h"

typedef struct {
    SpriteSheet sprite_sheet;
    SDL_Rect rect;
    uint16_t start_frame;
    uint16_t number_of_frames;
    uint16_t current_frame;
} Animation;

#endif //DOOMDEPTHS_ANIMATION_H
