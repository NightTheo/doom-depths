
//
// Created by Theo OMNES on 11/09/2023.
//

#ifndef DOOMDEPTHS_MONSTERS_H
#define DOOMDEPTHS_MONSTERS_H

#include "stdbool.h"

#include "monster.h"


Monster random_monster();
char* monster_to_string(Monster m);
MonstersList random_list_of_monsters(int8_t number_of_monsters);
MonstersList list_of_monster_without_dead_ones(MonstersList old_list);
bool monster_is_dead(Monster m);
#endif //DOOMDEPTHS_MONSTERS_H
