
//
// Created by Theo OMNES on 02/10/2023.
//

#include "../../port/in/query/is_current_round_finished.h"

#include "../../../domain/fight/fight.h"
#include "../../port/out/persistence/intern_game_state/get_current_fight.h"

bool current_round_is_finished() {
    Fight fight = get_current_fight();
    return fight.monsters_list.size <= 0;
}