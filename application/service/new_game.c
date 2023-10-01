
//
// Created by Theo OMNES on 01/10/2023.
//


#include "../port/out/persistence/game_state.h"
#include "../../application/port/in/new_game.h"
#include "../../ihm/ihm.h"

GameState new_game() {
    Map m = basic_map();
    GameState gameState;
    gameState.repository_status = REPOSITORY_NOT_USED;
    gameState.game = new_doom_depths(enter_map(m), m, player(100, 20));
    return gameState;
}