
//
// Created by Theo OMNES on 14/10/2023.
//

#include <SDL_ttf.h>
#include "health_bar.h"

void draw_health_text(SDL_Renderer *renderer, HealthBar health_bar, TTF_Font *font);

void draw_border(SDL_Renderer *renderer, HealthBar health_bar, SDL_Rect *rect);

void draw_current_health(SDL_Renderer *renderer, HealthBar health_bar, SDL_Rect rect);

SDL_Texture *getTextTexture(SDL_Renderer *renderer, HealthBar health_bar, TTF_Font *font);

SDL_Rect getTextRect(HealthBar health_bar, SDL_Texture *text_texture);

void draw_health_bar(SDL_Renderer *renderer, HealthBar health_bar, TTF_Font *font) {
    SDL_Rect rect = health_bar.rect;

    draw_border(renderer, health_bar, &rect);
    draw_current_health(renderer, health_bar, rect);
    draw_health_text(renderer, health_bar, font);
}

void draw_current_health(SDL_Renderer *renderer, HealthBar health_bar, SDL_Rect rect) {
    rect.w = (int) ((float) rect.w * ((float) health_bar.current_health / (float) health_bar.max_health));
    rect.h -= 2;
    rect.w -= 2;
    rect.x += 1;
    rect.y += 1;

    SDL_SetRenderDrawColor(
            renderer,
            health_bar.health_color.r,
            health_bar.health_color.g,
            health_bar.health_color.b,
            health_bar.health_color.a
            );
    SDL_RenderFillRect(renderer, &rect);
}

void draw_border(SDL_Renderer *renderer, HealthBar health_bar, SDL_Rect *rect) {
    SDL_SetRenderDrawColor(
            renderer,
            health_bar.health_color.r,
            health_bar.health_color.g,
            health_bar.health_color.b,
            health_bar.health_color.a
            );
    SDL_RenderDrawRect(renderer, rect);
}

void draw_health_text(SDL_Renderer *renderer, HealthBar health_bar, TTF_Font *font) {
    SDL_Texture *text_texture = getTextTexture(renderer, health_bar, font);

    SDL_Rect text_rect = getTextRect(health_bar, text_texture);

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_DestroyTexture(text_texture);
}

SDL_Rect getTextRect(HealthBar health_bar, SDL_Texture *text_texture) {
    int text_width, text_height;
    SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height);

    uint8_t ratio = health_bar.rect.h * 100 / text_height;

    text_width = text_width * ratio / 100;
    text_height = text_height *  ratio / 100;

    SDL_Rect text_rect = {
            health_bar.rect.x + ((health_bar.rect.w - text_width) / 2),
            health_bar.rect.y + ((health_bar.rect.h - text_height) / 2),
            text_width,
            text_height,
    };
    return text_rect;
}

SDL_Texture *getTextTexture(SDL_Renderer *renderer, HealthBar health_bar, TTF_Font *font) {
    char text[10];
    snprintf(text, 10, "%d/%d", health_bar.current_health, health_bar.max_health);
    SDL_Color color = get_color(SDL_WHITE);
    TTF_SetFontOutline(font, 1);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);
    return text_texture;
}


HealthBar create_health_bar(uint16_t max_health, SDL_Color health_color, SDL_Rect rect) {
    return (HealthBar) {
            .max_health = max_health,
            .current_health = max_health,
            .health_color = health_color,
            .rect = rect,
    };
}