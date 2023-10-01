
//
// Created by Theo OMNES on 13/09/2023.
//

#include <stdlib.h>
#include "../ihm.h"
#include "stdio.h"
#include "cli_ihm.h"
#include "../../application/port/out/persistence/restore_last_game.h"
#include "../../application/port/in/new_game.h"
#include "../../application/port/out/log/log_info.h"
#include "../../application/port/out/log/log_monster.h"
#include "../../application/port/out/log/log_error.h"

PlayerFightAction ask_player_fight_action(Player p) {
    display_fight_actions(p);
    int input = -1;
    // TODO better check input
    do {
        fflush(stdin);
        scanf("%d", &input);
    } while (input-1 < (p.remaining_number_of_attacks > 0 ? ATTACK : END_TURN) || input-1 > __player_fight_action_count - 1);
    log_info("player choose");
    log_info(player_fight_action_to_string(input - 1));
    return input-1;
}

void display_fight_actions(Player p) {
    for(PlayerFightAction action=ATTACK; action <= __player_fight_action_count - 1; action++) {
        if(action == ATTACK && p.remaining_number_of_attacks <= 0) continue;
        printf("%d. %s\n", action+1, player_fight_action_to_string(action));
    }
}

int8_t get_monster_index_to_attack(MonstersList monsters) {
    display_monsters(monsters);
    fprintf(stdout, "Select a monster to attack [1-%d]\n",monsters.size);
    int8_t input = 0;
    // TODO better check input
    do {
        fflush(stdin);
        scanf("%hhd", &input);
    } while (input < 1 || input > monsters.size);
    log_info("player choose monsters to attack");
    log_monster(monsters.monsters[input-1]);
    return input-1;
}

void display_monsters(MonstersList monsters) {
    for(int i = 0; i < monsters.size; i++) {
        char* s = monster_to_string(monsters.monsters[i]);
        fprintf(stdout, "%d. %s\n", i+1, s);
        free(s);
    }
}

void display_game_over() {
    fputs("\n GAME OVER\n", stdout);
}

void display_loot(Loot loot) {
    char* s = loot_to_string(loot);
    fprintf(stdout, "\nNew loot: \n%s\n", s);
    free(s);
}

const char* start_menu_action_to_string(StartMenuAction action) {
    char log[64];
    switch (action) {

        case NEW_GAME: return "New game";
        case RESTORE_LAST_GAME: return "Restore last game";
        default:
            sprintf(log, "Unknown action [%d]", action);
            log_error(log);
            return "Unknown action";
    }
}

GameState open_start_menu() {
    for(StartMenuAction a = 0; a < _start_menu_actions_count; a++) {
        fprintf(stdout, "%d. %s\n", a+1, start_menu_action_to_string(a));
    }
    int8_t input = -1;
    do {
        fflush(stdin);
        scanf("%hhd", &input);
    } while (input-1 < 0 || input-1 >= _start_menu_actions_count);

    switch ((StartMenuAction) (input-1)) {
        case NEW_GAME: return new_game();
        case RESTORE_LAST_GAME: return restore_last_game();
        default: {
            char log[64];
            sprintf(log, "Unknown choice [%d]", input);
            log_error(log);
            return new_game();
        }
    }
}