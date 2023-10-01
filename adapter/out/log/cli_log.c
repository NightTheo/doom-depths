
//
// Created by Theo OMNES on 12/09/2023.
//

#include <time.h>
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

#define LOG_INFO_FORMAT "[%s][info] %s\n" // [time][info] msg
#define LOG_ERROR_FORMAT "[%s][error] %s\n" // [time][error] msg
#define REPOSITORY_STATUS_FORMAT "Repository status: [%s]\n"

void log_info(const char *msg_info) {
    char *now = now_to_str();
    if (now == NULL) return;
    fprintf(stdout, LOG_INFO_FORMAT, now, msg_info);
    free(now);
}

void log_error(const char *msg_error) {
    char *now = now_to_str();
    if (now == NULL) return;
    fprintf(stderr, LOG_ERROR_FORMAT, now, msg_error);
    free(now);
}

void log_allocation_error() {
    log_error("failed allocate memory");
}

void log_monster(Monster m) {
    char *s = monster_to_string(m);
    printf("%s\n", s);
    free(s);
}

void log_monsters(MonstersList m) {
    for (int8_t i = 0; i < m.size; i++) {
        log_monster(m.monsters[i]);
    }
}

void log_player(Player p) {
    char *s = player_to_string(p);
    printf("%s\n", s);
    free(s);
}

void log_grimoire(Grimoire g) {
    char *s = grimoire_to_string(g);
    printf("%s\n", s);
    free(s);
}

void log_repository_status(RepositoryStatus status) {
    char log[64];
    const char *status_str = repository_status_to_string(status);
    snprintf(log, 64, REPOSITORY_STATUS_FORMAT, status_str);
    fprintf(stdout, log, status_str);
}