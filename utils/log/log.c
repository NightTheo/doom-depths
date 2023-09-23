
//
// Created by Theo OMNES on 12/09/2023.
//

#include "log.h"
#include "stdlib.h"
#include "stdio.h"
#include "../../monsters/monsters.h"

void log_info(const char* msg_info) {
    printf("[info] %s\n", msg_info);
}

void log_error(const char* msg_error) {
    fprintf(stderr,"[error] %s\n", msg_error);
}

void log_allocation_error() {
    log_error("failed allocate memory");
}

void log_monster(Monster m) {
    char* s = monster_to_string(m);
    printf("Monster %s\n", s);
    free(s);
}

void log_monsters(MonstersList m) {
    for(int8_t i = 0; i < m.size; i++) {
        log_monster(m.monsters[i]);
    }
}

void log_player(Player p) {
    char* s = player_to_string(p);
    printf("Player %s\n", s);
    free(s);
}