
//
// Created by Theo OMNES on 23/09/2023.
//

#ifndef DOOMDEPTHS_LOOT_H
#define DOOMDEPTHS_LOOT_H

#include "stdint.h"
#include "../weapon/weapon.h"
#include "../armor/armor.h"

typedef struct Loot {
    u_int16_t gold;
    Weapon weapon;
    Armor armor;
} Loot;

Loot empty_loot();
Loot random_loot();
char* loot_to_string(Loot l);

#endif //DOOMDEPTHS_LOOT_H
