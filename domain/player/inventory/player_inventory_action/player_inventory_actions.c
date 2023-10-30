
//
// Created by Theo OMNES on 25/09/2023.
//

#include "player_inventory_actions.h"
#include "log/log_error.h"

const char *inventory_action_to_string(PlayerInventoryAction action) {
    char log[32];
    switch (action) {
        case EXIT_INVENTORY:
            return "Exit inventory";
        case EQUIP_ITEM:
            return "Equip an item";
        case USE_ITEM:
            return "Use item";
        default:
            log_error("Unkown PlayerInventoryAction [%d]", action);
            return "?";
    }
}