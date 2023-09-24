
//
// Created by Theo OMNES on 23/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "weapon.h"
#include "../../utils/random/random.h"
#include "../../utils/utils.h"

Weapon random_weapon() {
    Weapon w = {
            random_between_included(EMPTY, __weapons_count - 1),
            random_between_included(5, 20)
    };
    return w;
}

Weapon weapon(WeaponKind kind, u_int8_t damages) {
    Weapon w = {
            kind,
            damages
    };
    return w;
}

Weapon* weapon_alloc(Weapon w) {
    Weapon* allocated = malloc(sizeof(Weapon));
    allocated->kind = w.kind;
    allocated->damages = w.damages;
    return allocated;
}

const char* weapon_kind_to_string(WeaponKind kind) {
    switch (kind) {
        case EMPTY: return "empty";
        case SWORD: return "sword";
        default: return "?";
    }
}

char* weapon_to_string(Weapon w) {
    char* str = malloc(64);
    snprintf(str, 64, "Weapon {kind: %s, damages: %d}",
             weapon_kind_to_string(w.kind),
             w.damages
             );
    return str;
}