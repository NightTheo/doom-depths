
//
// Created by Theo OMNES on 12/09/2023.
//

#include <string.h>
#include "player.h"
#include "stdlib.h"
#include "stdio.h"
#include "../../infrastructure/utils/utils.h"
#include "../../application/port/out/log/log_info.h"
#include "../../application/port/out/log/log_error.h"
#include "../../application/port/in/drink_potion.h"

Player player(uint8_t max_health, uint8_t mana) {
    Equipment equipment = default_equipment();
    Player p = {
            max_health,
            max_health,
            equipment.weapon.max_number_of_attacks_per_turn,
            equipment,
            start_grimoire(),
            empty_inventory(),
            mana,
            mana,
            false,
    };
    return p;
}

Player empty_player() {
    Player p;
    p.is_empty = true;
    p.current_mana = 0;
    p.max_mana = 0;
    p.current_health = 0;
    p.max_health = 0;
    p.inventory = no_inventory();
    p.equipment = empty_equipment();
    p.grimoire = empty_grimoire();
    p.remaining_number_of_attacks = 0;
    return p;
}

bool player_is_empty(Player p) {
    return p.is_empty;
}

char *player_to_string(Player p) {
    char *s = malloc(2048);
    char *equipment_str = equipment_to_string(p.equipment);
    char *inventory_str = inventory_to_string(p.inventory);
    sprintf(s, "Player {current_health: %d, "
               "max_health: %d, "
               "remaining_number_of_attacks: %d, "
               "max_number_of_attacks_per_turn: %d, "
               "current_mana: %d, "
               "max_mana: %d, "
               "%s, " // equipment
               "%s}", // inventory
            p.current_health,
            p.max_health,
            p.remaining_number_of_attacks,
            p.equipment.weapon.max_number_of_attacks_per_turn,
            p.current_mana,
            p.max_mana,
            equipment_str,
            inventory_str
    );

    free(equipment_str);
    free(inventory_str);
    return s;
}

Player restore_player_number_of_remaining_attacks(Player p) {
    p.remaining_number_of_attacks = p.equipment.weapon.max_number_of_attacks_per_turn;
    return p;
}

Player player_recover_mana(Player p, uint8_t mana) {
    p.current_mana = min(p.current_mana + mana, p.max_mana);
    return p;
}

bool player_is_alive(Player p) {
    return p.current_health > 0;
}

bool player_is_dead(Player p) {
    return !player_is_alive(p);
}

Player player_use_item_from_inventory(Player p, uint8_t index_item) {
    char log[64];
    if (index_item < 0 || index_item >= p.inventory.capacity) {
        snprintf(log, 64, "Index [%d] is not in inventory", index_item);
        log_error(log);
        return p;
    }

    InventoryItem item_to_use = p.inventory.items[index_item];
    switch (item_to_use.type) {
        case EMPTY_ITEM:
            log_info("Empty item, nothing to do.");
            break;
        case POTION_ITEM:
            p = drink_potion_at_index(p, index_item);
            break;
        default:
            log_info("Item not usable.");
            break;
    }

    return p;
}

Player free_player(Player p) {
    p.inventory = free_inventory(p.inventory);
    return p;
}

Player reset_remaining_number_of_attacks(Player player) {
    player.remaining_number_of_attacks = player.equipment.weapon.max_number_of_attacks_per_turn;
    return player;
}