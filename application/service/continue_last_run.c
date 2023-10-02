
//
// Created by Theo OMNES on 01/10/2023.
//

#include "../port/in/continue_last_run.h"

#include "../port/out/persistence/intern_game_state/game_state.h"
#include "../port/out/persistence/storage/restore_last_game.h"
#include "../port/out/persistence/intern_game_state/set_intern_game_state.h"


GameState continue_last_run() {
    GameState last_run = restore_last_game();
    if (last_run.repository_status == SAVE_LAST_GAME_SUCCEEDED) {
        set_intern_game_state(last_run.game);
    }
    return last_run;
}