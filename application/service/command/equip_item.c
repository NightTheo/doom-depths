
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>

#include <port/in/command/equip_item.h>

#include <player.h>

#include "log/log_error.h"
#include "log/log_info.h"

#include "utils.h"
#include <port/out/persistence/intern_game_state/set_player.h>
#include <port/out/persistence/intern_game_state/get_player.h>


Player player_equip_weapon_from_inventory(Player p, uint8_t weapon_index);

Player player_equip_armor_from_inventory(Player p, uint8_t armor_index);


void player_equip_item_from_inventory(uint8_t index_item) {
    Player p = get_player();
    if (index_item < 0 || index_item >= p.inventory.capacity) {
        log_error("Index [%d] is not in inventory", index_item);
        return;
    }
    InventoryItem item_to_equip = p.inventory.items[index_item];
    switch (item_to_equip.type) {
        case EMPTY_ITEM:
            log_info("Empty item, nothing done.");
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


    set_player(p);
}


Player player_equip_weapon_from_inventory(Player p, uint8_t weapon_index) {
    if (weapon_index < 0 || weapon_index >= p.inventory.capacity) {
        log_error("Index [%d] is not in inventory", weapon_index);
        return p;
    }
    InventoryItem item_in_inventory = p.inventory.items[weapon_index];
    Weapon weapond_equiped_before = p.equipment.weapon;
    p.equipment.weapon = *((Weapon *) item_in_inventory.item);

    p.inventory.items[weapon_index] = weapon_inventory_item(weapond_equiped_before);
    p.remaining_number_of_attacks = min(
            p.remaining_number_of_attacks,
            p.equipment.weapon.max_number_of_attacks_per_turn
    );

    free(item_in_inventory.item);
    item_in_inventory.item = NULL;

    //log
    char *w_str = weapon_to_string(p.equipment.weapon);
    log_info("Player equiped %s", w_str);
    free(w_str);


    return p;
}

Player player_equip_armor_from_inventory(Player p, uint8_t armor_index) {
    if (armor_index < 0 || armor_index >= p.inventory.capacity) {
        log_error("Index [%d] is not in inventory", armor_index);
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
    log_info("Player equiped %s", a_str);
    free(a_str);

    return p;
}
