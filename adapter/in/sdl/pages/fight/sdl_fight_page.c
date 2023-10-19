
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
#include "in/sdl/pages/fight/fight_action_buttons/fight_action_buttons.h"

FightPage fill_fight_buttons(SDL_IHM ihm);



FightPage fill_fight_page(SDL_IHM ihm) {
    FightPage fight = ihm.page.fight;
    fight.player = fill_fight_player(ihm.renderer);
    ihm.page.fight = fight;
    fight = fill_fight_buttons(ihm);

    log_info("fight page filled");
    start_new_round();
    return fight;
}

FightPage update_state_of_fight_page(FightPage fight) {
    fight.fight = get_current_fight();
    fight.player = update_sld_fight_player(fight.player);
    fight.buttons = update_style_of_fight_action_buttons(fight);
    return fight;
}

void draw_fight_page(SDL_Renderer *renderer, FightPage fight_page, SDL_IHM ihm) {
    draw_player(renderer, fight_page.player, ihm);
    draw_action_buttons(renderer, ihm);
    // draw enemy and its health bar
}

SDL_IHM fight_page_handle_event(SDL_Event event, SDL_IHM ihm) {
    return fight_action_buttons_handle_event(event, ihm);;
}

SDL_IHM update_fight_page(SDL_IHM ihm) {
    FightPage page = ihm.page.fight;

    page.player.animation = next_frame(page.player.animation);

    SDL_Rect safe_area = default_safe_area(window_rect(ihm.window));
    page.buttons = update_row_position_in_zone(page.buttons, safe_area);

    ihm.page.fight = page;
    return ihm;
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
