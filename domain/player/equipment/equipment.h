
//
// Created by Theo OMNES on 25/09/2023.
//

#ifndef DOOMDEPTHS_EQUIPMENT_H
#define DOOMDEPTHS_EQUIPMENT_H

#include "weapon/weapon.h"
#include "armor/armor.h"

typedef struct Equipment {
    Weapon weapon;
    Armor armor;
} Equipment;

Equipment empty_equipment();

Equipment default_equipment();

char *equipment_to_string(Equipment e);

#endif //DOOMDEPTHS_EQUIPMENT_H
