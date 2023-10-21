
//
// Created by Theo OMNES on 13/10/2023.
//

#include <SDL_image.h>
#include "in/sdl/sdl_controller.h"
#include "sdl_fight_page.h"
#include "port/out/log/log_info.h"
#include "in/sdl/components/button/button_events/button_events.h"
#include "port/out/persistence/intern_game_state/get_current_fight.h"
#include "port/in/command/start_new_round.h"
#include "port/in/query/is_player_alive.h"
#include "port/out/persistence/intern_game_state/get_map.h"
#include "port/in/command/finish_current_zone.h"
#include "in/sdl/pages/fight/fight_action_buttons/fight_action_buttons.h"
#include "port/in/query/is_current_fight_finished.h"

FightPage fill_fight_buttons(SDL_IHM ihm);


SDL_IHM ihm_after_fight_is_finished(SDL_IHM ihm);

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
    fight.buttons = update_state_of_fight_action_buttons(fight);
    return fight;
}

void draw_fight_page(SDL_Renderer *renderer, FightPage fight_page, SDL_IHM ihm) {
    draw_player(renderer, fight_page.player, ihm);
    draw_action_buttons(renderer, ihm);
    // draw enemy and its health bar
}

SDL_IHM fight_page_handle_event(SDL_Event event, SDL_IHM ihm) {
    ihm = fight_action_buttons_handle_event(event, ihm);
    ihm.page.fight = update_state_of_fight_page(ihm.page.fight);
    if(current_fight_is_finished()) {
        ihm = ihm_after_fight_is_finished(ihm);
    }
    return ihm;
}

SDL_IHM ihm_after_fight_is_finished(SDL_IHM ihm) {
    if(current_player_is_alive()) {
        finish_current_zone();
        ihm.current_page = MAP_PAGE;
        ihm.page.map = fill_map_page(ihm, get_map());
        return ihm;
    } else {
        // TODO: display game over
        ihm.current_page = TOWN_PAGE;
        return ihm;
    }
}

SDL_IHM update_fight_page(SDL_IHM ihm) {
    FightPage page = ihm.page.fight;
    Animation animation = page.player.animation;
    uint8_t number_of_frames_passed_since_last_second = ihm.number_of_frames_from_start % ihm.fps;
    uint8_t ratio = ihm.fps / animation.fps;
    if(number_of_frames_passed_since_last_second % ratio == 0) {
        animation = next_frame(page.player.animation);
        page.player.animation = animation;
    }

    SDL_Rect safe_area = default_safe_area(window_rect(ihm.window));
    page.buttons = update_row_position_in_zone(page.buttons, safe_area);

    ihm.page.fight = page;
    return ihm;
}
