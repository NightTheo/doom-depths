
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL.h"
#include "sdl_town_controller.h"
#include "in/sdl/components/point/point.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/color/sdl_color.h"
#include "port/out/log/log_info.h"
#include "in/sdl/components/button/button_clicked_event.h"
#include "port/in/command/new_run.h"
#include "port/in/command/continue_last_run.h"
#include "port/out/persistence/intern_game_state/game_state.h"
#include "port/out/persistence/intern_game_state/get_map.h"

SDL_IHM click_new_run(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);
SDL_IHM click_continue(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

TownWindow town_window(SDL_IHM ihm) {
    TownWindow w;
    w.is_displayed = true;
    SDL_Color buttons_background_color = get_color(SDL_RED);
    SDL_Color buttons_hover_color = get_color(SDL_DARK_RED);

    ButtonSize size = window_relative_button_size(70, (Padding){0, 5});
    ButtonCallback on_click_new_run = no_callback_param(&click_new_run);
    w.newRunButton = create_button(ihm, "NEW RUN", (Point) {100, 200}, size, on_click_new_run);
    w.newRunButton = color_button(
            buttons_background_color,
            buttons_hover_color,
            w.newRunButton
            );

    ButtonCallback on_click_continue = no_callback_param(&click_continue);
    w.continueButton = create_button(ihm, "CONTINUE", (Point) {100, 300}, size, on_click_continue);
    w.continueButton = color_button(
            buttons_background_color,
            buttons_hover_color,
            w.continueButton
            );
    return w;
}

void draw_town_window(SDL_Renderer *renderer, TownWindow town) {
    if(!town.is_displayed) return;

    draw_button(renderer, town.newRunButton);
    draw_button(renderer, town.continueButton);
}


SDL_IHM click_new_run(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("Clicked on new run");
    new_run();
    ihm.town_window.is_displayed = false;
    ihm.map_page.is_displayed = true;
    ihm.map_page = fill_map_page(ihm, ihm.map_page, get_map());
    return ihm;
}

SDL_IHM click_continue(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("Clicked on continue");
    continue_last_run();
    ihm.town_window.is_displayed = false;
    ihm.map_page.is_displayed = true;
    ihm.map_page = fill_map_page(ihm, ihm.map_page, get_map());
    return ihm;
}

SDL_IHM town_handle_event(SDL_Event event, SDL_IHM ihm) {
    TownWindow t = ihm.town_window;
    ButtonClicked new_run_clicked = button_handle_event(ihm, event, ihm.town_window.newRunButton);
    ihm = new_run_clicked.ihm;
    ihm.town_window.newRunButton = new_run_clicked.button;

    ButtonClicked continue_clicked = button_handle_event(ihm, event, ihm.town_window.continueButton);
    ihm = continue_clicked.ihm;
    ihm.town_window.continueButton = continue_clicked.button;

    return ihm;
}