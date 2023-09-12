
//
// Created by Theo OMNES on 12/09/2023.
//

#include "player.h"
#include "../fight/weapon/weapon.h"

Player player(int8_t max_health, int8_t number_of_attacks_per_tour) {
    Weapon sword = {
            SWORD,
            10,
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