
//
// Created by Theo OMNES on 10/10/2023.
//

#include "button_size.h"
#include "port/out/log/log_error.h"
#include "../button.h"
#include "port/out/log/log_info.h"


Button size_button_absolute(Button button);

Button size_button_window_relative(SDL_Window *window, Button button);

Button size_button_texture_fit(Button button);


Button size_button_texture(Button button);

ButtonSize absolute_button_size(uint16_t height, uint16_t width) {
    ButtonSize size;
    size.size_type = ABSOLUTE;
    size.width = width;
    size.height = height;
    return size;
}

ButtonSize window_relative_button_size(uint8_t window_percentage) {
    ButtonSize size;
    size.size_type = WINDOW_RELATIVE;
    size.window_percentage = window_percentage;

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

Button size_button_absolute(Button button) {
    button.button_rect.h = button.size.height;
    button.button_rect.w = button.size.width;
    button = size_button_texture(button);
    return button;
}

Button size_button_window_relative(SDL_Window *window, Button button) {
    int window_width;
    SDL_GetWindowSize(window, &window_width, NULL);
    SDL_QueryTexture(button.texture, NULL, NULL, NULL, &button.button_rect.h);
    button.button_rect.h += 20;
    button.button_rect.w = (window_width * button.size.window_percentage) / 100;
    button.button_rect.x = (window_width - button.button_rect.w) / 2;

    int texture_width, texture_height;
    SDL_QueryTexture(button.texture, NULL, NULL, &texture_width, &texture_height);
    button = size_button_texture(button);
    return button;
}

Button size_button_texture(Button button) {
    int texture_width, texture_height;
    SDL_QueryTexture(button.texture, NULL, NULL, &texture_width, &texture_height);
    SDL_SetTextureScaleMode(button.texture, SDL_ScaleModeBest);
    button.texture_rect = (SDL_Rect) {
            .x = button.button_rect.x + ((button.button_rect.w - texture_width) / 2),
            .y = button.button_rect.y + ((button.button_rect.h - texture_height) / 2),
            .w = texture_width > button.button_rect.w ? button.button_rect.w : texture_width,
            .h = texture_height > button.button_rect.h ? button.button_rect.h : texture_height,
    };
    return button;
}

Button size_button_texture_fit(Button button) {
    SDL_QueryTexture(button.texture, NULL, NULL, &button.button_rect.w, &button.button_rect.h);
    button.texture_rect = button.button_rect;
    return button;
}