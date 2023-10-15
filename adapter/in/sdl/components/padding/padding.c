
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL.h"
#include "padding.h"
#include "in/sdl/components/button/button.h"
#include "port/out/log/log_error.h"
#include "port/out/log/log_info.h"

Button padding_button_content_box(Padding padding, Button button);

Button padding_button_border_box(Padding padding, Button button);

Padding inverse_padding(Padding p) {
    return (Padding) {
            .horizontal = -p.horizontal,
            .vertical = -p.vertical,
            .box_sizing = p.box_sizing,
    };
}

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
    rect.w += 2 * p.horizontal;
    rect.h += 2 * p.vertical;
    return rect;
}

Button padding_button(Padding padding, Button button) {
    switch (padding.box_sizing) {
        case CONTENT_BOX: return padding_button_content_box(padding, button);
        case BORDER_BOX: return padding_button_border_box(padding, button);
        default: {
            log_error("Unknown box_sizing [%d]", padding.box_sizing);
            return button;
        }
    }
}

Button padding_button_content_box(Padding padding, Button button) {
    button.button_rect = padding_rect(button.button_rect, padding);
    return button;
}

Button padding_button_border_box(Padding padding, Button button) {
    button.texture_rect = padding_rect(button.texture_rect, inverse_padding(padding));
    return button;
}
