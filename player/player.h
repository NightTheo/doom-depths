
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_PLAYER_H
#define DOOMDEPTHS_PLAYER_H

#include "stdint.h"

#include "../fight/weapon/weapon.h"

typedef struct Player {
    int8_t current_health;
    int8_t max_health;
    int8_t remaining_number_of_attacks;
    int8_t number_of_attacks_per_tour;
    Weapon weapon;
} Player;

Player player(int8_t max_health, int8_t number_of_attacks_per_tour);

#endif //DOOMDEPTHS_PLAYER_H
