
//
// Created by Theo OMNES on 11/09/2023.
//

#include "monsters.h"

#include <stdlib.h>
#include <stdio.h>
#include "../utils/random/random.h"
#include "../utils/log/log.h"

Monster random_monster() {
    Monster m = {
            random_between_included(1, 10),
            random_between_included(5, 9),
            random_between_included(10, 20),
            random_between_included(0, 10)
    };
    return m;
}

MonstersList random_list_of_monsters(int8_t number_of_monsters) {
    Monster* m = malloc(sizeof(Monster) * number_of_monsters);
    if(NULL == m) {
        log_allocation_error();
        exit(EXIT_FAILURE);
    }
    for(int8_t i = 0; i < number_of_monsters; i++) {
        m[i] = random_monster();
    }
    MonstersList list = {number_of_monsters, m};
    return list;
}

char* monster_to_string(Monster m) {
    char* s = malloc(70);
    sprintf(s, "{health: %d, min_attack_power: %d, max_attack_power: %d, defense: %d}",
            m.health, m.min_attack_power, m.max_attack_power, m.defense);
    return s;
}

int8_t count_number_of_monsters_alive_in_list(MonstersList list) {
    int8_t number_of_monsters_alive = 0;
    for(int8_t i = 0; i < list.size; i++) {
        if(list.monsters[i].health > 0) number_of_monsters_alive += 1;
    }
    return number_of_monsters_alive;
}

MonstersList list_of_monster_without_dead_ones(MonstersList old_list) {
    int8_t number_of_monster_alive = count_number_of_monsters_alive_in_list(old_list);
    MonstersList new_list = {
            number_of_monster_alive,
            malloc(sizeof(Monster) * number_of_monster_alive)
    };
    int8_t new_list_index = 0;
    for(int8_t old_list_index = 0; old_list_index < old_list.size; old_list_index++) {
        if(old_list.monsters[old_list_index].health <= 0) continue;
        new_list.monsters[new_list_index] = old_list.monsters[old_list_index];
        new_list_index += 1;
    }

    free(old_list.monsters);
    old_list.monsters = NULL;
    return new_list;
}