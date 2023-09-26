
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_WEAPON_H
#define DOOMDEPTHS_WEAPON_H

#include "stdint.h"

typedef enum WeaponKind {
    EMPTY_WEAPON = 0,
    SWORD,


    __weapons_count
} WeaponKind;

typedef struct Weapon {
    enum WeaponKind kind;
    uint8_t min_damages;
    uint8_t max_damages;
    uint8_t max_number_of_attacks_per_turn;
} Weapon;

Weapon random_weapon();
char* weapon_to_string(Weapon w);
WeaponKind weapon_kind_from_string(const char* str);
Weapon weapon(WeaponKind kind, uint8_t min_damages, uint8_t max_damages, uint8_t max_number_of_attack_per_turn);
Weapon empty_weapon();
Weapon* weapon_alloc(Weapon w);

#endif //DOOMDEPTHS_WEAPON_H
