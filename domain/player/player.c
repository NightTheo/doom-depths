
//
// Created by Theo OMNES on 12/09/2023.
//

#include <string.h>
#include "player.h"
#include "stdlib.h"
#include "stdio.h"
#include "../../infrastructure/utils/log/log.h"
#include "../../infrastructure/utils/utils.h"

Player player_use_potion_from_inventory(Player player, uint8_t index_item);

Player player(uint8_t max_health, uint8_t mana) {
    Equipment equipment = default_equipment();
    Player p = {
            max_health,
            max_health,
            equipment.weapon.max_number_of_attacks_per_turn,
            equipment,
            empty_inventory(),
            mana,
            mana,
    };
    return p;
}

char* player_to_string(Player p) {
    char* s = malloc(1024);
    char* equipment_str = equipment_to_string(p.equipment);
    char* inventory_str = inventory_to_string(p.inventory);
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

    free(equipment_str);free(inventory_str);
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

Player player_equip_weapon_from_inventory(Player p, uint8_t weapon_index) {
    char log[128];
    if(weapon_index < 0 || weapon_index >= p.inventory.capacity) {
        snprintf(log, 128, "Index [%d] is not in inventory", weapon_index);log_error(log);
        return p;
    }
    InventoryItem w = p.inventory.items[weapon_index];
    Weapon weapond_equiped_before = p.equipment.weapon;
    p.equipment.weapon = *((Weapon*)w.item);

    p.inventory.items[weapon_index] = weapon_inventory_item(weapond_equiped_before);
    p.remaining_number_of_attacks = min(
            p.remaining_number_of_attacks,
            p.equipment.weapon.max_number_of_attacks_per_turn
            );

    free(w.item);
    w.item = NULL;

    //log
    char* w_str= weapon_to_string(p.equipment.weapon);snprintf(log, 128, "Player equiped %s", w_str);log_info(log);free(w_str);
    return p;
}

Player player_equip_armor_from_inventory(Player p, uint8_t armor_index) {
    char log[128];
    if(armor_index < 0 || armor_index >= p.inventory.capacity) {
        snprintf(log, 128, "Index [%d] is not in inventory", armor_index);log_error(log);
        return p;
    }

    InventoryItem a = p.inventory.items[armor_index];
    Armor armor_equiped_before = p.equipment.armor;
    p.equipment.armor = *((Armor*) a.item);
    p.inventory.items[armor_index] = armor_inventory_item(armor_equiped_before);

    free(a.item);
    a.item = NULL;

    // log
    char* a_str= armor_to_string(p.equipment.armor);snprintf(log, 128, "Player equiped %s", a_str);log_info(log);free(a_str);
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
            log_info("Empty item, nothing to do.");
            break;
        case WEAPON_ITEM:
            p = player_equip_weapon_from_inventory(p, index_item);
            break;
        case ARMOR_ITEM:
            p = player_equip_armor_from_inventory(p, index_item);
            break;
        default:
            log_info("Item not equipable");
            break;
    }

    return p;
}

Player player_use_item_from_inventory(Player p, uint8_t index_item) {
    char log[64];
    if(index_item < 0 || index_item >= p.inventory.capacity) {
        snprintf(log, 64, "Index [%d] is not in inventory", index_item);log_error(log);
        return p;
    }

    InventoryItem item_to_use = p.inventory.items[index_item];
    switch (item_to_use.type) {
        case EMPTY_ITEM:
            log_info("Empty item, nothing to do.");
            break;
        case POTION_ITEM:
            p = player_use_potion_from_inventory(p, index_item);
            break;
        default:
            log_info("Item not usable");
            break;
    }

    return p;
}

Player player_use_potion_from_inventory(Player player, uint8_t potion_index) {
    char log[128];
    if(potion_index < 0 || potion_index >= player.inventory.capacity) {
        snprintf(log, 128, "Index [%d] is not in inventory", potion_index);log_error(log);
        return player;
    }

    InventoryItem potion_item = player.inventory.items[potion_index];
    ManaPotion mana_potion = *((ManaPotion*)potion_item.item);
    if(mana_potion.is_full) {
        player_recover_mana(player, player.max_mana);
    } else {
        strcpy(log,"Potion is empty");log_info(log);
    }

    player.inventory.items[potion_index] = empty_inventory_item();
    free(potion_item.item);
    potion_item.item = NULL;
    return player;
}