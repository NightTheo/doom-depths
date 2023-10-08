
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_H
#define DOOMDEPTHS_BUTTON_H

#include "SDL2/SDL.h"
#include "in/sdl/components/padding/padding.h"

typedef struct SDL_IHM SDL_IHM;
typedef struct Point Point;

typedef struct Button Button;
struct Button{
    SDL_Rect rect;
    SDL_Texture* text_texture;
    SDL_Color bg_color;
    Padding padding;
};

void drawButton(SDL_Renderer *renderer, Button button);

Button padding_button(Button button, int horizontal, int vertical);

Button create_button(SDL_IHM ihm, const char *text, Point p, SDL_Color background_color);

#endif //DOOMDEPTHS_BUTTON_H
