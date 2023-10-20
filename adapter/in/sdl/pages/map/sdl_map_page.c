
//
// Created by Theo OMNES on 10/10/2023.
//

#include "in/sdl/components/button/button_events/button_events.h"
#include "in/sdl/components/point/point.h"
#include "sdl_map_page.h"
#include "port/out/log/log_info.h"
#include "in/sdl/components/color/sdl_color.h"
#include "port/out/log/log_error.h"
#include "port/in/command/player_enter_zone.h"

const int ZONE_CELL_SIZE = 70;

ButtonEvent click_zone(SDL_IHM ihm, ButtonCallbackParam param);

void draw_grid(SDL_Renderer *renderer,MapPage page);

void draw_zone(SDL_Renderer *renderer,SdlZone zone);

SDL_IHM grid_handle_event(SDL_IHM ihm, SDL_Event event, MapPage map);

SdlZone zone_button_at(SDL_IHM ihm, Map map, int row, int col);

SDL_IHM enter_fight_page(SDL_IHM ihm);

MapPage fill_map_page(SDL_IHM ihm, Map map) {
    MapPage page = ihm.page.map;
    page.map = map;
    page.grid = malloc(sizeof (SdlZone*) * map.height);
    for(int row = 0; row < map.height; row++) {
        page.grid[row] = malloc(sizeof(SdlZone) * map.width);
        for(int col = 0; col < map.width; col++) {
            page.grid[row][col] = zone_button_at(ihm, map, row, col);
        }
    }
    return page;
}

SdlZone zone_button_at(SDL_IHM ihm, Map map, int row, int col) {
    ButtonSize size = absolute_button_size(
            ZONE_CELL_SIZE,
            ZONE_CELL_SIZE);
    Point button_point = {.x = col * (ZONE_CELL_SIZE + 1), .y = row * (ZONE_CELL_SIZE + 1)};
    ButtonCallback on_click_zone = position_callback_param(position(col, row), &click_zone);
    char* id = malloc(sizeof(char) * 20);
    snprintf(id, 20, "zone_button_%d_%d", row, col);
    SdlZone z = {
            .zone = get_zone_in_map_by_position(map, position(col, row)),
            .button = size_button(ihm.window, create_button(id, button_point, size, on_click_zone)),
            .position = position(col, row),
    };
    bool zone_is_visible = z.zone.status != ZONE_EMPTY;
    z.button.state = zone_is_visible
            ? BUTTON_NORMAL
            : BUTTON_HIDEN;
    z = style_zone(z, map);
    return z;
}

SDL_IHM map_page_handle_event(SDL_Event event, SDL_IHM ihm) {
    return grid_handle_event(ihm, event, ihm.page.map);
}

SDL_IHM grid_handle_event(SDL_IHM ihm, SDL_Event event, MapPage map) {
    for(int row = 0; row < map.map.height; row++) {
        for(int col = 0; col < map.map.width; col++) {
            ButtonEvent handled_event = button_handle_event(ihm, event, map.grid[row][col].button);
            ihm = handled_event.ihm;
            if(ihm.current_page == MAP_PAGE) ihm.page.map.grid[row][col].button = handled_event.button;
        }
    }
    return ihm;
}

void draw_map_page(SDL_Renderer *renderer, MapPage map_page) {
    draw_grid(renderer, map_page);
}

void draw_grid(SDL_Renderer *renderer,MapPage page) {
    for(int row = 0; row < page.map.height; row++) {
        for(int col = 0; col < page.map.width; col++) {
            draw_zone(renderer, page.grid[row][col]);
        }
    }
}

void draw_zone(SDL_Renderer *renderer, SdlZone zone) {
    draw_button(renderer, zone.button);
}

ButtonEvent click_zone(SDL_IHM ihm, ButtonCallbackParam param) {
    if(param.param_type != POSITION) {
        log_error("Illegal param type [%d]", param.param_type);
        return button_event_not_handled(ihm, ihm.page.map.grid[0][0].button);
    }
    char* p = position_to_string(param.data.position);
    log_info("clicked on zone %s", p);
    free(p);

    player_enter_zone(param.data.position);
    Button button = ihm.page.map.grid[param.data.position.zone_y][param.data.position.zone_x].button;
    return button_clicked(enter_fight_page(ihm), button);
}

SDL_IHM enter_fight_page(SDL_IHM ihm) {
    ihm.current_page = FIGHT_PAGE;
    ihm.page.fight = fill_fight_page(ihm);
    ihm = update_fight_page(ihm);
    return ihm;
}

bool can_display_position_in_sdl_map(Position p, Map m) {
    if (!position_is_in_map_and_not_empty(p, m)) return false;
    if (positions_a_equals_b(m.spawn, p)) return true;
    if (position_is_finished(p, m)) return true;

    return position_is_finished(up_from(p), m)
           || position_is_finished(down_from(p), m)
           || position_is_finished(right_from(p), m)
           || position_is_finished(left_from(p), m);
}