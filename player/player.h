
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
    u_int8_t current_health;
    u_int8_t max_health;
    u_int8_t remaining_number_of_attacks;
    u_int8_t max_number_of_attacks_per_tour;
    Equipment equipement;
    Inventory inventory;
} Player;

Player player(u_int8_t max_health, u_int8_t number_of_attacks_per_tour);
char* player_to_string(Player p);
Player restore_player_number_of_remaining_attacks(Player);
bool player_is_dead(Player p);
bool player_is_alive(Player p);
Player player_equip_item_from_inventory(Player p, uint8_t index_item);

#endif //DOOMDEPTHS_PLAYER_H
