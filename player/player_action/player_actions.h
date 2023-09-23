
//
// Created by Theo OMNES on 13/09/2023.
//

#ifndef DOOMDEPTHS_PLAYER_ACTIONS_H
#define DOOMDEPTHS_PLAYER_ACTIONS_H

typedef enum PlayerAction{
    ATTACK = 0,
    END_TURN,
} PlayerAction;

const char* player_action_to_string(PlayerAction action);

#endif //DOOMDEPTHS_PLAYER_ACTIONS_H
