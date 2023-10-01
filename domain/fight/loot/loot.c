
//
// Created by Theo OMNES on 23/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "loot.h"
#include "../../../infrastructure/utils/random/random.h"

Loot empty_loot() {
    Loot l = {
            0,
            empty_weapon(),
            {EMPTY_ARMOR, 0},
            {0},
    };
    return l;
}

Loot random_loot() {
    Loot l = empty_loot();
    l.gold = (u_int16_t) random_between_included(0, 20);
    l.weapon = random_weapon();
    l.armor = random_armor();
    l.potion = random_potion();
    return l;
}

char *loot_to_string(Loot l) {
    uint16_t str_len = 256;
    char *str = malloc(str_len);
    char *weapon_str = weapon_to_string(l.weapon);
    char *armor_str = armor_to_string(l.armor);
    char *potion_str = potion_to_string(l.potion);
    snprintf(str, str_len - 1,
             "Loot {gold: %d, %s, %s, %s}",
             l.gold, weapon_str, armor_str, potion_str);

    free(weapon_str);
    free(armor_str);
    free(potion_str);
    return str;
}