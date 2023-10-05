
//
// Created by Theo OMNES on 05/10/2023.
//

#include <stdbool.h>

#include <application/port/in/command/start_ihm.h>
#include "SDL2/SDL.h"
#include "port/out/log/log_error.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;

void start_ihm() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("DoomDepths", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        log_error("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return;
    }

    surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        log_error("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return;
    }

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);

    //Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }
    }

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}