
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL.h"
#include "sdl_town_controller.h"
#include "in/sdl/components/point/point.h"
#include "in/sdl/sdl_controller.h"

TownWindow town_window(SDL_IHM ihm) {
    SDL_Color color = {200, 0, 0, 255};

    TownWindow w;
    Button newRunButton = create_button(ihm, "NEW RUN", (Point) {100, 200}, color);
    Button continueButton = create_button(ihm, "CONTINUE", (Point) {100, 300}, color);

    w.is_displayed = true;
    w.newRunButton = padding_button(newRunButton, 30, 10);
    w.continueButton = padding_button(continueButton, 30, 10);

    return w;
}