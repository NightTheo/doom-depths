
//
// Created by Theo OMNES on 25/09/2023.
//

#ifndef DOOMDEPTHS_PLAYER_INVENTORY_ACTIONS_H
#define DOOMDEPTHS_PLAYER_INVENTORY_ACTIONS_H

typedef enum PlayerInventoryAction {
    EQUIP_ITEM,
    // TODO unequip item

    EXIT_INVENTORY,
    _player_inventory_action_count
} PlayerInventoryAction;

const char* inventory_action_to_string(PlayerInventoryAction action);

#endif //DOOMDEPTHS_PLAYER_INVENTORY_ACTIONS_H
