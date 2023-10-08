
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_SDL_TOWN_CONTROLLER_H
#define DOOMDEPTHS_SDL_TOWN_CONTROLLER_H

#include "in/sdl/components/button/button.h"
#include "stdbool.h"

typedef struct TownWindow TownWindow;
struct TownWindow {
    bool is_displayed;
    Button newRunButton;
    Button continueButton;
};

TownWindow town_window(SDL_IHM ihm);


#endif //DOOMDEPTHS_SDL_TOWN_CONTROLLER_H
