
//
// Created by Theo OMNES on 05/10/2023.
//


#include <application/port/in/command/start_ihm.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>

#include "sdl_controller.h"
#include "port/out/log/log_error.h"
#include "in/sdl/pages/map/sdl_map_page.h"
#include "in/sdl/pages/fight/sdl_fight_page.h"
#include "in/sdl/pages/pages.h"

typedef struct InitResult InitResult;
struct InitResult {
    bool is_success;
    SDL_IHM ihm;
};


const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 840;


InitResult init();

void start_event_loop(SDL_IHM ihm, uint16_t FPS);

void close_sdl(SDL_IHM ihm);

SDL_IHM handle_event(SDL_Event e, SDL_IHM ihm);

void draw(SDL_IHM ihm);

void draw_pages(SDL_IHM ihm);

bool event_is_handled(SDL_Event event);

void start_ihm() {
    InitResult init_result = init();
    if (!init_result.is_success) return;

    SDL_IHM ihm = init_result.ihm;
    start_event_loop(ihm, 16);

    close_sdl(ihm);
}

void start_event_loop(SDL_IHM ihm, uint16_t FPS) {
    draw(ihm);
    SDL_Event e;
    bool app_is_running = true;
    while (app_is_running) {
        if (SDL_PollEvent(&e) == 0) continue; // no event
        if (e.type == SDL_QUIT) app_is_running = false;
        if(!event_is_handled(e)) continue;
        ihm = handle_event(e, ihm);
        draw(ihm);
        SDL_Delay(1000/FPS);
    }
}

bool event_is_handled(SDL_Event event) {
    Uint32 type = event.type;
    switch (type) {
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: return true;
        default:
            return false;
    }
}

void draw(SDL_IHM ihm) {
    SDL_SetRenderDrawColor(ihm.renderer, 0, 0, 0, 255);
    SDL_RenderClear(ihm.renderer);

    draw_pages(ihm);

    SDL_RenderPresent(ihm.renderer);
}

void draw_pages(SDL_IHM ihm) {
    SDL_Renderer* renderer = ihm.renderer;
    switch (ihm.current_page) {
        case TOWN_PAGE: return draw_town_window(renderer, ihm.page.town);
        case MAP_PAGE: return draw_map_page(renderer, ihm.page.map);
        case FIGHT_PAGE: return draw_fight_page(renderer, ihm.page.fight, ihm);
        default: {
            log_error("Unknown page [%d]", ihm.current_page);
            return;
        }
    }
}

InitResult init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL_Init Error: %s", SDL_GetError());
        return (InitResult) {false};
    }

    if(!(IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG)) {
        log_error("IMG_Init Error: %s", IMG_GetError());
        return (InitResult) {false};
    }

    if (TTF_Init() < 0) {
        log_error("TTF_Init Error : %s", TTF_GetError());
        return (InitResult) {false};
    }
    TTF_Font *font = TTF_OpenFont("resources/font/OpenSans.ttf", 20);
    if (font == NULL) {
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
    ihm.current_page = TOWN_PAGE;
    ihm.page.town = town_window(ihm);

    return (InitResult) {true, ihm};
}


void close_sdl(SDL_IHM ihm) {
    SDL_DestroyTexture(ihm.page.town.newRunButton.text_texture);
    SDL_DestroyTexture(ihm.page.town.continueButton.text_texture);
    TTF_CloseFont(ihm.font);
    TTF_Quit();
    SDL_DestroyRenderer(ihm.renderer);
    SDL_DestroyWindow(ihm.window);
    SDL_Quit();
}

SDL_IHM handle_event(SDL_Event e, SDL_IHM ihm) {
    switch (ihm.current_page) {
        case TOWN_PAGE: return town_handle_event(e, ihm);
        case MAP_PAGE: return map_page_handle_event(e, ihm);
        case FIGHT_PAGE: return fight_page_handle_event(e, ihm);
        default: {
            log_error("Unknown page [%d]", ihm.current_page);
            return ihm;
        }
    }
}