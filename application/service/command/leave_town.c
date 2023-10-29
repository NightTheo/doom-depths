
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include <port/in/command/leave_town.h>
#include <port/out/persistence/intern_game_state/game_state.h>
#include <port/in/command/leave_town_action.h>
#include <port/out/log/log_error.h>
#include <port/in/command/new_run.h>
#include <port/in/command/continue_last_run.h>
#include <port/out/log/log_repository_status.h>

bool leave_town(LeaveTownAction action) {
    if (action < 0 || action >= _leave_town_actions_count) {
        log_error("Not a valid action");
        return false;
    }

    switch (action) {
        case NEW_RUN:
            new_run();
            return true;
        case RESTORE_LAST_GAME: {
            GameState status = continue_last_run();
            return status.repository_status == RESTORE_LAST_GAME_SUCCEEDED;
        }
        default: {
            log_error("Unknown choice [%d]", action);
            new_run();
            return false;
        }
    }
}