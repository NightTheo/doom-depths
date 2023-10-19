
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
#include "in/sdl/components/screen_position/screen_position.h"

typedef enum {
    BUTTON_NORMAL,
    BUTTON_SELECTED,
    BUTTON_DISABLED,
    BUTTON_HIDEN,
} ButtonState;

typedef struct ButtonEvent ButtonEvent;
typedef struct {
    SDL_Color current;
    SDL_Color background;
    SDL_Color hover;
    SDL_Color disabled;
} ButtonColor;

typedef struct Button Button;
struct Button{
    ButtonState state;
    SDL_Rect button_rect;
    SDL_Rect texture_rect;
    SDL_Texture* texture;
    ButtonColor color;
    ButtonCallback callback;
    ButtonSize size;
    PositionInScreen position;
    uint8_t border_radius;
};

ButtonColor button_color(SDL_Color background, SDL_Color hover, SDL_Color disabled);

void draw_button(SDL_Renderer *renderer, Button button);

Button create_button(SDL_IHM ihm, Point p, ButtonSize size, ButtonCallback callback);

Button create_text_button(SDL_IHM ihm, const char *text, Point p, ButtonSize size, ButtonCallback callback);

Button create_img_button(SDL_IHM ihm, const char *img_path, Point p, ButtonSize size, ButtonCallback callback);

Button color_button(ButtonColor color, Button button);

ButtonEvent button_handle_event(SDL_IHM ihm, SDL_Event event, Button button);

bool button_at_point(Button button, Point point);

Button disable_button(Button button);

Button enable_button(Button button);

Button border_radius_button(uint8_t radius, Button button);

#endif //DOOMDEPTHS_BUTTON_H
