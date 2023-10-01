
//
// Created by Theo OMNES on 01/10/2023.
//



#include "../../../application/port/out/persistence/intern_game_state/game_state.h"
#include "../../../application/port/out/persistence/intern_game_state/set_intern_game_state.h"
#include "../../../application/port/out/persistence/intern_game_state/get_intern_game_state.h"

GameState GAME_STATE = {DOOM_DEPTHS_EMPTY};

GameState set_intern_game_state(GameState game_state) {
    GAME_STATE = game_state;
}

GameState get_intern_game_state() {
    return GAME_STATE;
}
