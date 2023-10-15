
//
// Created by Theo OMNES on 13/10/2023.
//

#include <SDL_image.h>
#include "in/sdl/sdl_controller.h"
#include "sdl_fight_page.h"
#include "port/out/log/log_error.h"
#include "port/out/persistence/intern_game_state/get_player.h"
#include "port/out/log/log_info.h"
#include "in/sdl/components/button/button_events/button_events.h"

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm);

SdlPlayer fill_fight_player();

void draw_action_buttons(SDL_Renderer *renderer, SDL_IHM ihm);

FightPage fill_fight_buttons(SDL_IHM ihm);

FightPage fill_fight_page(SDL_IHM ihm) {
    FightPage fight = ihm.page.fight;
    fight.player = fill_fight_player();
    fight.player.texture = IMG_LoadTexture(ihm.renderer, "resources/assets/player.png");
    if(fight.player.texture == NULL) {
        log_error("IMG_LoadTexture Error: %s.", IMG_GetError());
        return fight;
    }
    ihm.page.fight = fight;
    fight = fill_fight_buttons(ihm);

    log_info("fight page filled");
    return fight;
}

FightPage fill_fight_buttons(SDL_IHM ihm) {
    ButtonSize size = absolute_button_size(70, 70);
    FightPage fight = ihm.page.fight;
    fight.attack_button = create_img_button(
            ihm,
            "resources/assets/attack.png",
            (Point){.x = 0, .y = 0},
            size,
            no_callback_param(NULL));
    fight.attack_button = color_button(
            get_color(SDL_RED),
            get_color(SDL_MIDDLE_RED),
            fight.attack_button
            );

    Padding padding = box_sizing(padding_symetric(10), BORDER_BOX);
    fight.attack_button = padding_button(padding, fight.attack_button);

    log_info("after padding rect.w = %d, rect.h = %d", fight.attack_button.texture_rect.w, fight.attack_button.texture_rect.h);

    PositionInScreen positionInScreen = {.vertical = POSITION_END, .horizontal = POSITION_CENTER};
    fight.attack_button.position = positionInScreen;
    SDL_Rect zone = {.x = 0, .y = 0};
    SDL_GetWindowSize(ihm.window, &zone.w, &zone.h);
    fight.attack_button = position_button(positionInScreen, fight.attack_button, zone);

    log_info("after position rect.w = %d, rect.h = %d", fight.attack_button.texture_rect.w, fight.attack_button.texture_rect.h);

    ihm.page.fight = fight;
    return ihm.page.fight;
}

SdlPlayer fill_fight_player() {
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
    return player;
}

void draw_fight_page(SDL_Renderer *renderer, FightPage fight_page, SDL_IHM ihm) {
    draw_player(renderer, fight_page.player, ihm);
    draw_action_buttons(renderer, ihm);

    // draw enemy and its health bar
}

void draw_action_buttons(SDL_Renderer *renderer, SDL_IHM ihm) {
    draw_button(renderer, ihm.page.fight.attack_button);
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

SDL_IHM fight_page_handle_event(SDL_Event event, SDL_IHM ihm) {
    ButtonEvent attack_event = button_handle_event(ihm, event, ihm.page.fight.attack_button);
    ihm = attack_event.ihm;
    ihm.page.fight.attack_button = attack_event.button;
    return ihm;
}

SDL_IHM update_fight_page(SDL_IHM ihm) {
    ihm.page.fight.player.current_sprite += 1;
    if(ihm.page.fight.player.current_sprite > 1000 ) ihm.page.fight.player.current_sprite = 0;
    return ihm;
}