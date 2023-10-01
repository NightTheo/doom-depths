
//
// Created by Theo OMNES on 01/10/2023.
//


#include "../port/out/persistence/game_state.h"
#include "../../application/port/in/new_run.h"
#include "../port/out/ihm/leave_town_action.h"
#include "../port/out/ihm/display_map.h"

GameState new_run() {
    Map m = basic_map();
    GameState gameState;
    gameState.repository_status = REPOSITORY_NOT_USED;
    // TODO not enter map
    gameState.game = new_doom_depths(enter_map(m), m, player(100, 20));
    return gameState;
}