
//
// Created by Theo OMNES on 02/10/2023.
//

#include <domain/doom_depths/doom_depths.h>
#include <port/out/persistence/intern_game_state/get_intern_game_state.h>
#include "port/out/log/log_info.h"

bool current_fight_is_finished() {
    Fight f = get_current_fight_in_game(get_intern_game_state());
    return !player_is_alive(f.player) || f.monsters_list.size <= 0;
}