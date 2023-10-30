
//
// Created by Theo OMNES on 21/10/2023.
//

#include <SDL_image.h>
#include "background.h"
#include "log/log_info.h"

BackgroundResult create_background(SDL_Renderer *renderer, const char *path) {
    Background background = {
            .rect = {.x = 0, .y = 0, .w = 0, .h = 0},
            .texture = IMG_LoadTexture(renderer, path),
    };
    if (background.texture == NULL) {
        printf("Unable to load background %s! SDL_image Error: %s\n", path, IMG_GetError());
        return (BackgroundResult) {.success = false};
    }
    SDL_QueryTexture(background.texture, NULL, NULL, &background.rect.w, &background.rect.h);

    return (BackgroundResult) {.success = true, .background = background};
}

void draw_background(SDL_Renderer *renderer, SDL_Rect zone, Background background) {
    SDL_Rect src_rect = {.x = 0, .y = 0, .w = zone.w, .h = zone.h};

    if(zone.h > background.rect.h) {
        uint8_t ratio = 100 * background.rect.h / zone.h;
        src_rect.w = src_rect.w * ratio / 100;
    }

    if(zone.w > background.rect.w) {
        uint8_t ratio = 100 * background.rect.w / zone.w;
        src_rect.h = src_rect.h * ratio / 100;
    }

    src_rect.x = background.rect.w / 2 - src_rect.w / 2;
    src_rect.y = background.rect.h / 2 - src_rect.h / 2;
    SDL_RenderCopy(renderer, background.texture, &src_rect, &zone);
}