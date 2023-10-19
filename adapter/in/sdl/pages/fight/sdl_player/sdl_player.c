
//
// Created by Theo OMNES on 19/10/2023.
//

#include <SDL_image.h>
#include "sdl_player.h"
#include "port/out/persistence/intern_game_state/get_player.h"
#include "port/out/log/log_error.h"
#include "in/sdl/sdl_controller.h"


SdlPlayer update_sld_fight_player(SdlPlayer player) {
    player.player = get_player();
    player.health_bar.current_health = player.player.current_health;
    return player;
}

SdlPlayer fill_fight_player(SDL_Renderer *renderer) {
    int size = 32;
    SdlPlayer player = {
            .player = get_player(),
            .source_sprites_rect = {.w = 32, .h = 32, .x = 0, .y = 0},
            .destination_sprite_rect = {.w = size * 5, .h = size * 5, .x = 10, .y = 100},
            .current_sprite = 0,
            .health_bar = {
                    .health_color = get_color(SDL_GREEN),
                    .max_health = player.player.max_health,
                    .current_health = player.player.max_health,
            },
    };
    player.texture = IMG_LoadTexture(renderer, "resources/assets/player.png");
    if(player.texture == NULL) {
        log_error("IMG_LoadTexture Error: %s.", IMG_GetError());
        return player;
    }
    return player;
}

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm) {
    player.source_sprites_rect.x = 32 * ((player.current_sprite / 16) % 10);
    SDL_RenderCopy(renderer, player.texture, &player.source_sprites_rect, &player.destination_sprite_rect);
    player.health_bar.current_health = player.player.current_health;
    player.health_bar.rect = (SDL_Rect){
            .w = player.destination_sprite_rect.w,
            .h = 15,
            .x = player.destination_sprite_rect.x,
            .y = player.destination_sprite_rect.y - 20,
    };
    draw_health_bar(renderer, player.health_bar, ihm.font);
}