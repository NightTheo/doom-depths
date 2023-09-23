
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_LOG_H
#define DOOMDEPTHS_LOG_H
#include "../../player/player.h"
#include "../../monsters/monster.h"

void log_info(const char* msg_info);
void log_error(const char* msg_error);
void log_allocation_error();
void log_player(Player p);
void log_monster(Monster m);
void log_monsters(MonstersList m);

#endif //DOOMDEPTHS_LOG_H
