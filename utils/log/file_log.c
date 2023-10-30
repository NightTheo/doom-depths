
//
// Created by Theo OMNES on 12/09/2023.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <infrastructure/utils/time/time_util.h>

#include "log_info.h"
#include "log_error.h"
#include "log_player.h"
#include "log_monster.h"
#include "log_grimoire.h"
#include "application/port/out/persistence/storage/respository_status.h"
#include "log_repository_status.h"

#include "domain/player/player.h"
#include "domain/monsters/monsters.h"

#define LOG_FILE_PATH "log.txt"
#define LOG_INFO_FORMAT "[%s][info] %s\n" // [time][info] msg
#define LOG_ERROR_FORMAT "[%s][error] %s\n" // [time][error] msg
#define REPOSITORY_STATUS_FORMAT "Repository status: [%s]\n"

#define MAX_LOG_SIZE 4096

void log_info(const char *msg_info, ...) {
    FILE *f = fopen(LOG_FILE_PATH, "at");

    va_list args;
    va_start(args, msg_info);

    char *now = now_to_str();
    if (now != NULL) {
        char str[MAX_LOG_SIZE];
        str[0] = '\0';
        vsnprintf(str, MAX_LOG_SIZE, msg_info, args);
        fprintf(stderr, "[%s][info] %s\n", now, str);
        free(now);
    }
    va_end(args);

    fclose(f);
}

void log_error(const char *msg_error, ...) {
    FILE *f = fopen(LOG_FILE_PATH, "at");

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

    fclose(f);
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
    log_info(s);
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
    log_info(s);
    free(s);
    fclose(f);
}

void log_grimoire(Grimoire g) {
    FILE *f = fopen(LOG_FILE_PATH, "at");
    if (f == NULL) return;
    char *s = grimoire_to_string(g);
    log_info(s);
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