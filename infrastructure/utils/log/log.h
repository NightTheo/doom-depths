
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_LOG_H
#define DOOMDEPTHS_LOG_H
#include "../../../domain/player/player.h"
#include "../../../domain/monsters/monsters.h"
#include "../../../domain/magic/grimoire/grimoire.h"
#include "../time/time_util.h"
#include "../../repository/game_state.h"

#define LOG_INFO_FORMAT "[%s][info] %s\n" // [time][info] msg
#define LOG_ERROR_FORMAT "[%s][error] %s\n" // [time][error] msg

void log_info(const char* msg_info);
void log_error(const char* msg_error);
void log_allocation_error();
void log_player(Player p);
void log_monster(Monster m);
void log_monsters(MonstersList m);
void log_grimoire(Grimoire g);
void log_repository_status(RepositoryStatus status);

#endif //DOOMDEPTHS_LOG_H
