
//
// Created by Theo OMNES on 10/10/2023.
//

#include "button_size.h"
#include "port/out/log/log_error.h"
#include "../button.h"


Button size_button_absolute(Button button);

Button size_button_window_relative(SDL_Window *window, Button button);

Button size_button_texture_fit(Button button);


ButtonSize absolute_button_size(uint16_t height, uint16_t width, Padding padding) {
    ButtonSize size;
    size.size_type = ABSOLUTE;
    size.width = width;
    size.height = height;
    size.padding = padding;

    return size;
}

ButtonSize window_relative_button_size(uint8_t window_percentage, Padding padding) {
    ButtonSize size;
    size.size_type = WINDOW_RELATIVE;
    size.window_percentage = window_percentage;
    size.padding = padding;

    return size;
}

ButtonSize texture_fit_relative_button_size(Padding padding) {
    ButtonSize size;
    size.size_type = TEXTURE_FIT;
    size.padding = padding;

    return size;
}

Button size_button(SDL_Window *window, Button button) {
    switch (button.size.size_type) {
        case ABSOLUTE: return size_button_absolute(button);
        case WINDOW_RELATIVE: return size_button_window_relative(window, button);
        case TEXTURE_FIT: return size_button_texture_fit(button);
        default: {
            log_error("Unknown size_type [%d]", button.size.size_type);
            return button;
        }
    }
}

Button size_button_texture_fit(Button button) {
    SDL_QueryTexture(button.texture, NULL, NULL, &button.rect.w, &button.rect.h);
    return button;
}

Button size_button_window_relative(SDL_Window *window, Button button) {
    int window_width;
    SDL_GetWindowSize(window, &window_width, NULL);
    SDL_QueryTexture(button.texture, NULL, NULL, NULL, &button.rect.h);
    button.rect.h += 20;
    button.rect.w = (window_width * button.size.window_percentage) / 100;
    button.rect.x = (window_width - button.rect.w) / 2;
    return button;
}

Button size_button_absolute(Button button) {
    button.rect.h = button.size.height;
    button.rect.w = button.size.width;
    return button;
}