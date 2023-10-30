
//
// Created by Theo OMNES on 12/09/2023.
//

#include "log_info.h"
#include "log_error.h"
#include "log_monster.h"
#include "log_player.h"
#include "log_grimoire.h"

#include "domain/player/player.h"
#include "domain/monsters/monsters.h"

#define LOG_FILE_PATH "log.txt"

void log_info(const char *, ...) {
    return;
}

void log_error(const char *, ...) {
    return;
}

void log_allocation_error() {
    return;
}

void log_monster(Monster) {
    return;
}

void log_monsters(MonstersList) {
    return;
}

void log_player(Player) {
    return;
}

void log_grimoire(Grimoire) {
    return;
}