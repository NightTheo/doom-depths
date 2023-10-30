
//
// Created by Theo OMNES on 01/10/2023.
//

#include "fight.h"

#include <port/in/command/attack_with_weapon.h>

#include <port/out/persistence/intern_game_state/set_current_fight.h>
#include <port/out/persistence/intern_game_state/get_current_fight.h>
#include <port/out/ihm/display_loot.h>
#include <event/player_killed_monster.h>
#include "port/in/query/is_current_fight_finished.h"
#include "log/log_info.h"
#include "log/log_error.h"


void attack_with_weapon() {
    if (current_fight_is_finished()) {
        log_error("fight is finished, cannot attack");
        return;
    }
    Fight fight = get_current_fight();
    AttackResult attackResult = player_attacks_monster(
            fight.player,
            fight.monsters_list.monsters[0]
    );
    fight.player = attackResult.player;
    fight.monsters_list.monsters[0] = attackResult.monster;
    set_current_fight(fight);

    if (monster_is_dead(fight.monsters_list.monsters[0])) {
        player_killed_monster(attackResult.loot);
    }
}