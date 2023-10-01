
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

#define LOG_FILE_PATH "log.txt"
#define LOG_INFO_FORMAT "[%s][info] %s\n" // [time][info] msg
#define LOG_ERROR_FORMAT "[%s][error] %s\n" // [time][error] msg
#define REPOSITORY_STATUS_FORMAT "Repository status: [%s]\n"

void log_info(const char *msg_info) {
    FILE *f = fopen(LOG_FILE_PATH, "at");
    if (f == NULL) return;
    char *now = now_to_str();
    if (now == NULL) return;
    fprintf(f, LOG_INFO_FORMAT, now, msg_info);
    fclose(f);
    free(now);
}

void log_error(const char *msg_error) {
    FILE *f = fopen(LOG_FILE_PATH, "at");
    if (f == NULL) return;
    char *now = now_to_str();
    if (now == NULL) return;
    fprintf(stderr, LOG_ERROR_FORMAT, now, msg_error);
    fclose(f);
    free(now);
}

void log_allocation_error() {
    FILE *f = fopen(LOG_FILE_PATH, "at");
    if (f == NULL) return;
    log_error("failed allocate memory");
    fclose(f);
}

void log_monster(Monster m) {
    FILE *f = fopen(LOG_FILE_PATH, "at");
    if (f == NULL) return;
    char *s = monster_to_string(m);
    fprintf(f, "%s\n", s);
    free(s);
    fclose(f);
}

void log_monsters(MonstersList m) {
    for (int8_t i = 0; i < m.size; i++) {
        log_monster(m.monsters[i]);
    }
}

void log_player(Player p) {
    FILE *f = fopen(LOG_FILE_PATH, "at");
    if (f == NULL) return;
    char *s = player_to_string(p);
    fprintf(f, "%s\n", s);
    free(s);
    fclose(f);
}

void log_grimoire(Grimoire g) {
    FILE *f = fopen(LOG_FILE_PATH, "at");
    if (f == NULL) return;
    char *s = grimoire_to_string(g);
    fprintf(f, "%s\n", s);
    free(s);
    fclose(f);
}

void log_repository_status(RepositoryStatus status) {
    FILE *f = fopen(LOG_FILE_PATH, "at");
    if (f == NULL) return;
    char log[64];
    const char *status_str = repository_status_to_string(status);
    snprintf(log, 64, REPOSITORY_STATUS_FORMAT, status_str);
    fprintf(f, log, status_str);
    fclose(f);
}