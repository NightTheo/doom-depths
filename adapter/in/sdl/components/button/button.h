
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_H
#define DOOMDEPTHS_BUTTON_H

#include "SDL2/SDL.h"
#include "in/sdl/components/padding/padding.h"
#include "stdbool.h"
#include "in/sdl/components/button/button_size/button_size.h"
#include "in/sdl/components/button/button_callback/button_callback.h"
#include "in/sdl/components/point/point.h"

typedef struct ButtonEvent ButtonEvent;
typedef struct {
    SDL_Color current;
    SDL_Color background;
    SDL_Color hover;
} ButtonColor;

typedef struct Button Button;
struct Button{
    bool is_visible;
    SDL_Rect rect;
    SDL_Texture* texture;
    ButtonColor color;
    ButtonCallback callback;
    ButtonSize size;
};

ButtonColor button_color(SDL_Color current, SDL_Color background, SDL_Color hover);

void draw_button(SDL_Renderer *renderer, Button button);

Button padding_button(Padding padding, Button button);

Button create_button(SDL_IHM ihm, Point p, ButtonSize size, ButtonCallback callback);

Button create_text_button(SDL_IHM ihm, const char *text, Point p, ButtonSize size, ButtonCallback callback);

Button create_img_button(SDL_IHM ihm, const char *img_path, Point p, ButtonSize size, ButtonCallback callback);

Button color_button(SDL_Color background_color, SDL_Color hover_color, Button button);

ButtonEvent button_handle_event(SDL_IHM ihm, SDL_Event event, Button button);

bool button_at_point(Button button, Point point);

#endif //DOOMDEPTHS_BUTTON_H
