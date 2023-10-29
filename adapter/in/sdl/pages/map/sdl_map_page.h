
//
// Created by Theo OMNES on 10/10/2023.
//

#ifndef DOOMDEPTHS_SDL_MAP_PAGE_H
#define DOOMDEPTHS_SDL_MAP_PAGE_H

#include "stdbool.h"
#include "in/sdl/components/button/button.h"
#include "domain/map/map.h"
#include "in/sdl/pages/map/zone/sdl_zone.h"

typedef struct  {
    Button spawn;
    Map map;
    SdlZone **grid;
} MapPage;

void draw_map_page(SDL_Renderer *renderer, MapPage map_page);

SDL_IHM map_page_handle_event(SDL_Event event, SDL_IHM ihm);

MapPage fill_map_page(SDL_IHM ihm, Map map);

bool can_display_position_in_sdl_map(Position p, Map m);

#endif //DOOMDEPTHS_SDL_MAP_PAGE_H
