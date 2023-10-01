
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include "stdbool.h"

#include "../../domain/fight/fight.h"

#include "../port/in/attack_with_weapon.h"

#include "../port/out/log/log_error.h"


// get_monster_index_to_attack(f.monsters_list)

Fight attack_with_weapon(Fight fight) {
    AttackResult attackResult = player_attacks_monster(
            fight.player,
            fight.monsters_list.monsters[0]
    );
    fight.player = attackResult.player;
    fight.monsters_list.monsters[0] = attackResult.monster;
    fight.player.inventory = push_loot_in_inventory(fight.player.inventory, attackResult.loot);
    return fight;
}