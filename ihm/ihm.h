
//
// Created by Theo OMNES on 13/09/2023.
//

#ifndef DOOMDEPTHS_IHM_H
#define DOOMDEPTHS_IHM_H

#include "../fight/player_fight_action/player_fight_actions.h"
#include "../player/player.h"
#include "../monsters/monsters.h"
#include "../fight/loot/loot.h"

PlayerFightAction ask_player_fight_action(Player p);
int8_t get_monster_index_to_attack(MonstersList monsters);
void display_game_over();
void display_loot(Loot loot);
Player enter_player_s_inventory(Player p);

#endif //DOOMDEPTHS_IHM_H
