
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>

#include "../port/in/equip_item.h"

#include "../../domain/player/player.h"

#include "../port/out/log/log_error.h"
#include "../port/out/log/log_info.h"

#include "../../infrastructure/utils/utils.h"


Player player_equip_weapon_from_inventory(Player p, uint8_t weapon_index);
Player player_equip_armor_from_inventory(Player p, uint8_t armor_index);


Player player_equip_item_from_inventory(Player p, uint8_t index_item) {
    char log[64];
    if (index_item < 0 || index_item >= p.inventory.capacity) {
        snprintf(log, 64, "Index [%d] is not in inventory", index_item);
        log_error(log);
        return p;
    }
    InventoryItem item_to_equip = p.inventory.items[index_item];
    switch (item_to_equip.type) {
        case EMPTY_ITEM:
            log_info("Empty item, nothing to do.");
            break;
        case WEAPON_ITEM:
            p = player_equip_weapon_from_inventory(p, index_item);
            break;
        case ARMOR_ITEM:
            p = player_equip_armor_from_inventory(p, index_item);
            break;
        default:
            log_info("Item not equipable.");
            break;
    }

    return p;
}


Player player_equip_weapon_from_inventory(Player p, uint8_t weapon_index) {
    char log[128];
    if (weapon_index < 0 || weapon_index >= p.inventory.capacity) {
        snprintf(log, 128, "Index [%d] is not in inventory", weapon_index);
        log_error(log);
        return p;
    }
    InventoryItem w = p.inventory.items[weapon_index];
    Weapon weapond_equiped_before = p.equipment.weapon;
    p.equipment.weapon = *((Weapon *) w.item);

    p.inventory.items[weapon_index] = weapon_inventory_item(weapond_equiped_before);
    p.remaining_number_of_attacks = min(
            p.remaining_number_of_attacks,
            p.equipment.weapon.max_number_of_attacks_per_turn
    );

    free(w.item);
    w.item = NULL;

    //log
    char *w_str = weapon_to_string(p.equipment.weapon);
    snprintf(log, 128, "Player equiped %s", w_str);
    log_info(log);
    free(w_str);
    return p;
}

Player player_equip_armor_from_inventory(Player p, uint8_t armor_index) {
    char log[128];
    if (armor_index < 0 || armor_index >= p.inventory.capacity) {
        snprintf(log, 128, "Index [%d] is not in inventory", armor_index);
        log_error(log);
        return p;
    }

    InventoryItem a = p.inventory.items[armor_index];
    Armor armor_equiped_before = p.equipment.armor;
    p.equipment.armor = *((Armor *) a.item);
    p.inventory.items[armor_index] = armor_inventory_item(armor_equiped_before);

    free(a.item);
    a.item = NULL;

    // log
    char *a_str = armor_to_string(p.equipment.armor);
    snprintf(log, 128, "Player equiped %s", a_str);
    log_info(log);
    free(a_str);
    return p;
}
