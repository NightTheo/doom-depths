
//
// Created by Theo OMNES on 30/09/2023.
//

#ifndef DOOMDEPTHS_GAME_STATE_H
#define DOOMDEPTHS_GAME_STATE_H

#include "../../../../domain/doom_depths/doom_depths.h"
#include "respository_status.h"


typedef struct GameState GameState;
struct GameState {
    RepositoryStatus repository_status;
    DoomDepths game;
};

#endif //DOOMDEPTHS_GAME_STATE_H
