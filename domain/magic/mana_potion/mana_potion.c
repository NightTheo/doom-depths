
//
// Created by Theo OMNES on 26/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "mana_potion.h"


ManaPotion mana_potion() {
    ManaPotion p = {
            true,
    };
    return p;
}

ManaPotion random_potion() {
    ManaPotion p = {
            rand() % 2,
    };
    return p;
}

char *potion_to_string(ManaPotion p) {
    uint16_t str_len = 64;
    char *s = malloc(str_len);

    snprintf(s, str_len, "ManaPotion {is_full: %s}", p.is_full ? "true" : "false");

    return s;
}

ManaPotion *mana_potion_alloc(ManaPotion p) {
    ManaPotion *potion = malloc(sizeof(p));
    potion->is_full = p.is_full;
    return potion;
}