
//
// Created by Theo OMNES on 10/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_SIZE_H
#define DOOMDEPTHS_BUTTON_SIZE_H

#include <stdint.h>
#include <SDL_video.h>
#include "in/sdl/components/padding/padding.h"


typedef struct Button Button;

typedef enum {
    ABSOLUTE,
    WINDOW_RELATIVE,
    TEXTURE_FIT
} ButtonSizeType;

typedef struct ButtonSize {
    ButtonSizeType size_type;
    Padding padding;
    uint8_t window_percentage; // [0-100]
    uint16_t height;
    uint16_t width;
} ButtonSize;

ButtonSize absolute_button_size(uint16_t height, uint16_t width, Padding padding);

ButtonSize window_relative_button_size(uint8_t window_percentage, Padding padding);

ButtonSize texture_fit_relative_button_size(Padding padding);

Button size_button(SDL_Window *window, Button button);


#endif //DOOMDEPTHS_BUTTON_SIZE_H
