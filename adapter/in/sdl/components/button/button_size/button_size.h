
//
// Created by Theo OMNES on 10/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_SIZE_H
#define DOOMDEPTHS_BUTTON_SIZE_H

#include <stdint.h>
#include "in/sdl/components/padding/padding.h"

typedef enum {
    ABSOLUTE,
    WINDOW_RELATIVE,
    TEXT_FIT
} ButtonSizeType;

typedef struct ButtonSize {
    ButtonSizeType size_type;
    Padding padding;
    int8_t window_percentage; // [0-100]
    uint16_t height;
    uint16_t width;
} ButtonSize;

ButtonSize absolute_button_size(uint16_t height, uint16_t width, Padding padding);

ButtonSize window_relative_button_size(uint16_t window_percentage, Padding padding);

ButtonSize text_fit_relative_button_size(Padding padding);


#endif //DOOMDEPTHS_BUTTON_SIZE_H
