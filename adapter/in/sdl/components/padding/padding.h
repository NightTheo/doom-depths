
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_PADDING_H
#define DOOMDEPTHS_PADDING_H

typedef struct SDL_Rect SDL_Rect;
typedef struct Button Button;

typedef enum {CONTENT_BOX, BORDER_BOX} BoxSizing;

typedef struct Padding Padding;
struct Padding{
    int horizontal;
    int vertical;
    BoxSizing box_sizing;
};

Padding padding_asymetric(int horizontal, int vertical);

Padding padding_symetric(int padding);

Padding box_sizing(Padding padding, BoxSizing box_sizing);

SDL_Rect padding_rect(SDL_Rect rect, Padding p);

Button padding_button(Padding padding, Button button);

#endif //DOOMDEPTHS_PADDING_H
