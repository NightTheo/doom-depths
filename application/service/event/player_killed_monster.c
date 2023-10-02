
//
// Created by Theo OMNES on 02/10/2023.
//


#include "../../../domain/fight/loot/loot.h"
#include "../../../domain/fight/fight.h"
#include "../../../domain/fight/event/player_killed_monster.h"
#include "../../port/out/persistence/intern_game_state/get_current_fight.h"
#include "../../port/out/ihm/display_loot.h"

void player_killed_monster(Loot loot) {
    Fight fight = get_current_fight();
    fight.monsters_list = list_of_monster_without_dead_ones(fight.monsters_list);
    if (loot_is_not_empty(loot)) {
        display_loot(loot);
        fight.player.inventory = push_loot_in_inventory(fight.player.inventory, loot);
    }
}