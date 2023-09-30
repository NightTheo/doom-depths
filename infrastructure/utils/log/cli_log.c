
//
// Created by Theo OMNES on 12/09/2023.
//

#include <time.h>
#include "log.h"
#include "stdlib.h"
#include "stdio.h"
#include "../../../domain/monsters/monsters.h"

void log_info(const char* msg_info) {
    char * now = now_to_str();
    if(now == NULL) return;
    fprintf(stdout, LOG_INFO_FORMAT, now, msg_info);
    free(now);
}

void log_error(const char* msg_error) {
    char * now = now_to_str();
    if(now == NULL) return;
    fprintf(stderr,LOG_ERROR_FORMAT, now, msg_error);
    free(now);
}

void log_allocation_error() {
    log_error("failed allocate memory");
}

void log_monster(Monster m) {
    char* s = monster_to_string(m);
    printf("%s\n", s);
    free(s);
}

void log_monsters(MonstersList m) {
    for(int8_t i = 0; i < m.size; i++) {
        log_monster(m.monsters[i]);
    }
}

void log_player(Player p) {
    char* s = player_to_string(p);
    printf("%s\n", s);
    free(s);
}

void log_grimoire(Grimoire g) {
    char* s = grimoire_to_string(g);
    printf("%s\n", s);
    free(s);
}