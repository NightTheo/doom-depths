
//
// Created by Theo OMNES on 13/09/2023.
//

#include "player_actions.h"

const char* player_action_to_string(PlayerAction action) {
    switch (action) {
        case ATTACK: return "Attack";
        case END_TURN: return "End turn";
        default: return "no action";
    }
}