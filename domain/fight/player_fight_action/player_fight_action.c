
//
// Created by Theo OMNES on 13/09/2023.
//

#include "player_fight_actions.h"

const char* player_fight_action_to_string(PlayerFightAction action) {
    switch (action) {
        case ATTACK: return "Attack";
        case SHOW_INVENTORY: return "Show inventory";
        case END_TURN: return "End turn";
        case SAVE_GAME: return "Save All";
        default: return "no action";
    }
}