
//
// Created by Theo OMNES on 01/10/2023.
//

#include "../../../application/port/in/command/start_ihm.h"

#include "../../../application/port/out/ihm/display_game_over.h"
#include "../../../application/port/out/persistence/intern_game_state/game_state.h"
#include "../../../application/port/in/command/leave_town_action.h"
#include "../../../application/port/in/command/leave_town.h"
#include "../../../application/port/out/persistence/intern_game_state/get_intern_game_state.h"
#include "../../../application/port/in/command/player_enter_zone.h"
#include "../../../application/port/in/query/is_player_alive.h"
#include "../../../application/port/in/command/finish_current_zone.h"
#include "cli_controllers.h"

void start_ihm() {
    display_leave_town_actions();
    LeaveTownAction leave_town_action = get_leave_town_action();

    leave_town(leave_town_action);

    while (true) {
        DoomDepths game = player_enter_zone(enter_map(get_intern_game_state().map));

        fight(game);

        bool player_won = current_player_is_alive();
        if (player_won) {
            finish_current_zone();
        } else {
            display_game_over();
            free_doom_depths(get_intern_game_state());
            break;
        }
    }
}