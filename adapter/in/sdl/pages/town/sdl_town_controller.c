
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL.h"
#include "sdl_town_controller.h"
#include "in/sdl/components/point/point.h"
#include "in/sdl/components/color/sdl_color.h"
#include "port/out/log/log_info.h"
#include "in/sdl/components/button/button_events/button_events.h"
#include "port/in/command/new_run.h"
#include "port/in/command/continue_last_run.h"
#include "port/out/persistence/intern_game_state/game_state.h"
#include "port/out/persistence/intern_game_state/get_map.h"
#include "port/out/log/log_error.h"

ButtonEvent click_new_run(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);
ButtonEvent click_continue(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

TownWindow town_handle_aria_next(SDL_IHM ihm, SDL_Event event);

TownWindow select_town_button_by_id(const char *id, SDL_IHM ihm);

TownWindow town_window(SDL_IHM ihm) {
    TownWindow town;
    ButtonColor color = button_color(
            get_color(SDL_DARK_RED),
            get_color(SDL_RED),
            get_color(SDL_GREY)
    );

    ButtonSize size = window_relative_button_size(70);
    ButtonCallback on_click_new_run = no_callback_param(&click_new_run);
    town.new_run_button = create_text_button("new_run_button", ihm, "NEW RUN", (Point) {100, 200}, size, on_click_new_run);
    town.new_run_button = color_button(color, town.new_run_button);
    town.new_run_button = border_radius_button(3, town.new_run_button);

    ButtonCallback on_click_continue = no_callback_param(&click_continue);
    town.continue_button = create_text_button("continue_button", ihm, "CONTINUE", (Point) {100, 300}, size, on_click_continue);
    town.continue_button = color_button(color, town.continue_button);
    town.continue_button = border_radius_button(3, town.continue_button);

    Aria aria = create_aria(2);
    aria_add(aria, town.new_run_button.id);
    aria_add(aria, town.continue_button.id);
    town.aria = aria;

    return town;
}

void draw_town_window(SDL_Renderer *renderer, TownWindow town) {
    draw_button(renderer, town.new_run_button);
    draw_button(renderer, town.continue_button);
}


ButtonEvent click_new_run(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("Clicked on new run");
    new_run();
    Button b = ihm.page.town.new_run_button;
    ihm.current_page = MAP_PAGE;
    ihm.page.map = fill_map_page(ihm, get_map());
    return button_clicked(ihm, b);
}

ButtonEvent click_continue(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("Clicked on continue");
    continue_last_run();
    Button b = ihm.page.town.continue_button;
    ihm.current_page = MAP_PAGE;
    ihm.page.map = fill_map_page(ihm, get_map());
    return button_clicked(ihm, b);
}

SDL_IHM town_handle_event(SDL_Event event, SDL_IHM ihm) {
    ihm.page.town = town_handle_aria_next(ihm, event);

    ButtonEvent new_run_event = button_handle_event(ihm, event, ihm.page.town.new_run_button);
    ihm = new_run_event.ihm;
    ihm.page.town.new_run_button = new_run_event.button;

    ButtonEvent continue_event = button_handle_event(ihm, event, ihm.page.town.continue_button);
    ihm = continue_event.ihm;
    ihm.page.town.continue_button = continue_event.button;
    return ihm;
}

TownWindow town_handle_aria_next(SDL_IHM ihm, SDL_Event event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB) {
        ihm.page.town.aria = aria_next(ihm.page.town.aria);
    }
    const char *selected_id = ihm.page.town.aria.selected->id;
    if(selected_id == NULL) return ihm.page.town;

    return select_town_button_by_id(selected_id, ihm);
}

TownWindow select_town_button_by_id(const char *id, SDL_IHM ihm) {
    if(strcmp(id, ihm.page.town.new_run_button.id) == 0) {
        ihm.page.town.new_run_button = select_button(ihm.page.town.new_run_button);
        ihm.page.town.continue_button = unselect_button(ihm.page.town.continue_button);
    } else if(strcmp(id, ihm.page.town.continue_button.id) == 0) {
        ihm.page.town.continue_button = select_button(ihm.page.town.continue_button);
        ihm.page.town.new_run_button = unselect_button(ihm.page.town.new_run_button);
    } else {
        log_error("Unknown button id [%s]", id);
    }
    return ihm.page.town;
}

SDL_IHM update_town_page(SDL_IHM ihm) {
    ihm.page.town.new_run_button = size_button(ihm.window, ihm.page.town.new_run_button);
    ihm.page.town.continue_button = size_button(ihm.window, ihm.page.town.continue_button);
    return ihm;
}