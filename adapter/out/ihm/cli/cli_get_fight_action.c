
//
// Created by Theo OMNES on 01/10/2023.
//



#include <stdio.h>

#include "../../../../domain/player/player.h"
#include "../../../../domain/fight/player_fight_action/player_fight_actions.h"

#include "../../../../application/port/out/log/log_info.h"
#include "../../../../application/port/out/ihm/get_fight_action.h"

void display_fight_actions(Player p);


PlayerFightAction ask_player_fight_action(Player p) {
    display_fight_actions(p);
    int input = -1;
    // TODO better check input
    do {
        fflush(stdin);
        scanf("%d", &input);
    } while (input <= (p.remaining_number_of_attacks > 0 ? ATTACK : END_TURN) || input >= __player_fight_action_count);
    log_info("player choose");
    log_info(player_fight_action_to_string(input - 1));
    return input - 1;
}

void display_fight_actions(Player p) {
    for (PlayerFightAction action = ATTACK; action <= __player_fight_action_count - 1; action++) {
        if (action == ATTACK && p.remaining_number_of_attacks <= 0) continue;
        printf("%d. %s\n", action + 1, player_fight_action_to_string(action));
    }
}