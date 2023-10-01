
//
// Created by Theo OMNES on 25/09/2023.
//

#ifndef DOOMDEPTHS_ARMOR_H
#define DOOMDEPTHS_ARMOR_H

#include <stdint.h>

typedef enum ArmorKind {
    EMPTY_ARMOR = 0,
    CHEST_PLATE,

    __armor_kind_count
} ArmorKind;


typedef struct Armor {
    ArmorKind kind;
    uint8_t defense;
} Armor;

Armor armor(ArmorKind kind, uint8_t defense);

Armor *armor_alloc(Armor a);

Armor random_armor();

char *armor_to_string(Armor a);

ArmorKind armor_kind_from_string(const char *str);

#endif //DOOMDEPTHS_ARMOR_H
