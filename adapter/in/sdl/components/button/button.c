
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
#include "in/sdl/components/button/button_events/button_events.h"

ButtonEvent button_handle_click(SDL_IHM ihm, SDL_Event event, Button button);

ButtonEvent button_handle_hover(SDL_IHM ihm, SDL_Event event, Button button);

Button current_background_color_button(SDL_Color color, Button button);

void draw_rounded_rect(SDL_Renderer *renderer, SDL_Rect rect, uint8_t radius);

void draw_circle(SDL_Renderer *renderer, int x0, int y0, int radius);

void draw_filled_circle(SDL_Renderer *renderer, int x, int y, int radius);

void sdl_ellipse(SDL_Renderer *r, int x0, int y0, int radiusX, int radiusY, bool fill);

Button create_button(SDL_IHM ihm, Point p, ButtonSize size, ButtonCallback callback) {
    Button button;
    button.is_visible = true;
    button.is_enabled = true;
    button.button_rect = (SDL_Rect) {.x = p.x, .y = p.y};
    button.border_radius = 0;

    button.texture = NULL;
    button.texture_rect = button.button_rect;

    button.color = button_color(
            get_color(SDL_WHITE),
            get_color(SDL_WHITE),
            get_color(SDL_WHITE),
            get_color(SDL_WHITE)
            );
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
    button.button_rect.w = size.width;
    button.button_rect.h = size.height;
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
    if(button.border_radius == 0) SDL_RenderFillRect(renderer, &button.button_rect);
    else draw_rounded_rect(renderer, button.button_rect, button.border_radius);

    SDL_RenderCopy(renderer, button.texture, NULL, &button.texture_rect);
}

void draw_rounded_rect(SDL_Renderer *renderer, SDL_Rect rect, uint8_t radius) {
    int w = rect.w;
    int h = rect.h;
    int r = radius;

    if (r > w / 2) r = w / 2;
    if (r > h / 2) r = h / 2;

    SDL_RenderDrawLine(renderer, rect.x + r, rect.y, rect.x + w - r, rect.y);
    SDL_RenderDrawLine(renderer, rect.x + r, rect.y + h - 1, rect.x + w - r, rect.y + h - 1);
    SDL_RenderDrawLine(renderer, rect.x, rect.y + r, rect.x, rect.y + h - r);
    SDL_RenderDrawLine(renderer, rect.x + w - 1, rect.y + r, rect.x + w - 1, rect.y + h - r);

    draw_filled_circle(renderer, rect.x + r, rect.y + r, r);
    draw_filled_circle(renderer, rect.x + r, rect.y + h - r - 1, r);
    draw_filled_circle(renderer, rect.x + w - r - 1, rect.y + r, r);
    draw_filled_circle(renderer, rect.x + w - r - 1, rect.y + h - r - 1, r);

    SDL_Rect fill_rect = {rect.x + r, rect.y, w - 2 * r, h};
    SDL_RenderFillRect(renderer, &fill_rect);
    fill_rect = (SDL_Rect) {rect.x, rect.y + r, w, h - 2 * r};
    SDL_RenderFillRect(renderer, &fill_rect);
}

// https://stackoverflow.com/a/65745687
void draw_filled_circle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

Button color_button(ButtonColor color, Button button) {
    button.color = color;
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
    if(!button.is_visible || !button.is_enabled) return event_not_handled(ihm, button);

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
    if(!button.is_visible || !button.is_enabled) return event_not_handled(ihm, button);
    Point clicked_at = {event.button.x, event.button.y};
    if (!button_at_point(button, clicked_at)) return event_not_handled(ihm, button);

    ButtonCallback callback = button.callback;
    if(callback.invoke == NULL) {
        log_info("No callback for button, nothing to do");
        return event_not_handled(ihm, button);
    }
    return callback.invoke(ihm, callback.param);
}

bool button_at_point(Button button, Point point) {
    if (!button.is_visible) return false;

    return point.x >= button.button_rect.x && point.x <= button.button_rect.x + button.button_rect.w
           && point.y >= button.button_rect.y && point.y <= button.button_rect.y + button.button_rect.h;
}

ButtonColor button_color(SDL_Color current, SDL_Color background, SDL_Color hover, SDL_Color disabled) {
    ButtonColor color = {
            .current = current,
            .background = background,
            .hover = hover,
            .disabled = disabled,
    };
    return color;
}

Button disable_button(Button button) {
    button.is_enabled = false;
    button.color.current = button.color.disabled;
    return button;
}

Button enable_button(Button button) {
    button.is_enabled = true;
    button.color.current = button.color.background;
    return button;
}

Button border_radius_button(uint8_t radius, Button button) {
    button.border_radius = radius;
    return button;
}