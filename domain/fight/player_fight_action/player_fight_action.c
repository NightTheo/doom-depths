
//
// Created by Theo OMNES on 13/09/2023.
//

#include "player_fight_actions.h"
#include <application/port/out/log/log_error.h>

const char *player_fight_action_to_string(PlayerFightAction action) {
    switch (action) {
        case ATTACK:
            return "Attack";
        case OPEN_GRIMOIRE:
            return "Open grimoire";
        case SHOW_INVENTORY:
            return "Show inventory";
        case END_ROUND:
            return "End round";
        case SAVE_GAME:
            return "Save All";
        default:
            log_error("Unknown action [%d]", action);
            return "Unknown action";
    }
}