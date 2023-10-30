
//
// Created by Theo OMNES on 19/10/2023.
//

#include <SDL_image.h>
#include "sdl_player.h"
#include "application/port/out/persistence/intern_game_state/get_player.h"
#include "application/port/out/log/log_error.h"
#include "in/sdl/sdl_controller.h"

SpriteSheet player_sprite_sheet(SDL_Renderer *renderer);


SdlPlayer update_sld_fight_player(SdlPlayer player) {
    player.player = get_player();
    player.health_bar.current_health = player.player.current_health;
    return player;
}

SdlPlayer fill_fight_player(SDL_Renderer *renderer) {
    int sprite_size = 32;
    int sprite_size_in_screen = sprite_size * 5;
    Animation animation = {
            .sprite_rect = (SDL_Rect) {.w = sprite_size, .h = sprite_size, .x = 0, .y = 0},
            .screen_rect = (SDL_Rect) {.w = sprite_size_in_screen, .h = sprite_size_in_screen, .x = 10, .y = 100},
            .current_frame = 0,
            .number_of_frames = 10,
            .start_frame = 0,
            .sprite_sheet = player_sprite_sheet(renderer),
            .fps = 5,
    };
    SdlPlayer player = {
            .player = get_player(),
            .animation = animation,
            .health_bar = {
                    .health_color = get_color(SDL_GREEN),
                    .max_health = player.player.max_health,
                    .current_health = player.player.max_health,
            },
    };
    return player;
}

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm) {
    Animation animation = player.animation;
    SDL_RenderCopy(
            renderer,
            animation.sprite_sheet.texture,
            &animation.sprite_rect,
            &animation.screen_rect
            );
    player.health_bar.current_health = player.player.current_health;
    player.health_bar.rect = (SDL_Rect){
            .w = player.animation.screen_rect.w,
            .h = 15,
            .x = player.animation.screen_rect.x,
            .y = player.animation.screen_rect.y - 20,
    };
    draw_health_bar(renderer, player.health_bar, ihm.font);
}

SpriteSheet player_sprite_sheet(SDL_Renderer *renderer) {
    SpriteSheet sprite_sheet = {
            .texture = IMG_LoadTexture(renderer, "resources/assets/player.png"),
            .rows = 1,
            .columns = 10,
    };
    if(sprite_sheet.texture == NULL) {
        log_error("IMG_LoadTexture Error: %s.", IMG_GetError());
        return sprite_sheet;
    }
    return sprite_sheet;
}