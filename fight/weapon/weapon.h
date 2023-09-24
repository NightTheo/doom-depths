
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_WEAPON_H
#define DOOMDEPTHS_WEAPON_H

#include "stdint.h"

typedef enum WeaponKind {
    EMPTY = 0,
    SWORD,


    __weapons_count
} WeaponKind;

typedef struct Weapon {
    enum WeaponKind kind;
    u_int8_t damages;
} Weapon;

Weapon random_weapon();
char* weapon_to_string(Weapon w);
Weapon weapon(WeaponKind kind, u_int8_t damages);
Weapon* weapon_alloc(Weapon w);

#endif //DOOMDEPTHS_WEAPON_H
