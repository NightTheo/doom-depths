
//
// Created by Theo OMNES on 09/10/2023.
//


#ifndef DOOMDEPTHS_BUTTON_CLICKED_EVENT_H
#define DOOMDEPTHS_BUTTON_CLICKED_EVENT_H

#include "in/sdl/sdl_controller.h"

typedef struct ButtonClicked {
    SDL_IHM ihm;
    Button button;
} ButtonClicked;

ButtonClicked button_clicked(SDL_IHM ihm, Button button);

#endif //DOOMDEPTHS_BUTTON_CLICKED_EVENT_H
