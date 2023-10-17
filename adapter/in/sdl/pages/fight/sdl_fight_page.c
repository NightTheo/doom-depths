
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
#include "port/in/query/is_current_fight_finished.h"
#include "port/in/query/is_player_alive.h"
#include "port/out/persistence/intern_game_state/get_map.h"
#include "port/in/command/finish_current_zone.h"

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm);

SdlPlayer fill_fight_player();

void draw_action_buttons(SDL_Renderer *renderer, SDL_IHM ihm);

FightPage fill_fight_buttons(SDL_IHM ihm);

FightPage update_sld_fight_page(FightPage fight);

SdlPlayer update_sld_fight_player(SdlPlayer player);

Button update_attack_button(FightPage fight);

Button update_end_turn_button(FightPage fight);

ButtonEvent on_click_attack(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

ButtonEvent on_click_end_turn(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

Button fill_attack_button(SDL_IHM ihm, ButtonSize size);

Button fill_end_turn_button(SDL_IHM ihm, ButtonSize size);

ButtonEvent finish_fight(SDL_IHM ihm, Button button);

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
    fight.buttons = row_with_row_button_at_index(fight.buttons, update_attack_button(fight), 0);
    fight.buttons = row_with_row_button_at_index(fight.buttons, update_end_turn_button(fight), 1);
    return fight;
}

Button update_attack_button(FightPage fight) {
    Button button = get_button_in_row_at_index(fight.buttons, 0).cell.button;
    if(current_fight_is_finished() || fight.player.player.remaining_number_of_attacks == 0) {
        button = disable_button(button);
    } else button = enable_button(button);
    return button;
}

Button update_end_turn_button(FightPage fight) {
    Button button = get_button_in_row_at_index(fight.buttons, 1).cell.button;;
    if(current_fight_is_finished()) button = disable_button(button);
    else button = enable_button(button);
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

    fight.buttons = create_row(
            2,
            BUTTON, fill_attack_button(ihm, size),
            BUTTON, fill_end_turn_button(ihm, size)
    );

    PositionInScreen buttons_position = (PositionInScreen){.vertical = POSITION_END, .horizontal = POSITION_CENTER};
    SDL_Rect safe_area = safe_area_of(window_rect(ihm.window), 40, 30);
    fight.buttons = spacing_row(10, fight.buttons);
    fight.buttons = position_row(buttons_position, fight.buttons, safe_area);
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
            get_color(SDL_DARK_RED),
            get_color(SDL_RED),
            get_color(SDL_GREY)
    );
    attack_button = color_button(
            color,
            attack_button
    );

    Padding padding = box_sizing(padding_symetric(10), BORDER_BOX);
    attack_button = padding_button(padding, attack_button);
    attack_button = border_radius_button(5, attack_button);

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
            get_color(SDL_DARK_RED),
            get_color(SDL_RED),
            get_color(SDL_GREY)
    );
    end_turn_button = color_button(
            color,
            end_turn_button
    );

    Padding padding = box_sizing(padding_symetric(10), BORDER_BOX);
    end_turn_button = padding_button(padding, end_turn_button);
    end_turn_button = border_radius_button(5, end_turn_button);

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
    Button attack_button = get_button_in_row_at_index(ihm.page.fight.buttons, 0).cell.button;
    Button end_turn_button = get_button_in_row_at_index(ihm.page.fight.buttons, 1).cell.button;
    draw_button(renderer, attack_button);
    draw_button(renderer, end_turn_button);
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
    Button attack_button = get_button_in_row_at_index(ihm.page.fight.buttons, 0).cell.button;
    ButtonEvent attack_event = button_handle_event(ihm, event, attack_button);
    ihm = attack_event.ihm;
    ihm.page.fight.buttons = row_with_row_button_at_index(ihm.page.fight.buttons, attack_event.button, 0);

    Button end_turn_button = get_button_in_row_at_index(ihm.page.fight.buttons, 1).cell.button;
    ButtonEvent end_turn_event = button_handle_event(ihm, event, end_turn_button);
    ihm = end_turn_event.ihm;
    ihm.page.fight.buttons = row_with_row_button_at_index(ihm.page.fight.buttons, end_turn_event.button, 1);

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
    Button attack_button = get_button_in_row_at_index(ihm.page.fight.buttons, 0).cell.button;
    if (current_fight_is_finished()) {
        return finish_fight(ihm, attack_button);
    }

    return button_clicked(ihm, attack_button);
}

ButtonEvent on_click_end_turn(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("clicked on end turn");
    end_round();
    start_new_round();
    ihm.page.fight = update_sld_fight_page(ihm.page.fight);
    Button end_turn_button = get_button_in_row_at_index(ihm.page.fight.buttons, 1).cell.button;

    if (current_fight_is_finished()) {
        return finish_fight(ihm, end_turn_button);
    }

    return button_clicked(ihm, end_turn_button);
}

ButtonEvent finish_fight(SDL_IHM ihm, Button button) {
    if(current_player_is_alive()) {
        finish_current_zone();
        ihm.current_page = MAP_PAGE;
        ihm.page.map = fill_map_page(ihm, get_map());
        return button_clicked(ihm, button);
    } else {
        // TODO: display game over
        ihm.current_page = TOWN_PAGE;
        return button_clicked(ihm, button);
    }
}
