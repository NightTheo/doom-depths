
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL_ttf.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/point/point.h"

#include "in/sdl/components/color/sdl_color.h"
#include "button.h"
#include "port/out/log/log_info.h"
#include "button_clicked_event.h"

ButtonClicked button_handle_click(SDL_IHM ihm, SDL_Event event, Button button);

Button button_handle_hover(SDL_Event event, Button button);

Button current_background_color_button(SDL_Color color, Button button);

/**
 * By default padding to 0, background color to white
 */
Button create_button(SDL_IHM ihm, const char *text, Point p, button_callback callback) {
    Button button;
    button.is_visible = true;
    button.rect.x = p.x;
    button.rect.y = p.y;

    SDL_Surface *textSurface = TTF_RenderText_Solid(ihm.font, text, get_color(SDL_WHITE));
    button.text_texture = SDL_CreateTextureFromSurface(ihm.renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int window_width;
    SDL_GetWindowSize(ihm.window, &window_width, NULL);

    SDL_QueryTexture(button.text_texture, NULL, NULL, NULL, &button.rect.h);
    button.rect.h += 20;
    button.rect.w = (window_width * 70) / 100;
    button.rect.x = (window_width - button.rect.w) / 2;

    button.padding = (Padding) {0, 0};
    button.bg_color = get_color(SDL_WHITE);
    button.current_bg_color = get_color(SDL_WHITE);
    button.bg_hover_color = get_color(SDL_WHITE);

    button.callback = callback;

    return button;
}

void drawButton(SDL_Renderer *renderer, Button button) {
    if (!button.is_visible) return;
    SDL_Color color = button.current_bg_color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &button.rect);

    int text_width, text_height;
    SDL_QueryTexture(button.text_texture, NULL, NULL, &text_width, &text_height);
    SDL_Rect textRect = {
            button.rect.x + ((button.rect.w - text_width) / 2),
            button.rect.y + ((button.rect.h - text_height) / 2),
            text_width,
            text_height
    };
    SDL_RenderCopy(renderer, button.text_texture, NULL, &textRect);
}

Button padding_button(Padding padding, Button button) {
    button.padding = padding;
    padding_rect(&button.rect, button.padding);
    return button;
}

Button color_button(SDL_Color background_color, SDL_Color hover_color, Button button) {
    button.current_bg_color = background_color;
    button.bg_color = background_color;
    button.bg_hover_color = hover_color;
    return button;
}

Button background_color_button(SDL_Color color, Button button) {
    button.bg_color = color;
    return button;
}

Button background_hover_color_button(SDL_Color color, Button button) {
    button.bg_hover_color = color;
    return button;
}

ButtonClicked button_handle_event(SDL_IHM ihm, SDL_Event event, Button button) {
    switch (event.type) {
        case SDL_MOUSEBUTTONUP: return button_handle_click(ihm, event, button);
        case SDL_MOUSEMOTION: return (ButtonClicked) {ihm, button_handle_hover(event, button)};
        default: return (ButtonClicked) {ihm, button};
    }
}

Button button_handle_hover(SDL_Event event, Button button) {
    if (event.type != SDL_MOUSEMOTION) return button;
    Point mouse_at = {event.button.x, event.button.y};
    if (button_at_point(button, mouse_at)) {
        return current_background_color_button(button.bg_hover_color, button);
    } else {
        return current_background_color_button(button.bg_color, button);
    }
}

Button current_background_color_button(SDL_Color color, Button button) {
    button.current_bg_color = color;
    return button;
}

ButtonClicked button_handle_click(SDL_IHM ihm, SDL_Event event, Button button) {
    if (event.type != SDL_MOUSEBUTTONUP) return button_clicked(ihm, button);
    Point clicked_at = {event.button.x, event.button.y};
    if (!button_at_point(button, clicked_at)) return button_clicked(ihm, button);

    return button_clicked(button.callback(ihm), button);
}

bool button_at_point(Button button, Point point) {
    if (!button.is_visible) return false;

    return point.x >= button.rect.x && point.x <= button.rect.x + button.rect.w
           && point.y >= button.rect.y && point.y <= button.rect.y + button.rect.h;
}

ButtonClicked button_clicked(SDL_IHM ihm, Button button) {
    ButtonClicked clicked;
    clicked.ihm = ihm;
    clicked.button = button;
    return clicked;
}