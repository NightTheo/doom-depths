
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL_ttf.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/point/point.h"

#include "in/sdl/components/color/sdl_color.h"
#include "button.h"
#include "button_clicked_event.h"
#include "port/out/log/log_error.h"

ButtonClicked button_handle_click(SDL_IHM ihm, SDL_Event event, Button button);

Button button_handle_hover(SDL_Event event, Button button);

Button current_background_color_button(SDL_Color color, Button button);

Button size_button(SDL_Window *window, Button button);

Button size_button_absolute(Button button);

Button size_button_window_relative(SDL_Window *window, Button button);

Button size_button_text_fit(Button button);

/**
 * By default padding to 0, background health_color to white
 */
Button create_button(SDL_IHM ihm, const char *text, Point p, ButtonSize size, ButtonCallback callback) {
    Button button;
    button.is_visible = true;
    button.rect.x = p.x;
    button.rect.y = p.y;

    SDL_Surface *textSurface = TTF_RenderText_Solid(ihm.font, text, get_color(SDL_WHITE));
    button.text_texture = SDL_CreateTextureFromSurface(ihm.renderer, textSurface);
    SDL_FreeSurface(textSurface);

    button = padding_button(size.padding, button);
    button.color = button_color(get_color(SDL_WHITE), get_color(SDL_WHITE), get_color(SDL_WHITE));
    button.callback = callback;

    button.size = size;
    button = size_button(ihm.window, button);

    return button;
}

Button size_button(SDL_Window *window, Button button) {
    switch (button.size.size_type) {
        case ABSOLUTE: return size_button_absolute(button);
        case WINDOW_RELATIVE: return size_button_window_relative(window, button);
        case TEXT_FIT: return size_button_text_fit(button);
        default: {
            log_error("Unknown size_type [%d]", button.size.size_type);
            return button;
        }
    }
}

Button size_button_text_fit(Button button) {
    SDL_QueryTexture(button.text_texture, NULL, NULL, &button.rect.w, &button.rect.h);
    return button;
}

Button size_button_window_relative(SDL_Window *window, Button button) {
    int window_width;
    SDL_GetWindowSize(window, &window_width, NULL);
    SDL_QueryTexture(button.text_texture, NULL, NULL, NULL, &button.rect.h);
    button.rect.h += 20;
    button.rect.w = (window_width * button.size.window_percentage) / 100;
    button.rect.x = (window_width - button.rect.w) / 2;
    return button;
}

Button size_button_absolute(Button button) {
    button.rect.h = button.size.height;
    button.rect.w = button.size.width;
    return button;
}

void draw_button(SDL_Renderer *renderer, Button button) {
    if (!button.is_visible) return;
    SDL_Color color = button.color.current;
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
    button.size.padding = padding;
    padding_rect(&button.rect, button.size.padding);
    return button;
}

Button color_button(SDL_Color background_color, SDL_Color hover_color, Button button) {
    button.color.current = background_color;
    button.color.background = background_color;
    button.color.hover = hover_color;
    return button;
}

Button background_color_button(SDL_Color color, Button button) {
    button.color.background = color;
    return button;
}

Button background_hover_color_button(SDL_Color color, Button button) {
    button.color.hover = color;
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
        return current_background_color_button(button.color.hover, button);
    } else {
        return current_background_color_button(button.color.background, button);
    }
}

Button current_background_color_button(SDL_Color color, Button button) {
    button.color.current = color;
    return button;
}

ButtonClicked button_handle_click(SDL_IHM ihm, SDL_Event event, Button button) {
    if (event.type != SDL_MOUSEBUTTONUP) return button_clicked(ihm, button);
    Point clicked_at = {event.button.x, event.button.y};
    if (!button_at_point(button, clicked_at)) return button_clicked(ihm, button);

    ButtonCallback callback = button.callback;
    SDL_IHM ihm_after_callback = callback.invoke == NULL
            ? ihm
            : callback.invoke(ihm, callback.param);

    return button_clicked(ihm_after_callback, button);
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

ButtonColor button_color(SDL_Color current, SDL_Color background, SDL_Color hover) {
    ButtonColor color = {
            current,
            background,
            hover,
    };
    return color;
}