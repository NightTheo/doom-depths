
//
// Created by Theo OMNES on 23/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "weapon.h"
#include "../../utils/random/random.h"

Weapon random_weapon() {
    WeaponKind kind = (WeaponKind) random_between_included(EMPTY_WEAPON, __weapons_count - 1);
    if(kind == EMPTY_WEAPON) return empty_weapon();
    Weapon w = {
            kind,
            random_between_included(5, 10),
            random_between_included(8, 15),
            random_between_included(2, 5),
    };
    return w;
}

Weapon weapon(WeaponKind kind, uint8_t min_damages, uint8_t max_damages, uint8_t max_number_of_attack_per_turn) {
    Weapon w = {
            kind,
            min_damages,
            max_damages,
            max_number_of_attack_per_turn,
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
    allocated->min_damages = w.min_damages;
    allocated->max_damages = w.max_damages;
    allocated->max_number_of_attacks_per_turn = w.max_number_of_attacks_per_turn;
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
    char* str = malloc(128);
    snprintf(str, 127, "Weapon {kind: %s, min_damages: %d, max_damages: %d, max_number_of_attacks_per_turn: %d}",
             weapon_kind_to_string(w.kind),
             w.min_damages,
             w.max_damages,
             w.max_number_of_attacks_per_turn
             );
    return str;
}