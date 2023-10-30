
//
// Created by Theo OMNES on 15/10/2023.
//

#include "sdl_controller.h"
#include "button_events.h"

ButtonEvent button_clicked(SDL_IHM ihm, Button button) {
    ButtonEvent e = {
            .ihm = ihm,
            .button = button,
            .type = BUTTON_CLICKED,
    };
    return e;
}

ButtonEvent button_hovered(SDL_IHM ihm, Button button) {
    button.state = BUTTON_SELECTED;
    ButtonEvent e = {
            .ihm = ihm,
            .button = button,
            .type = BUTTON_HOVERED,
    };
    return e;
}

ButtonEvent button_unhovered(SDL_IHM ihm, Button button) {
    button.state = BUTTON_NORMAL;
    ButtonEvent e = {
            .ihm = ihm,
            .button = button,
            .type = BUTTON_UNHOVERED,
    };
    return e;
}

ButtonEvent button_event_not_handled(SDL_IHM ihm, Button button) {
    ButtonEvent e = {
            .ihm = ihm,
            .button = button,
            .type = BUTTON_EVENT_NOT_HANDLED,
    };
    return e;
}