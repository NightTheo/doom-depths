
//
// Created by Theo OMNES on 10/10/2023.
//

#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/point/point.h"
#include "sdl_map_page.h"
#include "port/out/log/log_info.h"
#include "in/sdl/components/color/sdl_color.h"


SDL_IHM click_spawn(SDL_IHM ihm);

MapPage map_page(SDL_IHM ihm) {
    MapPage map;

    map.spawn = create_button(ihm, "", (Point) {10, 200}, &click_spawn);
    map.spawn = color_button(get_color(SDL_BLUE), get_color(SDL_WHITE), map.spawn);

    return map;
}

SDL_IHM map_page_handle_event(SDL_Event event, SDL_IHM ihm) {
    MapPage map = ihm.map_page;

    // TODO

    ihm.map_page = map;
    return ihm;
}

SDL_IHM click_spawn(SDL_IHM ihm) {
    log_info("click spawn");
    return ihm;
}

void draw_map_page(SDL_Renderer *renderer, MapPage map_page) {
    if(!map_page.is_displayed) return;
    draw_button(renderer, map_page.spawn);
}
