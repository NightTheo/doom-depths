
//
// Created by Theo OMNES on 15/10/2023.
//

#include "in/sdl/components/button/button.h"
#include "screen_position.h"
#include "port/out/log/log_error.h"
#include "port/out/log/log_info.h"

SDL_Rect position_rect(PositionInScreen position, SDL_Rect rect, SDL_Rect zone);

int position_rect_x(HorizontalPosition position, SDL_Rect rect, SDL_Rect zone);

int position_rect_y(VerticalPosition position, SDL_Rect rect, SDL_Rect zone);

Button position_button(PositionInScreen position, Button button, SDL_Rect zone) {
    button.position = position;
    log_info("zone_x = %d, zone_y = %d", zone.x, zone.y);
    button.button_rect = position_rect(position, button.button_rect, zone);
    PositionInScreen centered = {.horizontal = POSITION_CENTER, .vertical = POSITION_CENTER};
    button.texture_rect = position_rect(centered, button.texture_rect, button.button_rect);
    return button;
}

SDL_Rect position_rect(PositionInScreen position, SDL_Rect rect, SDL_Rect zone) {
    rect.x = position_rect_x(position.horizontal, rect, zone);
    rect.y = position_rect_y(position.vertical, rect, zone);
    return rect;
}

int position_rect_x(HorizontalPosition position, SDL_Rect rect, SDL_Rect zone) {

    log_info("zone_width = %d", zone);
    switch (position) {
        case POSITION_START:
            return zone.x;
        case POSITION_END:
            return zone.x + zone.w - rect.w;
        case POSITION_CENTER:
            return zone.x + ((zone.w - rect.w) / 2);
        case NOT_POSITIONED: return rect.x;
        default: {
            log_error("Unknown horizontal position [%d]", position);
            return rect.x;
        }
    }
}

int position_rect_y(VerticalPosition position, SDL_Rect rect, SDL_Rect zone) {
    switch (position) {
        case POSITION_START:
            return zone.y;
        case POSITION_END:
            return zone.y + zone.h - rect.h;
        case POSITION_CENTER:
            return zone.y + ((zone.h - rect.h) / 2);
        case NOT_POSITIONED: return rect.y;
        default: {
            log_error("Unknown vertical position [%d]", position);
            return rect.y;
        }
    }
}

