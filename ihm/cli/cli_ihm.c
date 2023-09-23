
//
// Created by Theo OMNES on 13/09/2023.
//

#include <stdlib.h>
#include "../ihm.h"
#include "stdio.h"
#include "cli_ihm.h"
#include "../../utils/log/log.h"

PlayerAction ask_player_action(Player p) {
    display_menu(p);
    int input = -1;
    // TODO better check input
    do {
        fflush(stdin);
        scanf("%d", &input);
    } while (input-1 < (p.remaining_number_of_attacks > 0 ? ATTACK : END_TURN) || input-1 > END_TURN);
    log_info("player choose");
    log_info(player_action_to_string(input-1));
    return input-1;
}

void display_menu(Player p) {
    int8_t curent_index = 1;
    for(PlayerAction action=ATTACK; action <= END_TURN; action++) {
        if(action == ATTACK && p.remaining_number_of_attacks <= 0) break;
        printf("%d. %s\n", curent_index, player_action_to_string(action));
        curent_index += 1;
    }
}

int8_t ask_monster_index_to_attack(MonstersList monsters) {
    // TODO mask dead monsters
    display_monsters(monsters);
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
    printf("monsters 1, 2, 3 with their health\n");
}

void display_game_over() {
    fputs("\n GAME OVER\n", stdout);
}

void display_loot(Loot loot) {
    char* s = loot_to_string(loot);
    fprintf(stdout, "\nVous avez obtenu :\n%s\n", s);
    free(s);
}