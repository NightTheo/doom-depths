
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include "../../../application/port/in/start_ihm.h"

#include "../../../application/port/in/start_fight.h"

#include "../../../application/port/out/ihm/display_leave_town_actions.h"
#include "../../../application/port/out/ihm/display_game_over.h"
#include "../../../application/port/out/ihm/display_map.h"
#include "../../../application/port/out/persistence/intern_game_state/game_state.h"
#include "../../../application/port/out/ihm/leave_town_action.h"
#include "../../../application/port/out/log/log_error.h"
#include "../../../application/port/in/new_run.h"
#include "../../../application/port/in/continue_last_run.h"

GameState get_game_state_by_leave_town_action();

void start_ihm() {
    display_leave_town_actions();
    GameState state = get_game_state_by_leave_town_action();
    while (true) {
        state.game = start_fight(state.game);
        if (player_is_dead(state.game.player)) {
            display_game_over();
            break;
        }
        state.game.map.spawn = enter_map(state.game.map);
        state.game.map = spawn_player_on_map_at_position(state.game.player, state.game.map, state.game.map.spawn);
    }

    free_doom_depths(state.game);
}

GameState get_game_state_by_leave_town_action() {
    int8_t input = -1;
    do {
        fflush(stdin);
        scanf("%hhd", &input);
    } while (input - 1 < 0 || input - 1 >= _leave_town_actions_count);

    switch ((LeaveTownAction) (input - 1)) {
        case NEW_RUN:
            return new_run();
        case RESTORE_LAST_GAME:
            return continue_last_run();
        default: {
            char log[64];
            sprintf(log, "Unknown choice [%d]", input);
            log_error(log);
            return new_run();
        }
    }
}