
//
// Created by Theo OMNES on 25/09/2023.
//

#include <stdio.h>
#include "player_inventory_actions.h"
#include "../../../../infrastructure/utils/log/log.h"

const char* inventory_action_to_string(PlayerInventoryAction action) {
    char log[32];
    switch (action) {
        case EXIT_INVENTORY: return "Exit inventory";
        case EQUIP_ITEM: return "Equip an item";
        case USE_ITEM: return "Use item";
        default:
            snprintf(log, 31, "Unkown PlayerInventoryAction [%d]", action);
            log_error(log);
            return "?";
    }
}