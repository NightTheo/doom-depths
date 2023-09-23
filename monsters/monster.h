
//
// Created by Theo OMNES on 11/09/2023.
//

#ifndef DOOMDEPTHS_MONSTER_H
#define DOOMDEPTHS_MONSTER_H

#include "stdint.h"

typedef struct Monster {
    int8_t health;
    int8_t min_attack_power;
    int8_t max_attack_power;
    int8_t defense;
} Monster;

typedef struct MonstersList {
    int8_t size;
    Monster* monsters;
} MonstersList;

#endif //DOOMDEPTHS_MONSTER_H
