
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
#include "../../application/port/in/command/drink_potion.h"

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

Player free_player(Player p) {
    p.inventory = free_inventory(p.inventory);
    return p;
}