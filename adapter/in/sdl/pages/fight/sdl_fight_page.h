
//
// Created by Theo OMNES on 13/10/2023.
//

#ifndef DOOMDEPTHS_SDL_FIGHT_PAGE_H
#define DOOMDEPTHS_SDL_FIGHT_PAGE_H

#include <SDL_render.h>
#include <SDL_events.h>

typedef struct SDL_IHM SDL_IHM;

typedef struct  {

} FightPage;

void draw_fight_page(SDL_Renderer *renderer, FightPage fight_page);

SDL_IHM fight_page_handle_event(SDL_Event event, SDL_IHM ihm);

#endif //DOOMDEPTHS_SDL_FIGHT_PAGE_H
