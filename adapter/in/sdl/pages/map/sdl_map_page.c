
//
// Created by Theo OMNES on 10/10/2023.
//

#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/button/button_clicked_event.h"
#include "in/sdl/components/point/point.h"
#include "sdl_map_page.h"
#include "port/out/log/log_info.h"
#include "in/sdl/components/color/sdl_color.h"

#define ZONE_CELL_SIZE 50

SDL_IHM click_spawn(SDL_IHM ihm);

SDL_IHM click_on_zone(SDL_IHM ihm);

void draw_grid(SDL_Renderer *renderer,MapPage page);

void draw_zone(SDL_Renderer *renderer,SdlZone zone);

MapPage grid_handle_event(SDL_IHM ihm, SDL_Event event, MapPage map);

MapPage map_page(SDL_IHM ihm) {
    MapPage map;

    ButtonSize size = absolute_button_size(50, 50, (Padding){0,0});

    map.spawn = create_button(ihm, "", (Point) {10, 200}, size, &click_spawn);
    map.spawn = color_button(get_color(SDL_BLUE), get_color(SDL_WHITE), map.spawn);

    return map;
}

MapPage fill_map_page(SDL_IHM ihm, MapPage page, Map map) {
    page.map = map;
    page.grid = malloc(sizeof (SdlZone*) * map.height);
    ButtonSize size = absolute_button_size(
            ZONE_CELL_SIZE,
            ZONE_CELL_SIZE,
            (Padding){.horizontal = 0, .vertical = 0}
            );
    for(int row = 0; row < map.height; row++) {
        page.grid[row] = malloc(sizeof(SdlZone) * map.width);
        for(int col = 0; col < map.width; col++) {
            Point p = {.x = col * ZONE_CELL_SIZE, .y = row * ZONE_CELL_SIZE};
            SdlZone z = {
                    .zone = get_zone_in_map_by_position(map, position(col, row)),
                    .button = create_button(ihm, "", p, size, &click_on_zone),
            };
            z.button.is_visible = z.zone.status != ZONE_EMPTY;
            page.grid[row][col] = z;
        }
    }
    return page;
}

SDL_IHM map_page_handle_event(SDL_Event event, SDL_IHM ihm) {
    MapPage map = ihm.map_page;

    map = grid_handle_event(ihm, event, map);

    ihm.map_page = map;
    return ihm;
}

MapPage grid_handle_event(SDL_IHM ihm, SDL_Event event, MapPage map) {
    for(int row = 0; row < map.map.height; row++) {
        for(int col = 0; col < map.map.width; col++) {
            ButtonClicked clicked = button_handle_event(ihm, event, map.grid[row][col].button);
        }
    }
    return map;
}

SDL_IHM click_spawn(SDL_IHM ihm) {
    log_info("click spawn");
    return ihm;
}

void draw_map_page(SDL_Renderer *renderer, MapPage map_page) {
    if(!map_page.is_displayed) return;
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

SDL_IHM click_on_zone(SDL_IHM ihm) {
    log_info("clicked on zone");
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