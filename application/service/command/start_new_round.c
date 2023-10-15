
//
// Created by Theo OMNES on 02/10/2023.
//

#include <port/in/command/start_new_round.h>
#include <domain/fight/fight.h>
#include <port/out/persistence/intern_game_state/set_current_fight.h>
#include <port/out/persistence/intern_game_state/get_current_fight.h>
#include "port/in/query/is_current_fight_finished.h"
#include "port/out/log/log_info.h"

void start_new_round() {
    if (current_fight_is_finished()) {
        log_info("fight is finished");
        return;
    }

    Fight fight = get_current_fight();
    fight.player = player_recover_mana(fight.player, 10);
    fight.player = restore_player_number_of_remaining_attacks(fight.player);
    fight.turn += 1;
    set_current_fight(fight);
}