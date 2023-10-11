
//
// Created by Theo OMNES on 11/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_CALLBACK_H
#define DOOMDEPTHS_BUTTON_CALLBACK_H

#include "stdbool.h"
#include "map/position/position.h"

typedef struct SDL_IHM SDL_IHM;

typedef enum {
    VOID,
    POSITION,
} CallBackParamType;

typedef union callback_data {
    Position position;
} callback_data;

typedef struct button_callback_param{
    CallBackParamType param_type;
    callback_data data;
} ButtonCallbackParam;

typedef  SDL_IHM (*Invoke)(SDL_IHM ihm, ButtonCallbackParam);

typedef struct ButtonCallback {
    Invoke invoke;
    ButtonCallbackParam param;
} ButtonCallback;

ButtonCallback no_callback_param(Invoke invoke);

ButtonCallback position_callback_param(Position position, Invoke invoke);

#endif //DOOMDEPTHS_BUTTON_CALLBACK_H
