
//
// Created by Theo OMNES on 23/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "weapon.h"
#include "../../utils/random/random.h"

Weapon random_weapon() {
    WeaponKind kind = (WeaponKind) random_between_included(EMPTY_WEAPON, __weapons_count - 1);
    Weapon w = {
            kind,
            kind == EMPTY_WEAPON ? 0 : random_between_included(5, 20),
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

Weapon empty_weapon() {
    Weapon w = {
            EMPTY_WEAPON,
            0
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
        case EMPTY_WEAPON: return "empty";
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