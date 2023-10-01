
//
// Created by Theo OMNES on 01/10/2023.
//

#include "../../domain/fight/fight.h"
#include "../port/in/end_round.h"

Fight end_round(Fight fight) {
    fight.player = monsters_attack_player(fight.monsters_list, fight.player);
    fight.player = player_recover_mana(fight.player, 10);
    fight.player = restore_player_number_of_remaining_attacks(fight.player);
    fight.turn += 1;
    
    return fight;
}