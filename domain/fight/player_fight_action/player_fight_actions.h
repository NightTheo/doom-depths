
//
// Created by Theo OMNES on 13/09/2023.
//

#ifndef DOOMDEPTHS_PLAYER_FIGHT_ACTIONS_H
#define DOOMDEPTHS_PLAYER_FIGHT_ACTIONS_H

typedef enum PlayerFightAction {
    ATTACK = 0,
    OPEN_GRIMOIRE,
    SHOW_INVENTORY,
    END_TURN,
    SAVE_GAME,

    __player_fight_action_count
} PlayerFightAction;

const char *player_fight_action_to_string(PlayerFightAction action);

#endif //DOOMDEPTHS_PLAYER_FIGHT_ACTIONS_H
