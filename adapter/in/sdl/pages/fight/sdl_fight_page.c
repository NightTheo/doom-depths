
//
// Created by Theo OMNES on 13/10/2023.
//

#include <SDL_image.h>
#include "in/sdl/sdl_controller.h"
#include "sdl_fight_page.h"
#include "port/out/log/log_error.h"
#include "port/out/persistence/intern_game_state/get_player.h"

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm);

FightPage fill_fight_page(SDL_IHM ihm) {
    FightPage fight = ihm.page.fight;
    fight.player.texture = IMG_LoadTexture(ihm.renderer, "resources/assets/player_simple.png");
    if(fight.player.texture == NULL) {
        log_error("IMG_LoadTexture Error: %s.", IMG_GetError());
        return fight;
    }

    int size;
    SDL_QueryTexture(fight.player.texture, NULL, NULL, &size, NULL);

    fight.player.rect = (SDL_Rect){
            .w = size * 5,
            .h = size * 5,
            .x = 10,
            .y = 100,
    };
    fight.player.player = get_player();
    fight.player.health_bar = (HealthBar){
            .health_color = get_color(SDL_GREEN),
            .max_health = fight.player.player.max_health,
            .current_health = fight.player.player.max_health,
    };
    return fight;
}

void draw_fight_page(SDL_Renderer *renderer, FightPage fight_page, SDL_IHM ihm) {
    draw_player(renderer, fight_page.player, ihm);
}

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm) {
    SDL_RenderCopy(renderer, player.texture, NULL , &player.rect);
    player.health_bar.current_health = player.player.current_health;
    player.health_bar.rect = (SDL_Rect){
            .w = 150,
            .h = 15,
            .x = player.rect.x,
            .y = player.rect.y - 20,
    };
    draw_health_bar(renderer, player.health_bar, ihm.font);
}

SDL_IHM fight_page_handle_event(SDL_Event event, SDL_IHM ihm) {
    // TODO
    return ihm;
}