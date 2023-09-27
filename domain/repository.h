
//
// Created by Theo OMNES on 25/09/2023.
//

#ifndef DOOMDEPTHS_REPOSITORY_H
#define DOOMDEPTHS_REPOSITORY_H

#include "player/player.h"
#include "fight/fight.h"

typedef enum RepositoryStatus {
    REPOSITORY_NOT_USED,
    RESTORE_LAST_GAME_SUCCEEDED,
    RESTORE_LAST_GAME_FAILED,
    SAVE_LAST_GAME_SUCCEEDED,
    SAVE_LAST_GAME_FAILED,
} RepositoryStatus;

typedef struct GameState {
    RepositoryStatus repository_status;
    uint8_t turn;
    Player player;
    MonstersList monsters_list;
} GameState;

GameState restore_last_game();
RepositoryStatus save_game_state(GameState gameState);
const char* repository_status_to_string(RepositoryStatus status);
void log_repository_status(RepositoryStatus status);

#endif //DOOMDEPTHS_REPOSITORY_H
