
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
#include "port/in/command/attack_with_weapon.h"
#include "port/out/persistence/intern_game_state/get_current_fight.h"
#include "port/out/log/log_player.h"
#include "port/in/command/end_round.h"
#include "port/in/command/start_new_round.h"

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm);

SdlPlayer fill_fight_player();

void draw_action_buttons(SDL_Renderer *renderer, SDL_IHM ihm);

FightPage fill_fight_buttons(SDL_IHM ihm);

FightPage update_sld_fight_page(FightPage fight);

SdlPlayer update_sld_fight_player(SdlPlayer player);

Button update_attack_button(FightPage fight);

ButtonEvent on_click_attack(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

ButtonEvent on_click_end_turn(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

Button fill_attack_button(SDL_IHM ihm, ButtonSize size);

Button fill_end_turn_button(SDL_IHM ihm, ButtonSize size);

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
    start_new_round();
    return fight;
}

FightPage update_sld_fight_page(FightPage fight) {
    fight.fight = get_current_fight();
    log_player(fight.fight.player);
    fight.player = update_sld_fight_player(fight.player);
    fight.attack_button = update_attack_button(fight);
    return fight;
}

Button update_attack_button(FightPage fight) {
    Button button = fight.attack_button;
    if(fight.player.player.remaining_number_of_attacks == 0) {
        button = disable_button(button);
    } else {
        button = enable_button(button);
    }
    return button;
}

SdlPlayer update_sld_fight_player(SdlPlayer player) {
    player.player = get_player();
    player.health_bar.current_health = player.player.current_health;
    return player;
}

FightPage fill_fight_buttons(SDL_IHM ihm) {
    ButtonSize size = absolute_button_size(70, 70);
    FightPage fight = ihm.page.fight;
    fight.attack_button = fill_attack_button(ihm, size);
    fight.end_turn_button = fill_end_turn_button(ihm, size);

    ihm.page.fight = fight;
    return ihm.page.fight;
}

Button fill_attack_button(SDL_IHM ihm, ButtonSize size) {
    Button attack_button = create_img_button(
            ihm,
            "resources/assets/attack.png",
            (Point){.x = 0, .y = 0},
            size,
            no_callback_param(&on_click_attack)
    );

    ButtonColor color = button_color(
            get_color(SDL_RED),
            get_color(SDL_RED),
            get_color(SDL_MIDDLE_RED),
            get_color(SDL_GREY)
    );
    attack_button = color_button(
            color,
            attack_button
    );

    Padding padding = box_sizing(padding_symetric(10), BORDER_BOX);
    attack_button = padding_button(padding, attack_button);

    PositionInScreen positionInScreen = {.vertical = POSITION_END, .horizontal = POSITION_CENTER};
    attack_button.position = positionInScreen;
    SDL_Rect window_zone = {.x = 0, .y = 0};
    SDL_GetWindowSize(ihm.window, &window_zone.w, &window_zone.h);

    int safe_area_top = 40;
    int safe_area_bottom = 30;
    SDL_Rect safe_area = {.x = 0, .y = safe_area_top, .w = window_zone.w, .h = window_zone.h - (safe_area_top + safe_area_bottom)};
    attack_button = position_button(positionInScreen, attack_button, safe_area);

    return attack_button;
}

Button fill_end_turn_button(SDL_IHM ihm, ButtonSize size) {
    Button end_turn_button = create_img_button(
            ihm,
            "resources/assets/end_turn.png",
            (Point){.x = 0, .y = 0},
            size,
            no_callback_param(&on_click_end_turn)
    );

    ButtonColor color = button_color(
            get_color(SDL_RED),
            get_color(SDL_RED),
            get_color(SDL_MIDDLE_RED),
            get_color(SDL_GREY)
    );
    end_turn_button = color_button(
            color,
            end_turn_button
    );

    Padding padding = box_sizing(padding_symetric(10), BORDER_BOX);
    end_turn_button = padding_button(padding, end_turn_button);

    PositionInScreen positionInScreen = {.vertical = POSITION_END, .horizontal = POSITION_END};
    end_turn_button.position = positionInScreen;
    SDL_Rect window_zone = {.x = 0, .y = 0};
    SDL_GetWindowSize(ihm.window, &window_zone.w, &window_zone.h);

    int safe_area_top = 40;
    int safe_area_bottom = 30;
    SDL_Rect safe_area = {.x = 0, .y = safe_area_top, .w = window_zone.w, .h = window_zone.h - (safe_area_top + safe_area_bottom)};
    end_turn_button = position_button(positionInScreen, end_turn_button, safe_area);

    return end_turn_button;
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
    draw_button(renderer, ihm.page.fight.end_turn_button);
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

    ButtonEvent end_turn_event = button_handle_event(ihm, event, ihm.page.fight.end_turn_button);
    ihm = end_turn_event.ihm;
    ihm.page.fight.end_turn_button = end_turn_event.button;

    return ihm;
}

SDL_IHM update_fight_page(SDL_IHM ihm) {
    ihm.page.fight.player.current_sprite += 1;
    if(ihm.page.fight.player.current_sprite > 1000 ) ihm.page.fight.player.current_sprite = 0;
    return ihm;
}

ButtonEvent on_click_attack(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("clicked on attack");
    attack_with_weapon();
    ihm.page.fight = update_sld_fight_page(ihm.page.fight);
    return button_clicked(ihm, ihm.page.fight.attack_button);
}

ButtonEvent on_click_end_turn(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("clicked on end turn");
    end_round();
    start_new_round();
    ihm.page.fight = update_sld_fight_page(ihm.page.fight);
    return button_clicked(ihm, ihm.page.fight.end_turn_button);
}