
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL.h"
#include "sdl_town_controller.h"
#include "in/sdl/components/point/point.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/color/sdl_color.h"
#include "port/out/log/log_info.h"

SDL_IHM click_new_run(SDL_IHM ihm);
SDL_IHM click_continue(SDL_IHM ihm);

TownWindow town_window(SDL_IHM ihm) {

    TownWindow w;
    w.is_displayed = true;
    SDL_Color buttons_background_color = get_color(SDL_RED);
    SDL_Color buttons_hover_color = get_color(SDL_MIDDLE_RED);

    w.newRunButton = create_button(ihm, "NEW RUN", (Point) {100, 200}, &click_new_run);
    w.newRunButton = color_button(
            buttons_background_color,
            buttons_hover_color,
            w.newRunButton
            );

    w.continueButton = create_button(ihm, "CONTINUE", (Point) {100, 300}, &click_continue);
    w.continueButton = color_button(
            buttons_background_color,
            buttons_hover_color,
            w.continueButton
            );

    return w;
}

void draw_town_window(SDL_Renderer *renderer, TownWindow town) {
    if(!town.is_displayed) return;

    drawButton(renderer, town.newRunButton);
    drawButton(renderer, town.continueButton);
}

SDL_IHM click_new_run(SDL_IHM ihm) {
    log_info("Clicked on new run");
    return ihm;
}

SDL_IHM click_continue(SDL_IHM ihm) {
    log_info("Clicked on continue");
    return ihm;
}

SDL_IHM town_handle_event(SDL_Event event, SDL_IHM ihm) {
    TownWindow t = ihm.town_window;
    ButtonClicked new_run_clicked = button_handle_event(ihm, event, ihm.town_window.newRunButton);
    new_run_clicked.ihm->town_window.newRunButton =
    //ihm.town_window.continueButton = button_handle_event(ihm, event, ihm.town_window.continueButton);

    return ihm;
}