
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL.h"
#include "padding.h"
#include "in/sdl/components/button/button.h"


SDL_Rect padding_rect_content_box(SDL_Rect rect, Padding padding);

SDL_Rect padding_rect_border_box(SDL_Rect rect, Padding padding);

Padding padding_asymetric(int horizontal, int vertical) {
    return (Padding) {
        .horizontal = horizontal,
        .vertical = vertical,
        .box_sizing = CONTENT_BOX,
    };
}

Padding padding_symetric(int padding) {
    return (Padding) {
            .horizontal = padding,
            .vertical = padding,
            .box_sizing = CONTENT_BOX,
    };
}

Padding box_sizing(Padding padding, BoxSizing box_sizing) {
    padding.box_sizing = box_sizing;
    return padding;
}

SDL_Rect padding_rect(SDL_Rect rect, Padding p) {
    switch (p.box_sizing) {
        case CONTENT_BOX: return padding_rect_content_box(rect, p);
        case BORDER_BOX: return rect;
    }
}

SDL_Rect padding_rect_content_box(SDL_Rect rect, Padding padding) {
    rect.w += 2 * padding.horizontal;
    rect.h += 2 * padding.vertical;
    return rect;
}

Button padding_button(Padding padding, Button button) {
    button.button_rect = padding_rect(button.button_rect, padding);
    return button;
}
