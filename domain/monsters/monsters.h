
//
// Created by Theo OMNES on 11/09/2023.
//

#ifndef DOOMDEPTHS_MONSTERS_H
#define DOOMDEPTHS_MONSTERS_H

#include "stdint.h"
#include "stdbool.h"
#include "monsters.h"

typedef struct Monster {
    int8_t health;
    int8_t min_attack_power;
    int8_t max_attack_power;
    int8_t defense;
} Monster;

typedef struct MonstersList {
    int8_t size;
    Monster *monsters;
} MonstersList;

// TODO random monsters by turn/level
Monster random_monster();

char *monster_to_string(Monster m);

MonstersList empty_monster_list();

bool monster_list_is_empty(MonstersList);

MonstersList random_list_of_monsters(int8_t number_of_monsters);

MonstersList list_of_monster_without_dead_ones(MonstersList old_list);

bool monster_is_dead(Monster m);

MonstersList free_monsters_list(MonstersList monsters_list);

#endif //DOOMDEPTHS_MONSTERS_H
