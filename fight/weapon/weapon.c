
//
// Created by Theo OMNES on 23/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "weapon.h"
#include "../../utils/random/random.h"

Weapon random_weapon() {
    Weapon w = {
            random_between_included(EMPTY, __weapons_count - 1),
            random_between_included(5, 20)
    };
    return w;
}

const char* weapon_kind_to_string(WeaponKind kind) {
    switch (kind) {
        case EMPTY: return "empty";
        case SWORD: return "sword";
        default: return "?";
    }
}

char* weapon_to_string(Weapon w) {
    char* str = malloc(32);
    snprintf(str, 32, "Weapon {kind: %s, damages: %d}",
             weapon_kind_to_string(w.kind),
             w.damages
             );
    return str;
}