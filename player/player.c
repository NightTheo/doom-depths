
//
// Created by Theo OMNES on 12/09/2023.
//

#include "player.h"
#include "../fight/weapon/weapon.h"
#include "stdlib.h"
#include "stdio.h"

Player player(int8_t max_health, int8_t number_of_attacks_per_tour) {
    Weapon sword = {
            SWORD,
            20,
    };

    Player p = {
            max_health,
            max_health,
            number_of_attacks_per_tour,
            number_of_attacks_per_tour,
            sword,
    };

    return p;
}

char* player_to_string(Player p) {
    char* s = malloc(100);
    // todo weapon
    sprintf(s, "{current_health: %d, max_health: %d, remaining_number_of_attacks: %d, max_number_of_attacks_per_tour: %d, weapon: ?}",
           p.current_health, p.max_health, p.remaining_number_of_attacks, p.max_number_of_attacks_per_tour);
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