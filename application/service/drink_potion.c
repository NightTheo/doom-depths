
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include <string.h>

#include "../port/in/drink_potion.h"

#include "../../domain/player/player.h"

#include "../port/out/log/log_error.h"
#include "../port/out/log/log_info.h"
#include "../port/out/persistence/intern_game_state/set_player.h"

Player drink_potion_at_index(Player player, uint8_t potion_index) {
    char log[128];
    if (potion_index < 0 || potion_index >= player.inventory.capacity) {
        snprintf(log, 128, "Index [%d] is not in inventory", potion_index);
        log_error(log);
        return player;
    }

    if (player.inventory.items[potion_index].type != POTION_ITEM) {
        snprintf(log, 128, "Item at index [%d] is not a potion", potion_index);
        log_error(log);
        return player;
    }

    InventoryItem potion_item = player.inventory.items[potion_index];
    ManaPotion mana_potion = *((ManaPotion *) potion_item.item);
    if (mana_potion.is_full) {
        player_recover_mana(player, player.max_mana);
    } else {
        strcpy(log, "Potion is empty.");
        log_info(log);
    }

    player.inventory.items[potion_index] = empty_inventory_item();
    free(potion_item.item);
    potion_item.item = NULL;
    return set_player(player);
}