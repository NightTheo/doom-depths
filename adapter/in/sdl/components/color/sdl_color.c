
//
// Created by Theo OMNES on 08/10/2023.
//

#include "sdl_color.h"
#include "port/out/log/log_error.h"


SDL_Color get_color(SDL_COLOR color) {
    switch (color) {
        case SDL_WHITE: return (SDL_Color) {255, 255, 255, 255};
        case SDL_GREEN: return (SDL_Color) {0, 255, 0, 255};
        case SDL_RED: return (SDL_Color) {255, 0, 0, 255};
        case SDL_MIDDLE_RED: return (SDL_Color) {235, 0, 0, 255};
        case SDL_DARK_RED: return (SDL_Color) {200, 0, 0, 255};
        case SDL_BLUE: return (SDL_Color) {0, 0, 255, 255};
        case SDL_GREY: return (SDL_Color) {40, 40, 40, 255};
        case SDL_TRANSPARENT: return (SDL_Color) {0, 0, 0, 0};
        default: {
            log_error("Unknown color [%d]", color);
            return (SDL_Color) {255, 255, 255, 255}; // white by default
        }
    }
}

