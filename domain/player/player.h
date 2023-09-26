
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_PLAYER_H
#define DOOMDEPTHS_PLAYER_H

#include "stdint.h"
#include "stdbool.h"

#include "../fight/weapon/weapon.h"
#include "inventory/inventory.h"
#include "equipment/equipment.h"

typedef struct Player {
    uint8_t current_health;
    uint8_t max_health;
    uint8_t remaining_number_of_attacks;
    Equipment equipment;
    Inventory inventory;
    uint8_t current_mana;
    uint8_t max_mana;
} Player;

Player player(uint8_t max_health, uint8_t mana);
char* player_to_string(Player p);
Player restore_player_number_of_remaining_attacks(Player);
Player player_recover_mana(Player p, uint8_t mana);
bool player_is_dead(Player p);
bool player_is_alive(Player p);
Player player_equip_item_from_inventory(Player p, uint8_t index_item);
Player player_use_item_from_inventory(Player p, uint8_t index_item);

#endif //DOOMDEPTHS_PLAYER_H
