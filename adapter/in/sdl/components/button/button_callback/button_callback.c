
//
// Created by Theo OMNES on 11/10/2023.
//

#include "button_callback.h"

ButtonCallback no_callback_param(Invoke invoke) {
    ButtonCallback callback = {
            .param = {.param_type = VOID},
            .invoke = invoke
    };
    return callback;
}

ButtonCallback position_callback_param(Position position, Invoke invoke) {
    ButtonCallback callback = {
            .param = {
                    .param_type = POSITION,
                    .data = {.position = position}
                    },
            .invoke = invoke
    };
    return callback;
}