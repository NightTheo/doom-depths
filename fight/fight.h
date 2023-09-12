
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_FIGHT_H
#define DOOMDEPTHS_FIGHT_H

#include "../monsters/monster.h"
#include "../player/player.h"

typedef struct AttackResult {
    Player player;
    Monster monster;
} AttackResult;


Monster monster_takes_damages(Monster m, int8_t damages);
AttackResult player_attacks_monster(Player p, Monster m);
#endif //DOOMDEPTHS_FIGHT_H
