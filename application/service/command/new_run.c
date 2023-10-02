
//
// Created by Theo OMNES on 01/10/2023.
//


#include "../../port/out/persistence/intern_game_state/game_state.h"
#include "../../port/in/command/new_run.h"
#include "../../port/out/persistence/intern_game_state/set_intern_game_state.h"

GameState new_run() {
    Map m = basic_map();
    GameState gameState;
    // TODO not enter map
    gameState.game = new_doom_depths(m, player(100, 20));

    set_intern_game_state(gameState.game);

    return gameState;
}