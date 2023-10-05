
//
// Created by Theo OMNES on 23/09/2023.
//

#ifndef DOOMDEPTHS_LOOT_H
#define DOOMDEPTHS_LOOT_H

#include "stdint.h"
#include "stdbool.h"
#include <domain/fight/weapon/weapon.h>
#include <domain/fight/armor/armor.h>
#include <domain/magic/mana_potion/mana_potion.h>

typedef struct Loot {
    u_int16_t gold;
    Weapon weapon;
    Armor armor;
    ManaPotion potion;
} Loot;

Loot empty_loot();

Loot random_loot();

char *loot_to_string(Loot l);

bool loot_is_not_empty(Loot l);

#endif //DOOMDEPTHS_LOOT_H
