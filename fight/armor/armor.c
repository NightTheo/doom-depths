
//
// Created by Theo OMNES on 25/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "armor.h"
#include "../../utils/log/log.h"
#include "../../utils/random/random.h"

Armor armor(ArmorKind kind, uint8_t defense) {
    Armor a = {
            kind,
            defense
    };
    return a;
}

Armor* armor_alloc(Armor a) {
    Armor* armor = malloc(sizeof(a));
    armor->kind = a.kind;
    armor->defense = a.defense;
    return armor;
}

Armor empty_armor() {
    return armor(EMPTY_ARMOR, 0);
}

Armor random_armor() {
    ArmorKind kind = random_between_included(EMPTY_ARMOR, __armor_kind_count-1);
    if(kind == EMPTY_ARMOR) return empty_armor();

    return (Armor) {
        kind,
        random_between_included(5, 15),
    };
}

const char* armor_kind_to_string(ArmorKind armorKind) {
    char log[32];
    switch (armorKind) {

        case EMPTY_ARMOR: return "Empty armor";
        case CHEST_PLATE: return "Chest plate";
        default:
            snprintf(log, 31, "unkown armor kind [%d]", armorKind);log_error(log);
            return "?";
    }
}

char* armor_to_string(Armor a) {
    uint8_t str_len = 64;
    char* s = malloc(str_len);
    snprintf(s, str_len-1, "Armor {kind: %s, defense: %d}", armor_kind_to_string(a.kind),a.defense);

    return s;
}