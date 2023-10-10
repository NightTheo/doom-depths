
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_H
#define DOOMDEPTHS_BUTTON_H

#include "SDL2/SDL.h"
#include "in/sdl/components/padding/padding.h"
#include "stdbool.h"

typedef struct Point Point;
typedef struct SDL_IHM SDL_IHM;

typedef  SDL_IHM (*button_callback)(SDL_IHM ihm);

typedef struct ButtonClicked ButtonClicked;

typedef struct Button Button;
struct Button{
    bool is_visible;
    SDL_Rect rect;
    SDL_Texture* text_texture;
    SDL_Color current_bg_color;
    SDL_Color bg_color;
    SDL_Color bg_hover_color;
    Padding padding;
    button_callback callback;
};


void draw_button(SDL_Renderer *renderer, Button button);

Button padding_button(Padding padding, Button button);

Button create_button(SDL_IHM ihm, const char *text, Point p, button_callback callback);

Button color_button(SDL_Color background_color, SDL_Color hover_color, Button button);

ButtonClicked button_handle_event(SDL_IHM ihm, SDL_Event event, Button button);

bool button_at_point(Button button, Point point);

#endif //DOOMDEPTHS_BUTTON_H
