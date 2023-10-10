
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_H
#define DOOMDEPTHS_BUTTON_H

#include "SDL2/SDL.h"
#include "in/sdl/components/padding/padding.h"
#include "stdbool.h"
#include "in/sdl/components/button/button_size/button_size.h"

typedef struct Point Point;
typedef struct SDL_IHM SDL_IHM;

typedef  SDL_IHM (*button_callback)(SDL_IHM ihm);

typedef struct ButtonClicked ButtonClicked;

typedef struct {
    SDL_Color current;
    SDL_Color background;
    SDL_Color hover;
} ButtonColor;

typedef struct Button Button;
struct Button{
    bool is_visible;
    SDL_Rect rect;
    SDL_Texture* text_texture;
    ButtonColor color;
    button_callback callback;
    ButtonSize size;
};

ButtonColor button_color(SDL_Color current, SDL_Color background, SDL_Color hover);

void draw_button(SDL_Renderer *renderer, Button button);

Button padding_button(Padding padding, Button button);

Button create_button(SDL_IHM ihm, const char *text, Point p, ButtonSize size, button_callback callback);

Button color_button(SDL_Color background_color, SDL_Color hover_color, Button button);

ButtonClicked button_handle_event(SDL_IHM ihm, SDL_Event event, Button button);

bool button_at_point(Button button, Point point);

#endif //DOOMDEPTHS_BUTTON_H
