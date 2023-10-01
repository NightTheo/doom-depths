
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include <stdlib.h>

#include "../../../../domain/monsters/monsters.h"

#include "../../../../application/port/out/ihm/get_monster_to_attack.h"

#include "../../../../application/port/out/log/log_info.h"
#include "../../../../application/port/out/log/log_monster.h"

void display_monsters(MonstersList monsters);


int8_t get_monster_index_to_attack(MonstersList monsters) {
    display_monsters(monsters);
    fprintf(stdout, "Select a monster to attack [1-%d]\n",monsters.size);
    int8_t input = 0;
    // TODO better check input
    do {
        fflush(stdin);
        scanf("%hhd", &input);
    } while (input < 1 || input > monsters.size);
    log_info("player choose monsters to attack");
    log_monster(monsters.monsters[input-1]);
    return input-1;
}

void display_monsters(MonstersList monsters) {
    for(int i = 0; i < monsters.size; i++) {
        char* s = monster_to_string(monsters.monsters[i]);
        fprintf(stdout, "%d. %s\n", i+1, s);
        free(s);
    }
}