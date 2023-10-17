
//
// Created by Theo OMNES on 15/10/2023.
//

#include <SDL_video.h>

#ifndef DOOMDEPTHS_SCREEN_POSITION_H
#define DOOMDEPTHS_SCREEN_POSITION_H

typedef struct SDL_Rect SDL_Rect;
typedef struct Button Button;

enum position_ {
    NOT_POSITIONED,
    POSITION_START,
    POSITION_END,
    POSITION_CENTER,
};

typedef enum position_ VerticalPosition;
typedef enum position_ HorizontalPosition;

typedef struct {
    VerticalPosition vertical;
    HorizontalPosition horizontal;
} PositionInScreen;

PositionInScreen position_in_screen(VerticalPosition, HorizontalPosition);

Button position_button(PositionInScreen position, Button button, SDL_Rect zone);

SDL_Rect window_rect(SDL_Window *window);

SDL_Rect safe_area_of(SDL_Rect rect, int top, int bottom);

#endif //DOOMDEPTHS_SCREEN_POSITION_H
