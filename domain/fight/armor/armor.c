
//
// Created by Theo OMNES on 25/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "armor.h"
#include "../../../infrastructure/utils/random/random.h"
#include "../../../application/port/out/log/log_error.h"

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
    const char* kind = armor_kind_to_string(a.kind);
    snprintf(s, str_len, "Armor {kind: %s, defense: %d}", kind, a.defense);

    return s;
}

ArmorKind armor_kind_from_string(const char* str) {
    if(strcmp(str, "EMPTY_ARMOR") == 0) return EMPTY_ARMOR;
    if(strcmp(str, "CHEST_PLATE") == 0) return CHEST_PLATE;

    char log[32];
    snprintf(log, 32, "[%s] does not match an ArmorKind", str);
    log_error(log);
    return EMPTY_ARMOR; // by default
}