
//
// Created by Theo OMNES on 11/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_CALLBACK_H
#define DOOMDEPTHS_BUTTON_CALLBACK_H

#include "stdbool.h"
#include "domain/map/position/position.h"

typedef struct SDL_IHM SDL_IHM;
typedef struct ButtonEvent ButtonEvent;

typedef enum {
    VOID,
    POSITION,
} CallbackParamType;

typedef union {
    Position position;
} CallbackData;

typedef struct {
    CallbackParamType param_type;
    CallbackData data;
} ButtonCallbackParam;

typedef  ButtonEvent (*Invoke)(SDL_IHM ihm, ButtonCallbackParam);

typedef struct {
    Invoke invoke;
    ButtonCallbackParam param;
} ButtonCallback;

ButtonCallback no_callback_param(Invoke invoke);

ButtonCallback position_callback_param(Position position, Invoke invoke);

#endif //DOOMDEPTHS_BUTTON_CALLBACK_H
