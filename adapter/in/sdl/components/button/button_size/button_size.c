
//
// Created by Theo OMNES on 10/10/2023.
//

#include "button_size.h"

ButtonSize absolute_button_size(uint16_t height, uint16_t width, Padding padding) {
    ButtonSize size;
    size.size_type = ABSOLUTE;
    size.width = width;
    size.height = height;
    size.padding = padding;

    return size;
}

ButtonSize window_relative_button_size(uint16_t window_percentage, Padding padding) {
    ButtonSize size;
    size.size_type = WINDOW_RELATIVE;
    size.window_percentage = window_percentage;
    size.padding = padding;

    return size;
}

ButtonSize text_fit_relative_button_size(Padding padding) {
    ButtonSize size;
    size.size_type = TEXT_FIT;
    size.padding = padding;

    return size;
}