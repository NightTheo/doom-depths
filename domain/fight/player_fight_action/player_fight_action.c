
//
// Created by Theo OMNES on 13/09/2023.
//

#include <stdio.h>
#include "player_fight_actions.h"
#include "../../../application/port/out/log/log_error.h"

const char *player_fight_action_to_string(PlayerFightAction action) {
    char log[64];
    switch (action) {
        case ATTACK:
            return "Attack";
        case OPEN_GRIMOIRE:
            return "Open grimoire";
        case SHOW_INVENTORY:
            return "Show inventory";
        case END_TURN:
            return "End turn";
        case SAVE_GAME:
            return "Save All";
        default:
            sprintf(log, "Unknown action [%d]", action);
            log_error(log);
            return "Unknown action";
    }
}