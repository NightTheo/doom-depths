
//
// Created by Theo OMNES on 01/10/2023.
//

#include "../../domain/fight/fight.h"

#include "../port/in/attack_with_weapon.h"

#include "../port/out/persistence/intern_game_state/set_current_fight.h"
#include "../port/out/persistence/intern_game_state/get_current_fight.h"
#include "../port/out/ihm/display_loot.h"
#include "../../domain/fight/event/player_killed_monster.h"


Fight attack_with_weapon() {
    Fight fight = get_current_fight();
    AttackResult attackResult = player_attacks_monster(
            fight.player,
            fight.monsters_list.monsters[0]
    );
    fight.player = attackResult.player;
    fight.monsters_list.monsters[0] = attackResult.monster;
    if (monster_is_dead(fight.monsters_list.monsters[0])) {
        player_killed_monster(attackResult.loot);
    }

    return set_current_fight(fight);
}