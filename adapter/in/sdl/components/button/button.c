
//
// Created by Theo OMNES on 06/10/2023.
//

#include <SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/point/point.h"

#include "in/sdl/components/color/sdl_color.h"
#include "button.h"
#include "in/sdl/components/button/button_events/button_events.h"
#include "port/out/log/log_error.h"
#include "port/out/log/log_info.h"

ButtonEvent button_handle_click(SDL_IHM ihm, SDL_Event event, Button button);

ButtonEvent button_handle_hover(SDL_IHM ihm, SDL_Event event, Button button);

Button current_background_color_button(SDL_Color color, Button button);


Button create_button(SDL_IHM ihm, Point p, ButtonSize size, ButtonCallback callback) {
    Button button;
    button.is_visible = true;
    button.button_rect = (SDL_Rect) {.x = p.x, .y = p.y};

    button.texture = NULL;
    button.texture_rect = button.button_rect;

    button.color = button_color(get_color(SDL_WHITE), get_color(SDL_WHITE), get_color(SDL_WHITE));
    button.callback = callback;

    button.size = size;
    return button;
}

Button create_text_button(SDL_IHM ihm, const char *text, Point p, ButtonSize size, ButtonCallback callback) {
    Button button = create_button(ihm, p, size, callback);

    SDL_Surface *textSurface = TTF_RenderText_Solid(ihm.font, text, get_color(SDL_WHITE));
    if (textSurface == NULL) {
        log_error("TTF_RenderText_Solid Error: %s.", TTF_GetError());
        return button;
    }
    button.texture = SDL_CreateTextureFromSurface(ihm.renderer, textSurface);
    if (button.texture == NULL) {
        log_error("SDL_CreateTextureFromSurface Error: %s.", SDL_GetError());
        return button;
    }
    SDL_FreeSurface(textSurface);

    return size_button(ihm.window, button);
}


Button create_img_button(SDL_IHM ihm, const char *img_path, Point p, ButtonSize size, ButtonCallback callback) {
    Button button = create_button(ihm, p, size, callback);

    log_info("Loading image %s", img_path);
    button.texture = IMG_LoadTexture(ihm.renderer, img_path);
    if(button.texture == NULL) {
        log_error("IMG_LoadTexture Error: %s.", IMG_GetError());
        return button;
    }
    log_info("Image loaded", img_path);
    return size_button(ihm.window, button);
}

void draw_button(SDL_Renderer *renderer, Button button) {
    if (!button.is_visible) return;
    SDL_Color color = button.color.current;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &button.button_rect);

    SDL_Rect *source_texture_rect = NULL;
    SDL_RenderCopy(renderer, button.texture, source_texture_rect, &button.texture_rect);
}

Button color_button(SDL_Color background_color, SDL_Color hover_color, Button button) {
    button.color.current = background_color;
    button.color.background = background_color;
    button.color.hover = hover_color;
    return button;
}

ButtonEvent button_handle_event(SDL_IHM ihm, SDL_Event event, Button button) {
    switch (event.type) {
        case SDL_MOUSEBUTTONUP: return button_handle_click(ihm, event, button);
        case SDL_MOUSEMOTION: return button_handle_hover(ihm, event, button);
        default: return event_not_handled(ihm, button);
    }
}

ButtonEvent button_handle_hover(SDL_IHM ihm, SDL_Event event, Button button) {
    if (event.type != SDL_MOUSEMOTION) return event_not_handled(ihm, button);
    Point mouse_at = {event.button.x, event.button.y};
    if (button_at_point(button, mouse_at)) {
        return button_hovered(ihm, current_background_color_button(button.color.hover, button));
    } else {
        return button_unhovered(ihm, current_background_color_button(button.color.background, button));
    }
}

Button current_background_color_button(SDL_Color color, Button button) {
    button.color.current = color;
    return button;
}

ButtonEvent button_handle_click(SDL_IHM ihm, SDL_Event event, Button button) {
    if (event.type != SDL_MOUSEBUTTONUP) return event_not_handled(ihm, button);
    Point clicked_at = {event.button.x, event.button.y};
    if (!button_at_point(button, clicked_at)) return event_not_handled(ihm, button);

    ButtonCallback callback = button.callback;
    if(callback.invoke == NULL) log_info("No callback for button, nothing to do");
    SDL_IHM ihm_after_callback = callback.invoke == NULL
            ? ihm
            : callback.invoke(ihm, callback.param);

    return button_clicked(ihm_after_callback, button);
}

bool button_at_point(Button button, Point point) {
    if (!button.is_visible) return false;

    return point.x >= button.button_rect.x && point.x <= button.button_rect.x + button.button_rect.w
           && point.y >= button.button_rect.y && point.y <= button.button_rect.y + button.button_rect.h;
}

ButtonColor button_color(SDL_Color current, SDL_Color background, SDL_Color hover) {
    ButtonColor color = {
            current,
            background,
            hover,
    };
    return color;
}