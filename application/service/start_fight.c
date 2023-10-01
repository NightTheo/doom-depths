
//
// Created by Theo OMNES on 01/10/2023.
//

#include "../port/in/start_fight.h"
#include "../../domain/doom_depths/doom_depths.h"
#include "../port/out/log/log_error.h"
#include "../port/in/end_round.h"

DoomDepths start_fight(DoomDepths game) {
    if (doom_depths_is_empty(game)) {
        log_error("Game is empty");
        return game;
    };
    Fight f = get_current_fight_in_game(game);
    f.player.remaining_number_of_attacks = f.player.equipment.weapon.max_number_of_attacks_per_turn;
    while (player_is_alive(f.player) && f.monsters_list.size > 0) {
        f = new_round(set_current_fight_in_game(game, f));
        f = end_round(f);
    }

    game.player = f.player;
    game = set_current_fight_in_game(game, f);
    Zone zone_finished = set_zone_status(
            get_zone_of_player_current_zone_in_map(game.map),
            ZONE_FINISHED
    );
    return set_current_zone_in_game(game, zone_finished);
}