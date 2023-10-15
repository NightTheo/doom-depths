
//
// Created by Theo OMNES on 01/10/2023.
//

#include <domain/fight/fight.h>
#include <port/in/command/end_round.h>
#include <port/out/persistence/intern_game_state/set_current_fight.h>
#include <port/out/persistence/intern_game_state/get_current_fight.h>
#include <port/in/query/is_current_fight_finished.h>
#include "port/out/log/log_info.h"

void end_round() {
    Fight fight = get_current_fight();
    if (current_fight_is_finished()) {
        log_info("fight is finished");
        return;
    }

    fight.player = monsters_attack_player(fight.monsters_list, fight.player);
    set_current_fight(fight);
}