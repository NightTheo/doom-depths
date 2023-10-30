
//
// Created by Theo OMNES on 29/09/2023.
//

#include "doom_depths.h"
#include "stdbool.h"
#include "log/log_error.h"

DoomDepths empty_game();

DoomDepths new_doom_depths(Map map, Player p) {
    Position spawn = map.spawn;
    if (position_is_in_map_and_not_empty(spawn, map) == false) {
        log_error("Bad spawn.");
        free_map(map);
        free_player(p);
        return empty_game();
    }
    DoomDepths game;
    game.map = spawn_player_on_map_at_position(p, map, spawn);
    game.player = p;

    return game;
}

DoomDepths empty_game() {
    DoomDepths game;
    game.player = empty_player();
    game.map = empty_map();

    return game;
}

Fight get_current_fight_in_game(DoomDepths game) {
    return get_player_current_zone_in_map(game.map).fight;
}

DoomDepths set_current_zone_in_game(DoomDepths game, Zone zone) {
    Position p = game.map.spawn;
    game.map.zones[p.zone_y][p.zone_x] = zone;
    return game;
}

DoomDepths set_current_fight_in_game(DoomDepths game, Fight f) {
    Zone z = get_player_current_zone_in_map(game.map);
    z.fight = f;
    return set_current_zone_in_game(game, z);
}

void free_doom_depths(DoomDepths game) {
    free_player(game.player);
    free_map(game.map);
}

bool doom_depths_is_empty(DoomDepths game) {
    return player_is_empty(game.player) || map_is_empty(game.map);
}