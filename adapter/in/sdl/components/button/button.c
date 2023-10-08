
//
// Created by Theo OMNES on 06/10/2023.
//

#include "SDL2/SDL_ttf.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/components/point/point.h"

#include "button.h"

Button create_button(SDL_IHM ihm, const char *text, Point p, SDL_Color background_color) {
    Button button;
    button.rect.x = p.x;
    button.rect.y = p.y;

    SDL_Surface* textSurface = TTF_RenderText_Solid(ihm.font, text, (SDL_Color){255, 255, 255, 255});
    button.text_texture = SDL_CreateTextureFromSurface(ihm.renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_QueryTexture(button.text_texture, NULL, NULL, &button.rect.w, &button.rect.h);
    button.bg_color = background_color;
    return button;
}

void drawButton(SDL_Renderer *renderer, Button button) {
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

Button padding_button(Button button, int horizontal, int vertical) {
    button.padding.horizontal = horizontal;
    button.padding.vertical = vertical;
    padding_rect(&button.rect, button.padding);
    return button;
}

