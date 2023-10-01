
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include "../../../application/port/in/start_ihm.h"

#include "../../../application/port/out/ihm/display_leave_town_actions.h"
#include "../../../application/port/out/ihm/display_game_over.h"
#include "../../../application/port/out/ihm/display_map.h"
#include "../../../application/port/out/persistence/intern_game_state/game_state.h"
#include "../../../application/port/in/leave_town_action.h"
#include "../../../application/port/out/log/log_error.h"
#include "../../../application/port/in/end_round.h"
#include "../../../application/port/in/leave_town.h"
#include "../../../application/port/out/persistence/intern_game_state/get_intern_game_state.h"
#include "../../../application/port/in/player_enter_zone.h"
#include "../../../application/port/in/query/is_current_fight_finished.h"
#include "../../../application/port/in/query/is_player_alive.h"
#include "../../../application/port/in/finish_current_zone.h"

LeaveTownAction get_game_state_by_leave_town_action();
void fight(DoomDepths game);

void start_ihm() {
    display_leave_town_actions();
    LeaveTownAction leave_town_action = get_game_state_by_leave_town_action();
    leave_town(leave_town_action);

    while (true) {
        DoomDepths game = player_enter_zone(enter_map(get_intern_game_state().map));

        fight(game);

        bool player_won = current_player_is_alive();
        if (player_won) {
            finish_current_zone();
            player_enter_zone(enter_map(game.map));
        } else {
            display_game_over();
            free_doom_depths(get_intern_game_state());
            break;
        }
    }
}

LeaveTownAction get_game_state_by_leave_town_action() {
    int8_t input = -1;
    do {
        fflush(stdin);
        scanf("%hhd", &input);
    } while (input <= 0 || input > _leave_town_actions_count);
    return (LeaveTownAction) input-1;
}

void fight(DoomDepths game) {
    if (doom_depths_is_empty(game)) {
        log_error("Game is empty");
        return;
    };
    while (current_fight_is_finished() == false) {
        new_round(get_intern_game_state()); // TODO REMOVE param !
        end_round();
    }
}