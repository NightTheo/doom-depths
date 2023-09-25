
//
// Created by Theo OMNES on 12/09/2023.
//

#include "player.h"
#include "stdlib.h"
#include "stdio.h"
#include "../utils/log/log.h"

Player player(u_int8_t max_health, u_int8_t number_of_attacks_per_tour) {
    Player p = {
            max_health,
            max_health,
            number_of_attacks_per_tour,
            number_of_attacks_per_tour,
            default_equipment(),
            empty_inventory(),
    };
    return p;
}

char* player_to_string(Player p) {
    char* s = malloc(1024);
    char* equipment_str = equipment_to_string(p.equipement);
    char* inventory_str = inventory_to_string(p.inventory);
    sprintf(s, "{current_health: %d, "
               "max_health: %d, "
               "remaining_number_of_attacks: %d, "
               "max_number_of_attacks_per_tour: %d, "
               "%s, " // equipment
               "%s}", // inventory
           p.current_health,
           p.max_health,
           p.remaining_number_of_attacks,
           p.max_number_of_attacks_per_tour,
           equipment_str,
           inventory_str
           );

    free(equipment_str);free(inventory_str);
    return s;
}

Player restore_player_number_of_remaining_attacks(Player p) {
    p.remaining_number_of_attacks = p.max_number_of_attacks_per_tour;
    return p;
}

bool player_is_alive(Player p) {
    return p.current_health > 0;
}

bool player_is_dead(Player p) {
    return !player_is_alive(p);
}

Player player_equip_weapon_from_inventory(Player p, uint8_t weapon_index) {
    char log[64];
    if(weapon_index < 0 || weapon_index >= p.inventory.capacity) {
        snprintf(log, 64, "Index [%d] is not in inventory", weapon_index);log_error(log);
        return p;
    }
    InventoryItem w = p.inventory.items[weapon_index];
    Weapon weapond_equiped_before = p.equipement.weapon;
    p.equipement.weapon = *((Weapon*)w.item);

    p.inventory.items[weapon_index] = weapon_inventory_item(weapond_equiped_before);

    free(w.item);
    w.item = NULL;

    //log
    char* w_str= weapon_to_string(p.equipement.weapon);snprintf(log, 64, "Player equiped %s", w_str);log_info(log);free(w_str);
    return p;
}

Player player_equip_item_from_inventory(Player p, uint8_t index_item) {
    char log[64];
    if(index_item < 0 || index_item >= p.inventory.capacity) {
        snprintf(log, 64, "Index [%d] is not in inventory", index_item);log_error(log);
        return p;
    }
    InventoryItem item_to_equip = p.inventory.items[index_item];
    switch (item_to_equip.type) {
        case EMPTY_ITEM:
            snprintf(log, 64, "Empty item, nothing to do");log_info(log);
            break;
        case WEAPON_ITEM:
            p = player_equip_weapon_from_inventory(p, index_item);
            break;
    }

    return p;
}