
//
// Created by Theo OMNES on 01/10/2023.
//


#include <zone/zone.h>

#include <port/out/persistence/intern_game_state/game_state.h>
#include <port/out/persistence/intern_game_state/set_intern_game_state.h>
#include <port/out/persistence/intern_game_state/get_intern_game_state.h>
#include <port/out/persistence/intern_game_state/get_map.h>
#include <port/out/persistence/intern_game_state/get_current_fight.h>
#include <port/out/persistence/intern_game_state/set_player.h>
#include <port/out/persistence/intern_game_state/get_player.h>

DoomDepths GAME_STATE = {DOOM_DEPTHS_EMPTY};

DoomDepths set_intern_game_state(DoomDepths game_state) {
    GAME_STATE = game_state;
    return GAME_STATE;
}

DoomDepths get_intern_game_state() {
    return GAME_STATE;
}

Map get_map() {
    return GAME_STATE.map;
}

Map set_current_map(Map map) {
    GAME_STATE.map = map;
    return map;
}

Fight set_current_fight(Fight fight) {
    set_current_fight_in_game(get_intern_game_state(), fight);
    return fight;
}

Fight get_current_fight() {
    return get_current_fight_in_game(get_intern_game_state());
}

Player set_player(Player player) {
    Fight fight = get_current_fight();
    fight.player = player;
    set_current_fight(fight);
    return player;
}

Player get_player() {
    return get_current_fight().player;
}