
//
// Created by Theo OMNES on 19/10/2023.
//

#ifndef DOOMDEPTHS_EVENT_H
#define DOOMDEPTHS_EVENT_H

#include "components/button/button_events/button_events.h"
#include "sdl_controller.h"

typedef enum {
    EVENT_NOT_HANDLED,
    BUTTON_EVENT,
} EventType;

typedef union {
    ButtonEvent button_event;
} SpecificEvent;

typedef struct {
    SDL_IHM ihm;
    EventType type;
    SpecificEvent data;
} Event_bak;

#endif //DOOMDEPTHS_EVENT_H
