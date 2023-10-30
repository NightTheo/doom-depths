
//
// Created by Theo OMNES on 12/09/2023.
//

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "time/time_util.h"

#include "log_info.h"
#include "log_error.h"
#include "log_player.h"
#include "log_monster.h"
#include "log_grimoire.h"

#include "player.h"
#include "monsters.h"

#define MAX_LOG_SIZE 4096



/**
 * Inspired by #trevodorax aka Paul GAUDEAUX
 */
void log_info(const char *msg_info, ...) {
    char *now = now_to_str();
    if (now == NULL) return;

    va_list args;
    va_start(args, msg_info);

    char str[MAX_LOG_SIZE];
    str[0] = '\0';
    vsnprintf(str, MAX_LOG_SIZE, msg_info, args);
    fprintf(stdout, "[%s][info] %s\n", now, str);

    free(now);
    va_end(args);
}

void log_error(const char *msg_error, ...) {
    va_list args;
    va_start(args, msg_error);

    char *now = now_to_str();
    if (now != NULL) {
        char str[MAX_LOG_SIZE];
        str[0] = '\0';
        vsnprintf(str, MAX_LOG_SIZE, msg_error, args);
        fprintf(stderr, "[%s][error] %s\n", now, str);
        free(now);
    }

    va_end(args);
}

void log_allocation_error() {
    log_error("failed allocate memory");
}

void log_monster(Monster m) {
    char *s = monster_to_string(m);
    log_info(s);
    free(s);
}

void log_monsters(MonstersList m) {
    for (int8_t i = 0; i < m.size; i++) {
        log_monster(m.monsters[i]);
    }
}

void log_player(Player p) {
    char *s = player_to_string(p);
    log_info(s);
    free(s);
}

void log_grimoire(Grimoire g) {
    char *s = grimoire_to_string(g);
    log_info(s);
    free(s);
}