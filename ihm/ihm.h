
//
// Created by Theo OMNES on 13/09/2023.
//

#ifndef DOOMDEPTHS_IHM_H
#define DOOMDEPTHS_IHM_H

#include "../domain/fight/player_fight_action/player_fight_actions.h"
#include "../domain/player/player.h"
#include "../domain/monsters/monsters.h"
#include "../domain/fight/loot/loot.h"
#include "../domain/repository.h"

typedef enum StartMenuAction {
    NEW_GAME,
    RESTORE_LAST_GAME,

    _start_menu_actions_count
} StartMenuAction;

PlayerFightAction ask_player_fight_action(Player p);
int8_t get_monster_index_to_attack(MonstersList monsters);
void display_game_over();
void display_loot(Loot loot);
Player enter_player_s_inventory(Player p);
GameState open_start_menu();

#endif //DOOMDEPTHS_IHM_H
