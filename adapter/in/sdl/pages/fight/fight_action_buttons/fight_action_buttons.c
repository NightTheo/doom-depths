
//
// Created by Theo OMNES on 19/10/2023.
//

#include "fight_action_buttons.h"
#include "in/sdl/sdl_controller.h"
#include "in/sdl/pages/fight/sdl_fight_page.h"
#include "port/in/query/is_current_fight_finished.h"
#include "in/sdl/components/button/button_events/button_events.h"
#include "port/out/log/log_info.h"
#include "port/in/command/attack_with_weapon.h"
#include "port/in/command/end_round.h"
#include "port/in/command/start_new_round.h"


ButtonEvent on_click_attack(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

ButtonEvent on_click_end_turn(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

ButtonEvent on_click_potion(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param);

Button update_attack_button(FightPage fight);

Button update_end_turn_button(FightPage fight);

Button update_potion_button(FightPage fight);


// NB: Change the order of the enum values to change the order of the buttons
typedef enum {
    POTION_BUTTON,
    END_TURN_BUTTON,
    ATTACK_BUTTON,


    number_of_buttons // keep this one as the last one
} ButtonsOrder;


FightPage fill_fight_buttons(SDL_IHM ihm) {
    ButtonSize size = absolute_button_size(70, 70);
    FightPage fight = ihm.page.fight;

    // TODO unify button creation (lot of duplication)
    fight.buttons = create_row_with_indexes(
            number_of_buttons,
            ATTACK_BUTTON, BUTTON, fill_attack_button(ihm, size),
            END_TURN_BUTTON, BUTTON, fill_end_turn_button(ihm, size),
            POTION_BUTTON, BUTTON, fill_potion_button(ihm, size)
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
            get_color(SDL_DARK_RED),
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
            get_color(SDL_DARK_RED),
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

Button fill_potion_button(SDL_IHM ihm, ButtonSize size) {
    Button potion_button = create_img_button(
            ihm,
            "resources/assets/potion.png",
            (Point){.x = 0, .y = 0},
            size,
            no_callback_param(&on_click_potion)
    );

    ButtonColor color = button_color(
            get_color(SDL_DARK_RED),
            get_color(SDL_DARK_RED),
            get_color(SDL_RED),
            get_color(SDL_GREY)
    );

    potion_button = color_button(color,potion_button);
    Padding padding = box_sizing(padding_symetric(10), BORDER_BOX);
    potion_button = padding_button(padding, potion_button);
    potion_button = border_radius_button(5, potion_button);

    return potion_button;
}

void draw_action_buttons(SDL_Renderer *renderer, SDL_IHM ihm) {
    // TODO draw row !
    Button attack_button = get_button_in_row_at_index(ihm.page.fight.buttons, ATTACK_BUTTON).cell.button;
    Button end_turn_button = get_button_in_row_at_index(ihm.page.fight.buttons, END_TURN_BUTTON).cell.button;
    Button potion_button = get_button_in_row_at_index(ihm.page.fight.buttons, POTION_BUTTON).cell.button;
    draw_button(renderer, attack_button);
    draw_button(renderer, end_turn_button);
    draw_button(renderer, potion_button);
}

Row update_fight_action_buttons(FightPage fight) {
    fight.buttons = row_with_row_button_at_index(fight.buttons, update_attack_button(fight), ATTACK_BUTTON);
    fight.buttons = row_with_row_button_at_index(fight.buttons, update_end_turn_button(fight), END_TURN_BUTTON);
    fight.buttons = row_with_row_button_at_index(fight.buttons, update_potion_button(fight), POTION_BUTTON);
    return fight.buttons;
}


Button update_attack_button(FightPage fight) {
    Button button = get_button_in_row_at_index(fight.buttons, ATTACK_BUTTON).cell.button;
    if(current_fight_is_finished() || fight.player.player.remaining_number_of_attacks == 0) {
        button = disable_button(button);
    } else button = enable_button(button);
    return button;
}

Button update_end_turn_button(FightPage fight) {
    Button button = get_button_in_row_at_index(fight.buttons, END_TURN_BUTTON).cell.button;;
    if(current_fight_is_finished()) button = disable_button(button);
    else button = enable_button(button);
    return button;
}

Button update_potion_button(FightPage fight) {
    Button button = get_button_in_row_at_index(fight.buttons, POTION_BUTTON).cell.button;
    // TODO if no more potions, disable button
    return button;
}

SDL_IHM fight_action_buttons_handle_event(SDL_Event event, SDL_IHM ihm) {
    Button attack_button = get_button_in_row_at_index(ihm.page.fight.buttons, ATTACK_BUTTON).cell.button;
    ButtonEvent attack_event = button_handle_event(ihm, event, attack_button);
    ihm = attack_event.ihm;
    ihm.page.fight.buttons = row_with_row_button_at_index(ihm.page.fight.buttons, attack_event.button, ATTACK_BUTTON);

    Button end_turn_button = get_button_in_row_at_index(ihm.page.fight.buttons, END_TURN_BUTTON).cell.button;
    ButtonEvent end_turn_event = button_handle_event(ihm, event, end_turn_button);
    ihm = end_turn_event.ihm;
    ihm.page.fight.buttons = row_with_row_button_at_index(ihm.page.fight.buttons, end_turn_event.button, END_TURN_BUTTON);

    Button potion_button = get_button_in_row_at_index(ihm.page.fight.buttons, POTION_BUTTON).cell.button;
    ButtonEvent potion_event = button_handle_event(ihm, event, potion_button);
    ihm = potion_event.ihm;
    ihm.page.fight.buttons = row_with_row_button_at_index(ihm.page.fight.buttons, potion_event.button, POTION_BUTTON);

    return ihm;
}

ButtonEvent on_click_attack(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("clicked on attack");
    attack_with_weapon();
    ihm.page.fight = update_sld_fight_page(ihm.page.fight);
    Button attack_button = get_button_in_row_at_index(ihm.page.fight.buttons, ATTACK_BUTTON).cell.button;
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
    Button end_turn_button = get_button_in_row_at_index(ihm.page.fight.buttons, END_TURN_BUTTON).cell.button;

    if (current_fight_is_finished()) {
        return finish_fight(ihm, end_turn_button);
    }

    return button_clicked(ihm, end_turn_button);
}

ButtonEvent on_click_potion(SDL_IHM ihm, __attribute__((unused)) ButtonCallbackParam param) {
    log_info("clicked on potion");

    ihm.page.fight = update_sld_fight_page(ihm.page.fight);
    Button potion = get_button_in_row_at_index(ihm.page.fight.buttons, POTION_BUTTON).cell.button;

    return button_clicked(ihm, potion);
}

