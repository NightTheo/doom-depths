
//
// Created by Theo OMNES on 05/10/2023.
//

#include <stdbool.h>

#include <application/port/in/command/start_ihm.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

#include "sdl_controller.h"
#include "port/out/log/log_error.h"
#include "in/sdl/components/button/button.h"


typedef struct InitResult InitResult;
struct InitResult {
    bool is_success;
    SDL_IHM ihm;
};



const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 840;


InitResult init();

void start_event_loop(SDL_IHM ihm);

void close(SDL_IHM ihm);

SDL_Texture * load_texture(const char *path, SDL_Renderer *renderer);

void handle_event(SDL_Event e, SDL_IHM ihm);


SDL_Surface *load_surface(const char *path);

void draw(SDL_IHM ihm);

void start_ihm() {
    InitResult init_result = init();
    if (init_result.is_success == false) return;

    SDL_IHM ihm = init_result.ihm;
    start_event_loop(ihm);

    close(ihm);
}

void start_event_loop(SDL_IHM ihm) {
    SDL_Event e;
    bool app_is_up = true;
    while (app_is_up) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) app_is_up = false;
        }
        handle_event(e, ihm);
        draw(ihm);
    }
}


void draw(SDL_IHM ihm) {
    SDL_SetRenderDrawColor(ihm.renderer, 0, 0, 0, 255);
    SDL_RenderClear(ihm.renderer);

    drawButton(ihm.renderer, ihm.town_window.newRunButton);
    drawButton(ihm.renderer, ihm.town_window.continueButton);

    SDL_RenderPresent(ihm.renderer);
}

InitResult init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL_Init Error: %s", SDL_GetError());
        return (InitResult) {false};
    }

    if (TTF_Init() < 0) {
        log_error("TTF_Init Error : %s", TTF_GetError());
        return (InitResult) {false};
    }
    TTF_Font *font = TTF_OpenFont("resources/font/OpenSans.ttf", 24);
    if(font == NULL) {
        log_error("TTF_OpenFont Error : %s", TTF_GetError());
        return (InitResult) {false};
    }

    SDL_Window *window = SDL_CreateWindow("DoomDepths", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        log_error("SDL_CreateWindow Error: %s", SDL_GetError());
        return (InitResult) {false};
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        log_error("SDL_CreateRenderer : %s", SDL_GetError());
        return (InitResult) {false};;
    }

    SDL_IHM ihm;
    ihm.window = window;
    ihm.renderer = renderer;
    ihm.font = font;
    ihm.town_window = town_window(ihm);

    return (InitResult) {true, ihm};
}


void close(SDL_IHM ihm) {
    SDL_DestroyTexture(ihm.town_window.newRunButton.text_texture);
    SDL_DestroyTexture(ihm.town_window.continueButton.text_texture);
    TTF_CloseFont(ihm.font);
    TTF_Quit();
    SDL_DestroyRenderer(ihm.renderer);
    SDL_DestroyWindow(ihm.window);
    SDL_Quit();
}

SDL_Texture * load_texture(const char *path, SDL_Renderer *renderer) {
    SDL_Surface *surface = load_surface(path);
    if(surface == NULL) {
        log_error("Cannot load media at [%s]", path);
        return NULL;
    }

    SDL_Texture *media = SDL_CreateTextureFromSurface(renderer, surface);
    if(media == NULL) {
        log_error("SDL_CreateTextureFromSurface: %s", SDL_GetError());
        return NULL;
    }

    return media;
}

// TODO load not only BMP
SDL_Surface *load_surface(const char *path) {
    SDL_Surface *surface = SDL_LoadBMP(path);
    if (surface == NULL) {
        log_error("SDL_LoadBMP: %s", "with path [%s]", SDL_GetError(), path);
        return NULL;
    }
    return surface;
}

void handle_event(SDL_Event e, SDL_IHM ihm) {

}