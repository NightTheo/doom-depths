
//
// Created by Theo OMNES on 25/09/2023.
//

#ifndef DOOMDEPTHS_REPOSITORY_H
#define DOOMDEPTHS_REPOSITORY_H

#include "player/player.h"
#include "fight/fight.h"

typedef struct GameState {
    uint8_t turn;
    Player player;
    MonstersList monsters_list;
} GameState;

GameState restore_last_game();
bool save_game_state(GameState gameState);

#endif //DOOMDEPTHS_REPOSITORY_H
