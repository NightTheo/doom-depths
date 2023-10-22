
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_SDL_TOWN_CONTROLLER_H
#define DOOMDEPTHS_SDL_TOWN_CONTROLLER_H


#include "stdbool.h"
#include "in/sdl/components/button/button.h"
#include "in/sdl/components/aria/aria.h"
#include "in/sdl/components/background/background.h"

typedef struct TownWindow TownWindow;
struct TownWindow {
    Button new_run_button;
    Button continue_button;
    Aria aria;
    Background background;
    SDL_Window *window;
};

TownWindow town_window(SDL_IHM ihm);

void draw_town_window(SDL_Renderer *renderer, TownWindow town);

SDL_IHM town_handle_event(SDL_Event event, SDL_IHM ihm);

SDL_IHM update_town_page(SDL_IHM ihm);

#endif //DOOMDEPTHS_SDL_TOWN_CONTROLLER_H
