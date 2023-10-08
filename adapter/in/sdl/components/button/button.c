
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL_ttf.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/point/point.h"

#include "in/sdl/components/color/sdl_color.h"
#include "button.h"
#include "port/out/log/log_info.h"

/**
 *
 * By default padding to 0, background color to white
 */
Button create_button(SDL_IHM ihm, const char *text, Point p, void (*callback)()) {
    Button button;
    button.is_visible = true;
    button.rect.x = p.x;
    button.rect.y = p.y;

    SDL_Surface *textSurface = TTF_RenderText_Solid(ihm.font, text, (SDL_Color) {255, 255, 255, 255});
    button.text_texture = SDL_CreateTextureFromSurface(ihm.renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_QueryTexture(button.text_texture, NULL, NULL, &button.rect.w, &button.rect.h);

    button.padding = (Padding) {0, 0};
    button.bg_color = get_color(SDL_WHITE);

    button.callback = callback;

    return button;
}

void drawButton(SDL_Renderer *renderer, Button button) {
    if (!button.is_visible) return;
    SDL_SetRenderDrawColor(renderer, button.bg_color.r, button.bg_color.g, button.bg_color.b, button.bg_color.a);
    SDL_RenderFillRect(renderer, &button.rect);

    Padding p = button.padding;
    SDL_Rect textRect = {
            button.rect.x + p.horizontal,
            button.rect.y + p.vertical,
            button.rect.w - (2 * p.horizontal),
            button.rect.h - (2 * p.vertical)
    };
    SDL_RenderCopy(renderer, button.text_texture, NULL, &textRect);
}

Button padding_button(Padding padding, Button button) {
    button.padding = padding;
    padding_rect(&button.rect, button.padding);
    return button;
}

Button background_color_button(SDL_Color color, Button button) {
    button.bg_color = color;
    return button;
}

void button_handle_event(SDL_Event event, Button button) {
    if (event.type != SDL_MOUSEBUTTONUP) return;
    Point clicked_at = {event.button.x, event.button.y};
    if (!button_is_clicked_at_point(button, clicked_at)) return;

    button.callback();
}

bool button_is_clicked_at_point(Button button, Point clicked_at) {
    if (!button.is_visible) return false;

    return clicked_at.x >= button.rect.x && clicked_at.x <= button.rect.x + button.rect.w
           && clicked_at.y >= button.rect.y && clicked_at.y <= button.rect.y + button.rect.h;
}
