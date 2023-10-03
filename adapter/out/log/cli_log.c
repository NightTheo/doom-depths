
//
// Created by Theo OMNES on 12/09/2023.
//

#include <time.h>
#include <string.h>
#include "stdlib.h"
#include "stdio.h"

#include "../../../infrastructure/utils/time/time_util.h"

#include "../../../application/port/out/log/log_info.h"
#include "../../../application/port/out/log/log_error.h"
#include "../../../application/port/out/log/log_player.h"
#include "../../../application/port/out/log/log_monster.h"
#include "../../../application/port/out/log/log_grimoire.h"
#include "../../../application/port/out/persistence/storage/respository_status.h"
#include "../../../application/port/out/log/log_repository_status.h"

#include "../../../domain/player/player.h"
#include "../../../domain/monsters/monsters.h"

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

void log_repository_status(RepositoryStatus status) {
    char log[64];
    const char *status_str = repository_status_to_string(status);
    snprintf(log, 64, "Repository status: [%s]\\n", status_str);

    bool is_failure = status == SAVE_LAST_GAME_FAILED || status == RESTORE_LAST_GAME_FAILED;

    if(is_failure) {
        log_error(status_str);
    } else {
        log_info(status_str);
    }
}