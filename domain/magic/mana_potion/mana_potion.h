
//
// Created by Theo OMNES on 26/09/2023.
//

#ifndef DOOMDEPTHS_MANA_POTION_H
#define DOOMDEPTHS_MANA_POTION_H

#include "stdint.h"
#include "stdbool.h"

typedef struct ManaPotion {
    bool is_full;
} ManaPotion;

ManaPotion mana_potion();
ManaPotion random_potion();
char* potion_to_string(ManaPotion p);
ManaPotion* mana_potion_alloc(ManaPotion p);

#endif //DOOMDEPTHS_MANA_POTION_H
