
//
// Created by Theo OMNES on 13/09/2023.
//

#include <stdlib.h>
#include "../ihm.h"
#include "stdio.h"
#include "cli_ihm.h"
#include "../../utils/log/log.h"
#include "inventory_cli/inventory_cli.h"

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