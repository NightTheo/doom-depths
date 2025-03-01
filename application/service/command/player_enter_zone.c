
//
// Created by Theo OMNES on 01/10/2023.
//

#include <port/out/persistence/intern_game_state/game_state.h>
#include <port/in/command/player_enter_zone.h>
#include <port/out/persistence/intern_game_state/get_intern_game_state.h>
#include <port/out/persistence/intern_game_state/set_intern_game_state.h>
#include "log/log_info.h"

void player_enter_zone(Position position) {
    DoomDepths game = get_intern_game_state();

    if (!player_can_move_to_position_in_map(position, game.map)) return;

    Fight old_fight = get_current_fight_in_game(game);
    Player player = old_fight.player;
    if (player_is_empty(player)) free_player(player);

    game.map = spawn_player_on_map_at_position(player, game.map, position);

    set_intern_game_state(game);

    log_position(position);
}