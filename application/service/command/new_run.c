
//
// Created by Theo OMNES on 01/10/2023.
//


#include <port/out/persistence/intern_game_state/game_state.h>
#include <port/in/command/new_run.h>
#include <port/out/persistence/intern_game_state/set_intern_game_state.h>

void new_run() {
    Map m = basic_map();
    GameState gameState;
    gameState.game = new_doom_depths(m, player(100, 20));
    set_intern_game_state(gameState.game);
}