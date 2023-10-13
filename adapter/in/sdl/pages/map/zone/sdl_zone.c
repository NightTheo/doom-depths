
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
        case ZONE_FINISHED:
            return color_button(
                    get_color(SDL_GREEN),
                    get_color(SDL_GREEN),
                    zone.button
            );
            break;
        default: {
            log_error("Unknown zone status [%d]", zone.zone.status);
            return zone.button;
        }
    }
}

Button accessible_button(Button button) {
    return color_button(
            get_color(SDL_WHITE),
            get_color(SDL_BLUE),
            button
    );
}

Button not_accessible_button(Button button) {
    return color_button(
            get_color(SDL_GREY),
            get_color(SDL_GREY),
            button
    );
}