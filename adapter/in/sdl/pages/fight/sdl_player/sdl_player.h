
//
// Created by Theo OMNES on 19/10/2023.
//

#ifndef DOOMDEPTHS_SDL_PLAYER_H
#define DOOMDEPTHS_SDL_PLAYER_H

#include <SDL_render.h>
#include "domain/player/player.h"
#include "in/sdl/pages/fight/health_bar/health_bar.h"
#include "in/sdl/components/animation/animation.h"

typedef struct SDL_IHM SDL_IHM;

typedef struct SdlPlayer {
    Player player;
    Animation animation;
    HealthBar health_bar;
} SdlPlayer;

SdlPlayer update_sld_fight_player(SdlPlayer player);

SdlPlayer fill_fight_player(SDL_Renderer *renderer);

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm);

#endif //DOOMDEPTHS_SDL_PLAYER_H
