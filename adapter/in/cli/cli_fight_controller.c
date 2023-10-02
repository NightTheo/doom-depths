
//
// Created by Theo OMNES on 01/10/2023.
//



#include <stdio.h>

#include "../../../domain/player/player.h"
#include "../../../domain/fight/player_fight_action/player_fight_actions.h"

#include "../../../application/port/out/log/log_info.h"
#include "../../../domain/doom_depths/doom_depths.h"
#include "../../../application/port/out/log/log_error.h"
#include "../../../application/port/in/query/is_current_fight_finished.h"
#include "../../../application/port/in/command/start_new_round.h"
#include "../../../application/port/out/persistence/intern_game_state/get_current_fight.h"
#include "../../../application/port/in/query/is_current_round_finished.h"
#include "../../../application/port/out/log/log_player.h"
#include "../../../application/port/out/log/log_grimoire.h"
#include "../../../application/port/out/log/log_monster.h"
#include "../../../application/port/in/command/end_round.h"
#include "../../../application/port/out/persistence/intern_game_state/get_intern_game_state.h"
#include "../../../application/port/in/command/attack_with_weapon.h"
#include "cli_controllers.h"
#include "../../../application/port/out/persistence/storage/respository_status.h"
#include "../../../application/port/out/log/log_repository_status.h"
#include "../../../application/port/out/persistence/storage/save_game_state.h"

void display_fight_actions(Player p);

Fight new_round();

PlayerFightAction ask_player_fight_action(Player p);

Fight player_makes_action(PlayerFightAction action);


Fight save_game_in_fight();

Fight enter_player_inventory_in_fight(Fight);


void fight(DoomDepths game) {
    if (doom_depths_is_empty(game)) {
        log_error("Game is empty");
        return;
    }
    while (current_fight_is_finished() == false) {
        start_new_round();
        new_round();
    }
}

Fight new_round() {
    Fight f = get_current_fight();
    char turn_log[16];
    sprintf(turn_log, "round %d", f.turn);
    log_info(turn_log);

    while (current_round_is_finished() == false) {

        f = get_current_fight();

        log_player(f.player);
        log_grimoire(f.player.grimoire);
        log_monsters(f.monsters_list);

        PlayerFightAction action = ask_player_fight_action(f.player);
        if (action == END_ROUND) {
            end_round();
            break;
        }
        f = player_makes_action(action);
    }

    return f;
}


PlayerFightAction ask_player_fight_action(Player p) {
    display_fight_actions(p);
    int input = -1;
    // TODO better check input
    do {
        fflush(stdin);
        scanf("%d", &input);
    } while (input <= (p.remaining_number_of_attacks > 0 ? ATTACK : END_ROUND) || input >= __player_fight_action_count);

    char log[32];
    snprintf(log, 32, "Player choose action [%s]", player_fight_action_to_string(input - 1));
    log_info(log);

    return input - 1;
}

void display_fight_actions(Player p) {
    for (PlayerFightAction action = ATTACK; action <= __player_fight_action_count - 1; action++) {
        if (action == ATTACK && p.remaining_number_of_attacks <= 0) continue;
        printf("%d. %s\n", action + 1, player_fight_action_to_string(action));
    }
}

Fight player_makes_action(PlayerFightAction action) {
    Fight f = get_current_fight_in_game(get_intern_game_state());
    switch (action) {
        case ATTACK:
            return attack_with_weapon();
        case OPEN_GRIMOIRE:
            return open_grimoire_in_fight(f);
        case SHOW_INVENTORY:
            return enter_player_inventory_in_fight(f);
        case SAVE_GAME:
            return save_game_in_fight();
        default: {
            char log[32];
            snprintf(log, 32, "Invalid FightAction [%d].", action);
            log_error(log);
            break;
        }

    }
    return f;
}

Fight enter_player_inventory_in_fight(Fight f) {
    f.player = enter_player_inventory(f.player);
    return f;
}

Fight save_game_in_fight() {
    DoomDepths current_state = get_intern_game_state();
    RepositoryStatus status = save_game_state(current_state);
    log_repository_status(status);
    return get_current_fight_in_game(current_state);
}