
//
// Created by Theo OMNES on 01/10/2023.
//

#include "../../domain/fight/fight.h"
#include "../port/in/end_round.h"
#include "../port/out/persistence/intern_game_state/set_current_fight.h"
#include "../port/out/persistence/intern_game_state/get_current_fight.h"
#include "../port/in/query/is_current_fight_finished.h"

Fight end_round() {
    Fight fight = get_current_fight();
    if(current_fight_is_finished()) return fight;

    fight.player = monsters_attack_player(fight.monsters_list, fight.player);

    if(player_is_dead(fight.player)) return set_current_fight(fight);

    fight.player = player_recover_mana(fight.player, 10);
    fight.player = restore_player_number_of_remaining_attacks(fight.player);
    fight.turn += 1;

    return set_current_fight(fight);
}