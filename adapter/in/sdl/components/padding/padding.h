
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_PADDING_H
#define DOOMDEPTHS_PADDING_H

typedef struct Button Button;
typedef struct SDL_Rect SDL_Rect;

typedef struct Padding Padding;
struct Padding{
    int horizontal;
    int vertical;
};

void padding_rect(SDL_Rect *rect, Padding p);

#endif //DOOMDEPTHS_PADDING_H
