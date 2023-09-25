
//
// Created by Theo OMNES on 25/09/2023.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "equipment.h"

Equipment default_equipment() {
    Equipment e = {
            weapon(SWORD, 15, 20, 10),
    };
    return e;
}

char* equipment_to_string(Equipment e) {
    uint16_t str_len = 512;
    char* str = malloc(str_len);
    char* weapon_str = weapon_to_string(e.weapon);

    snprintf(str, str_len, "Equipment {%s}", weapon_str);

    free(weapon_str);
    return str;
}