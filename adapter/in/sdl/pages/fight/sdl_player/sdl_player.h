
//
// Created by Theo OMNES on 19/10/2023.
//

#ifndef DOOMDEPTHS_SDL_PLAYER_H
#define DOOMDEPTHS_SDL_PLAYER_H

#include <SDL_render.h>
#include "player/player.h"
#include "in/sdl/pages/fight/health_bar/health_bar.h"

typedef struct SDL_IHM SDL_IHM;

typedef struct SdlPlayer {
    Player player;
    SDL_Texture *texture;
    SDL_Rect source_sprites_rect;
    SDL_Rect destination_sprite_rect;
    HealthBar health_bar;
    uint32_t current_sprite;
} SdlPlayer;

SdlPlayer update_sld_fight_player(SdlPlayer player);

SdlPlayer fill_fight_player(SDL_Renderer *renderer);

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm);

#endif //DOOMDEPTHS_SDL_PLAYER_H
