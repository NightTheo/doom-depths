
//
// Created by Theo OMNES on 13/10/2023.
//

#ifndef DOOMDEPTHS_SDL_FIGHT_PAGE_H
#define DOOMDEPTHS_SDL_FIGHT_PAGE_H

#include <SDL_render.h>
#include <SDL_events.h>
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

typedef struct  {
    SdlPlayer player;
    Fight fight;
} FightPage;

FightPage fill_fight_page(SDL_IHM ihm);

void draw_fight_page(SDL_Renderer *renderer, FightPage fight_page, SDL_IHM ihm);

SDL_IHM fight_page_handle_event(SDL_Event event, SDL_IHM ihm);

SDL_IHM update_fight_page(SDL_IHM ihm);



#endif //DOOMDEPTHS_SDL_FIGHT_PAGE_H
