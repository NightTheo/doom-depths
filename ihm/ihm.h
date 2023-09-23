
//
// Created by Theo OMNES on 13/09/2023.
//

#ifndef DOOMDEPTHS_IHM_H
#define DOOMDEPTHS_IHM_H

#include "../player/player_action/player_actions.h"
#include "../player/player.h"
#include "../monsters/monsters.h"

PlayerAction ask_player_action(Player p);
int8_t ask_monster_index_to_attack(MonstersList monsters);
void display_game_over();
#endif //DOOMDEPTHS_IHM_H
