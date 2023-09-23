
//
// Created by Theo OMNES on 23/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "loot.h"
#include "../../utils/random/random.h"

Loot empty_loot() {
    Loot l = {
            0,
            EMPTY,
    };
    return l;
}

Loot random_loot() {
    Loot l = empty_loot();
    l.gold = (u_int16_t) random_between_included(0, 20);
    l.weapon = random_weapon();

    return l;
}

char* loot_to_string(Loot l) {
    char* str = malloc(100);
    char* weapon = weapon_to_string(l.weapon);
    snprintf(str,100,"Loot {gold: %d, %s}",l.gold,weapon);

    free(weapon);
    return str;
}