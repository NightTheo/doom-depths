
//
// Created by Theo OMNES on 01/10/2023.
//



#include <stdio.h>

#include <player.h>
#include <player_fight_action/player_fight_actions.h>

#include <doom_depths.h>
#include "cli_controllers.h"

#include "log/log_info.h"
#include "log/log_error.h"
#include <port/in/query/is_current_fight_finished.h>
#include <port/in/command/start_new_round.h>
#include <port/out/persistence/intern_game_state/get_current_fight.h>
#include <port/in/query/is_current_round_finished.h>
#include "log/log_player.h"
#include "log/log_grimoire.h"
#include "log/log_monster.h"
#include <port/in/command/end_round.h>
#include <port/out/persistence/intern_game_state/get_intern_game_state.h>
#include <port/in/command/attack_with_weapon.h>
#include <port/out/persistence/storage/respository_status.h>
#include "log/log_repository_status.h"
#include <port/out/persistence/storage/save_game_state.h>

void display_fight_actions(Player p);

void display_round();

PlayerFightAction ask_player_fight_action(Player p);

void player_makes_action(PlayerFightAction action);


void save_game_in_fight();


void fight() {
    DoomDepths game = get_intern_game_state();
    if (doom_depths_is_empty(game)) {
        log_error("Game is empty");
        // TODO set intern state to KO !
        return;
    }
    while (!current_fight_is_finished()) {
        start_new_round();
        display_round();
    }
}

void display_round() {
    Fight f = get_current_fight();
    log_info("round %d", f.turn);

    while (!current_round_is_finished()) {
        f = get_current_fight();
        log_player(f.player);
        log_grimoire(f.player.grimoire);
        log_monsters(f.monsters_list);

        PlayerFightAction action = ask_player_fight_action(f.player);
        if (action == END_ROUND) {
            end_round();
            break;
        }
        player_makes_action(action);
    }
}


PlayerFightAction ask_player_fight_action(Player p) {
    display_fight_actions(p);
    int input = -1;
    // TODO better check input
    do {
        fflush(stdin);
        scanf("%d", &input);
    } while (input <= (p.remaining_number_of_attacks > 0 ? ATTACK : END_ROUND) || input > __player_fight_action_count);

    log_info("Player choose action [%s]", player_fight_action_to_string(input - 1));

    return input - 1;
}

void display_fight_actions(Player p) {
    for (PlayerFightAction action = ATTACK; action <= __player_fight_action_count - 1; action++) {
        if (action == ATTACK && p.remaining_number_of_attacks <= 0) continue;
        printf("%d. %s\n", action + 1, player_fight_action_to_string(action));
    }
}

void player_makes_action(PlayerFightAction action) {
    Fight f = get_current_fight_in_game(get_intern_game_state());
    switch (action) {
        case ATTACK:
            return attack_with_weapon();
        case OPEN_GRIMOIRE:
            return open_grimoire_in_fight(f);
        case SHOW_INVENTORY:
            return enter_player_inventory(f.player);
        case SAVE_GAME:
            return save_game_in_fight();
        default: {
            log_error("Invalid FightAction [%d].", action);
            return;
        }

    }
}


void save_game_in_fight() {
    DoomDepths current_state = get_intern_game_state();
    RepositoryStatus status = save_game_state(current_state);
}