
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>

#include "../../../../application/port/out/ihm/leave_town_action.h"

#include "../../../../application/port/in/new_run.h"
#include "../../../../application/port/in/continue_last_run.h"

#include "../../../../application/port/out/persistence/restore_last_game.h"
#include "../../../../application/port/out/log/log_error.h"


const char *leave_town_options_to_string(LeaveTownAction action);


GameState leave_town() {
    for (LeaveTownAction a = 0; a < _leave_town_actions_count; a++) {
        fprintf(stdout, "%d. %s\n", a + 1, leave_town_options_to_string(a));
    }
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

const char *leave_town_options_to_string(LeaveTownAction action) {
    char log[64];
    switch (action) {

        case NEW_RUN:
            return "NEW RUN";
        case RESTORE_LAST_GAME:
            return "CONTINUE";
        default:
            sprintf(log, "Unknown action [%d]", action);
            log_error(log);
            return "Unknown action";
    }
}