
//
// Created by Theo OMNES on 14/10/2023.
//

#ifndef DOOMDEPTHS_HEALTH_BAR_H
#define DOOMDEPTHS_HEALTH_BAR_H

#include <stdint.h>
#include <SDL_render.h>
#include "SDL_ttf.h"
#include "components/color/sdl_color.h"

typedef struct {
    uint16_t max_health;
    uint16_t current_health;
    SDL_Color health_color;
    SDL_Rect rect;
} HealthBar;

void draw_health_bar(SDL_Renderer *renderer, HealthBar health_bar, TTF_Font *font);

HealthBar create_health_bar(uint16_t max_health, SDL_Color health_color, SDL_Rect rect);

#endif //DOOMDEPTHS_HEALTH_BAR_H
