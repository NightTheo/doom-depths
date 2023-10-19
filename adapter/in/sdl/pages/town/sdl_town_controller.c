
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

ButtonEvent click_new_run(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);
ButtonEvent click_continue(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

TownWindow town_window(SDL_IHM ihm) {
    TownWindow w;
    ButtonColor color = button_color(
            get_color(SDL_DARK_RED),
            get_color(SDL_RED),
            get_color(SDL_GREY)
    );

    ButtonSize size = window_relative_button_size(70);
    ButtonCallback on_click_new_run = no_callback_param(&click_new_run);
    w.newRunButton = create_text_button(ihm, "NEW RUN", (Point) {100, 200}, size, on_click_new_run);
    w.newRunButton = color_button(color,w.newRunButton);
    w.newRunButton = border_radius_button(3, w.newRunButton);

    ButtonCallback on_click_continue = no_callback_param(&click_continue);
    w.continueButton = create_text_button(ihm, "CONTINUE", (Point) {100, 300}, size, on_click_continue);
    w.continueButton = color_button(color,w.continueButton);
    w.continueButton = border_radius_button(3, w.continueButton);

    return w;
}

void draw_town_window(SDL_Renderer *renderer, TownWindow town) {
    draw_button(renderer, town.newRunButton);
    draw_button(renderer, town.continueButton);
}


ButtonEvent click_new_run(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("Clicked on new run");
    new_run();
    Button b = ihm.page.town.newRunButton;
    ihm.current_page = MAP_PAGE;
    ihm.page.map = fill_map_page(ihm, get_map());
    return button_clicked(ihm, b);
}

ButtonEvent click_continue(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("Clicked on continue");
    continue_last_run();
    Button b = ihm.page.town.continueButton;
    ihm.current_page = MAP_PAGE;
    ihm.page.map = fill_map_page(ihm, get_map());
    return button_clicked(ihm, b);
}

SDL_IHM town_handle_event(SDL_Event event, SDL_IHM ihm) {
    TownWindow t = ihm.page.town;
    ButtonEvent new_run_event = button_handle_event(ihm, event, ihm.page.town.newRunButton);
    ihm = new_run_event.ihm;
    ihm.page.town.newRunButton = new_run_event.button;

    ButtonEvent continue_event = button_handle_event(ihm, event, ihm.page.town.continueButton);
    ihm = continue_event.ihm;
    ihm.page.town.continueButton = continue_event.button;

    return ihm;
}

SDL_IHM update_style_town_page(SDL_IHM ihm) {
    ihm.page.town.newRunButton = size_button(ihm.window, ihm.page.town.newRunButton);
    ihm.page.town.continueButton = size_button(ihm.window, ihm.page.town.continueButton);
    return ihm;
}