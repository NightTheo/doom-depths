
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL.h"
#include "sdl_town_controller.h"
#include "in/sdl/components/point/point.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/color/sdl_color.h"
#include "port/out/log/log_info.h"

void click_new_run();
void click_continue();

TownWindow town_window(SDL_IHM ihm) {

    TownWindow w;
    w.is_displayed = true;
    SDL_Color buttons_background_color = get_color(SDL_RED);
    SDL_Color buttons_hover_color = get_color(SDL_DARK_RED);

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

void click_new_run() {
    log_info("Clicked on new run");
}

void click_continue() {
    log_info("Clicked on continue");
}

TownWindow town_handle_event(SDL_Event event, TownWindow town) {
    town.newRunButton = button_handle_event(event, town.newRunButton);
    town.continueButton = button_handle_event(event, town.continueButton);

    return town;
}