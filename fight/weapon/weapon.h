
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_WEAPON_H
#define DOOMDEPTHS_WEAPON_H

#include "stdint.h"

enum WeaponKind {
    EMPTY = 0,
    SWORD,
};

typedef struct Weapon {
    enum WeaponKind kind;
    int8_t damages;
} Weapon;

#endif //DOOMDEPTHS_WEAPON_H
