
//
// Created by Theo OMNES on 09/10/2023.
//


#ifndef DOOMDEPTHS_BUTTON_EVENTS_H
#define DOOMDEPTHS_BUTTON_EVENTS_H

typedef enum {
    EVENT_NOT_HANDLED,
    BUTTON_CLICKED,
    BUTTON_HOVERED,
    BUTTON_UNHOVERED
} ButtonEventType;

typedef struct ButtonEvent {
    SDL_IHM ihm;
    Button button;
    ButtonEventType type;
} ButtonEvent;


ButtonEvent button_clicked(SDL_IHM ihm, Button button);

ButtonEvent event_not_handled(SDL_IHM ihm, Button button);

ButtonEvent button_hovered(SDL_IHM ihm, Button button);

ButtonEvent button_unhovered(SDL_IHM ihm, Button button);

#endif //DOOMDEPTHS_BUTTON_EVENTS_H
