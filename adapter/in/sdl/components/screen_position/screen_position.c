
//
// Created by Theo OMNES on 15/10/2023.
//

#include "in/sdl/components/button/button.h"
#include "screen_position.h"
#include "port/out/log/log_error.h"
#include "port/out/log/log_info.h"

SDL_Rect position_rect(PositionInScreen position, SDL_Rect rect, SDL_Window *window);

int position_rect_x(HorizontalPosition position, SDL_Rect rect, int screen_width);

int position_rect_y(VerticalPosition position, SDL_Rect rect, int screen_height);

Button position_button(PositionInScreen position, Button button, SDL_Window *window) {
    button.position = position;
    button.rect = position_rect(position, button.rect, window);
    return button;
}

SDL_Rect position_rect(PositionInScreen position, SDL_Rect rect, SDL_Window *window) {
    log_info("rect.w = %d, rect.h = %d", rect.w, rect.h);
    int screen_width, screen_height;
    SDL_GetWindowSize(window, &screen_width, &screen_height);
    rect.x = position_rect_x(position.horizontal, rect, screen_width);
    rect.y = position_rect_y(position.vertical, rect, screen_height);
    return rect;
}

int position_rect_x(HorizontalPosition position, SDL_Rect rect, int screen_width) {

    log_info("screen_width = %d", screen_width);
    switch (position) {
        case POSITION_START:
            return 0;
        case POSITION_END:
            return screen_width - rect.w;
        case POSITION_CENTER:
            return (screen_width - rect.w) / 2;
        case NOT_POSITIONED: return rect.x;
        default: {
            log_error("Unknown horizontal position [%d]", position);
            return rect.x;
        }
    }
}

int position_rect_y(VerticalPosition position, SDL_Rect rect, int screen_height) {
    switch (position) {
        case POSITION_START:
            return 0;
        case POSITION_END:
            return screen_height - rect.h;
        case POSITION_CENTER:
            return (screen_height - rect.h) / 2;
        case NOT_POSITIONED: return rect.y;
        default: {
            log_error("Unknown vertical position [%d]", position);
            return rect.y;
        }
    }
}

