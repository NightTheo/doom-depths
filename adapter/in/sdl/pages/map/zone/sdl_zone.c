
//
// Created by Theo OMNES on 10/10/2023.
//

#include "sdl_zone.h"
#include "port/out/log/log_error.h"
#include "in/sdl/components/color/sdl_color.h"
#include "map/map.h"
#include "in/sdl/pages/map/sdl_map_page.h"

Button accessible_button(Button button);

Button not_accessible_button(Button button);

Button style_button_in_zone(SdlZone zone, Map map);

SdlZone style_zone(SdlZone zone, Map map) {
    bool zone_is_visible = zone.zone.status != ZONE_EMPTY && can_display_position_in_sdl_map(zone.position, map);
    if (!zone_is_visible) {
        zone.button.is_visible = false;
        return zone;
    }
    zone.button = style_button_in_zone(zone, map);
    return zone;
}

Button style_button_in_zone(SdlZone zone, Map map) {
    switch (zone.zone.status) {
        case ZONE_NOT_DISCOVERED:
            return player_can_move_to_position_in_map(zone.position, map)
                          ? accessible_button(zone.button)
                          : not_accessible_button(zone.button);
            break;
        case ZONE_FINISHED: {
            ButtonColor color = button_color(
                    get_color(SDL_GREEN),
                    get_color(SDL_GREEN),
                    get_color(SDL_GREEN)
            );
            return color_button(
                    color,
                    zone.button
            );
            break;
        }

        default: {
            log_error("Unknown zone status [%d]", zone.zone.status);
            return zone.button;
        }
    }
}

Button accessible_button(Button button) {
    SDL_Color white = get_color(SDL_WHITE);
    ButtonColor color = button_color(white, get_color(SDL_GREY), white);
    return color_button(
            color,
            button
    );
}

Button not_accessible_button(Button button) {
    SDL_Color grey = get_color(SDL_GREY);
    ButtonColor color = button_color(grey, grey, grey);
    return color_button(
            color,
            button
    );
}