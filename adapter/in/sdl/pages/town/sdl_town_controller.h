
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_SDL_TOWN_CONTROLLER_H
#define DOOMDEPTHS_SDL_TOWN_CONTROLLER_H


#include "stdbool.h"
#include "in/sdl/components/button/button.h"

typedef struct TownWindow TownWindow;
struct TownWindow {
    Button newRunButton;
    Button continueButton;
};

TownWindow town_window(SDL_IHM ihm);

void draw_town_window(SDL_Renderer *renderer, TownWindow town);

SDL_IHM town_handle_event(SDL_Event event, SDL_IHM ihm);


#endif //DOOMDEPTHS_SDL_TOWN_CONTROLLER_H
