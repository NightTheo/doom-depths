
//
// Created by Theo OMNES on 25/09/2023.
//

#ifndef DOOMDEPTHS_REPOSITORY_H
#define DOOMDEPTHS_REPOSITORY_H

#include "player/player.h"
#include "fight/fight.h"
#include "doom_detpths/doom_depths.h"

typedef enum RepositoryStatus {
    REPOSITORY_NOT_USED,
    RESTORE_LAST_GAME_SUCCEEDED,
    RESTORE_LAST_GAME_FAILED,
    SAVE_LAST_GAME_SUCCEEDED,
    SAVE_LAST_GAME_FAILED,
} RepositoryStatus;

const char* repository_status_to_string(RepositoryStatus status);
void log_repository_status(RepositoryStatus status);

typedef struct GameState {
    RepositoryStatus repository_status;
    DoomDepths game;
} GameState;

GameState restore_last_game();
RepositoryStatus save_game_state(GameState gameState);

#endif //DOOMDEPTHS_REPOSITORY_H
