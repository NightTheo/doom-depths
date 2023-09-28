
//
// Created by Theo OMNES on 12/09/2023.
//

#include "log.h"
#include "stdlib.h"
#include "stdio.h"
#include "../../../domain/monsters/monsters.h"

#define LOG_FILE_PATH "log.txt"

void log_info(const char* msg_info) {
    FILE* f = fopen(LOG_FILE_PATH, "at");
    if(f == NULL) return;
    fprintf(f, "[info] %s\n", msg_info);
    fclose(f);
}

void log_error(const char* msg_error) {
    FILE* f = fopen(LOG_FILE_PATH, "at");
    if(f == NULL) return;
    fprintf(stderr,"[error] %s\n", msg_error);
    fclose(f);
}

void log_allocation_error() {
    FILE* f = fopen(LOG_FILE_PATH, "at");
    if(f == NULL) return;
    log_error("failed allocate memory");
    fclose(f);
}

void log_monster(Monster m) {
    FILE* f = fopen(LOG_FILE_PATH, "at");
    if(f == NULL) return;
    char* s = monster_to_string(m);
    fprintf(f, "%s\n", s);
    free(s);
    fclose(f);
}

void log_monsters(MonstersList m) {
    for(int8_t i = 0; i < m.size; i++) {
        log_monster(m.monsters[i]);
    }
}

void log_player(Player p) {
    FILE* f = fopen(LOG_FILE_PATH, "at");
    if(f == NULL) return;
    char* s = player_to_string(p);
    fprintf(f, "%s\n", s);
    free(s);
    fclose(f);
}

void log_grimoire(Grimoire g) {
    FILE* f = fopen(LOG_FILE_PATH, "at");
    if(f == NULL) return;
    char* s = grimoire_to_string(g);
    fprintf(f, "%s\n", s);
    free(s);
    fclose(f);
}