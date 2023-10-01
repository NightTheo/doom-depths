
//
// Created by Theo OMNES on 01/10/2023.
//

#include "../port/in/continue_last_run.h"

#include "../port/out/persistence/game_state.h"
#include "../port/out/persistence/restore_last_game.h"


GameState continue_last_run() {
    return restore_last_game();
}