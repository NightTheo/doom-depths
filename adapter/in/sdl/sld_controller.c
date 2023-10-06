
//
// Created by Theo OMNES on 05/10/2023.
//

#include <stdbool.h>

#include <application/port/in/command/start_ihm.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

#include "port/out/log/log_error.h"


typedef struct Padding Padding;
struct Padding{
    int horizontal;
    int vertical;
};

typedef struct Button Button;
struct Button{
    SDL_Rect rect;
    SDL_Texture* text_texture;
    SDL_Color bg_color;
    Padding padding;
};

typedef struct Point Point;
struct Point{
    int x;
    int y;
};

typedef struct TownWindow TownWindow;
struct TownWindow {
    Button newRunButton;
    Button continueButton;
};

typedef struct SDL_IHM SDL_IHM;
struct SDL_IHM {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    TownWindow town_window;
};

typedef struct InitResult InitResult;
struct InitResult {
    bool is_success;
    SDL_IHM ihm;
};



const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 840;


InitResult init();

void close(SDL_IHM ihm);

SDL_Texture * load_texture(const char *path, SDL_Renderer *renderer);

void handle_event(SDL_Event e, SDL_IHM ihm);

void handle_clicked(SDL_Event event, SDL_IHM ihm);

void handle_mouse_moved(SDL_Event event, SDL_IHM ihm);

void start_event_loop(SDL_IHM ihm);

SDL_Surface *load_surface(const char *path);

void draw(SDL_IHM ihm);

void drawButton(SDL_Renderer *renderer, Button *button);

Button create_button(SDL_IHM *ihm, const char *text, Point p, SDL_Color background_color);

Button horizontal_padding(Button button, int padding);

Button vertical_padding(Button button, int padding);

Button padding(Button button, int horizontal, int vertical);

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

    drawButton(ihm.renderer, &ihm.town_window.newRunButton);
    drawButton(ihm.renderer, &ihm.town_window.continueButton);

    SDL_RenderPresent(ihm.renderer);
}

Button create_button(SDL_IHM *ihm, const char *text, Point p, SDL_Color background_color) {
    Button button;
    button.rect.x = p.x;
    button.rect.y = p.y;

    SDL_Surface* textSurface = TTF_RenderText_Solid(ihm->font, text, (SDL_Color){255, 255, 255, 255});
    button.text_texture = SDL_CreateTextureFromSurface(ihm->renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_QueryTexture(button.text_texture, NULL, NULL, &button.rect.w, &button.rect.h);
    button.bg_color = background_color;
    return button;
}

void drawButton(SDL_Renderer *renderer, Button *button) {
    SDL_SetRenderDrawColor(renderer, button->bg_color.r, button->bg_color.g, button->bg_color.b, button->bg_color.a);
    SDL_RenderFillRect(renderer, &button->rect);

    Padding p = button->padding;
    SDL_Rect textRect = {
            button->rect.x + p.horizontal,
            button->rect.y + p.vertical,
            button->rect.w - (2 * p.horizontal),
            button->rect.h - (2 * p.vertical)
    };
    SDL_RenderCopy(renderer, button->text_texture, NULL, &textRect);
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
    TTF_Font *font = TTF_OpenFont("OpenSans.ttf", 24);
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

    SDL_Color color = {200, 0, 0, 255};

    Button newRunButton = create_button(&ihm, "NEW RUN", (Point) {100, 200}, color);
    Button continueButton = create_button(&ihm, "CONTINUE", (Point) {100, 300}, color);

    ihm.town_window.newRunButton = padding(newRunButton, 30, 10);
    ihm.town_window.continueButton = padding(continueButton, 30, 10);

    return (InitResult) {true, ihm};
}

Button padding(Button button, int horizontal, int vertical) {
    button.rect.w += 2 * horizontal;
    button.rect.h += 2 * vertical;
    button.padding.horizontal = horizontal;
    button.padding.vertical = vertical;
    return button;
}


Button vertical_padding(Button button, int padding) {
    button.rect.h += 2 * padding;
    button.padding.vertical = padding;
    return button;
}

Button horizontal_padding(Button button, int padding) {
    button.rect.w += 2 * padding;
    button.padding.horizontal = padding;
    return button;
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
    switch (e.type) {
        case SDL_MOUSEBUTTONUP:
            return handle_clicked(e, ihm);
        case SDL_MOUSEMOTION:
            return handle_mouse_moved(e, ihm);
        default:
            return;
    }
}

void handle_mouse_moved(SDL_Event event, SDL_IHM ihm) {

}

void handle_clicked(SDL_Event event, SDL_IHM ihm) {

}
