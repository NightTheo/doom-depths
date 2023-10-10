
//
// Created by Theo OMNES on 10/10/2023.
//

#ifndef DOOMDEPTHS_SDL_MAP_PAGE_H
#define DOOMDEPTHS_SDL_MAP_PAGE_H

#include "stdbool.h"
#include "in/sdl/components/button/button.h"
#include "map/map.h"

typedef struct  {
    bool is_displayed;
    Button spawn;
    Map map;
} MapPage;

MapPage map_page(SDL_IHM ihm);

void draw_map_page(SDL_Renderer *renderer, MapPage map_page);

SDL_IHM map_page_handle_event(SDL_Event event, SDL_IHM ihm);

#endif //DOOMDEPTHS_SDL_MAP_PAGE_H
