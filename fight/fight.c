
//
// Created by Theo OMNES on 12/09/2023.
//

#include <stdio.h>
#include "fight.h"
#include "../utils/random/random.h"
#include "../utils/utils.h"
#include "../utils/log/log.h"
#include "../ihm/ihm.h"

Fight turn(Fight f);
Player decrement_player_remaining_attacks(Player p);
Fight player_makes_action(PlayerAction action, Fight f);

Fight start_fight(Fight f) {
    while(player_is_alive(f.player)) {
        if(f.monsters_list.size <= 0) {
            f.monsters_list = random_list_of_monsters(random_between_included(2, 5));
        }
        f = turn(f);
        f.player = monsters_attack_player(f.monsters_list, f.player);
        f.player = restore_player_number_of_remaining_attacks(f.player);
        f.turn += 1;
    }

    if(player_is_dead(f.player)) {
        display_game_over();
    }

    return f;
}

Fight turn(Fight f) {
        char turn_log[16];sprintf(turn_log, "turn %d", f.turn);log_info(turn_log);

    while(f.player.remaining_number_of_attacks > 0 && f.monsters_list.size > 0) {
            log_player(f.player);
            log_monsters(f.monsters_list);
        PlayerAction action = ask_player_action(f.player);
        if(action == END_TURN) break;
        f = player_makes_action(action, f);
        f.monsters_list = list_of_monster_without_dead_ones(f.monsters_list);
    }

    return f;
}

Fight player_makes_action(PlayerAction action, Fight f) {
    switch (action) {
        case END_TURN: return f;
        case ATTACK: {
            int8_t attacked_monster_index = ask_monster_index_to_attack(f.monsters_list);
            AttackResult attackResult = player_attacks_monster(
                    f.player,
                    f.monsters_list.monsters[attacked_monster_index]
            );
            f.player = attackResult.player;
            f.monsters_list.monsters[attacked_monster_index] = attackResult.monster;
            break;
        }
    }
    return f;
}

Monster monster_takes_damages(Monster m, int8_t damages) {
    int8_t damages_after_defense =  max(0, damages - m.defense);
    m.health = max(0, m.health - damages_after_defense);
    log_info("Monster tooks damages, is now:"); log_monster(m);
    return m;
}

AttackResult player_attacks_monster(Player p, Monster m) {
    log_info("player attacks monsters");
    AttackResult res = {p,m};
    if(p.remaining_number_of_attacks <= 0) return res;
    res.player = decrement_player_remaining_attacks(p);
    res.monster = monster_takes_damages(m, p.weapon.damages);
    return res;
}

Player decrement_player_remaining_attacks(Player p) {
    p.remaining_number_of_attacks = max(0, p.remaining_number_of_attacks - 1);
    return p;
}

Player monsters_attack_player(MonstersList monsters, Player p) {
    for(int i = 0; i < monsters.size; i++) {
        p = monster_attacks_player(monsters.monsters[i], p).player;
        if(player_is_dead(p)) return p;
    }
    return p;
}

AttackResult monster_attacks_player(Monster m, Player p) {
    log_info("monsters attack player");log_player(p);log_monster(m);
    int8_t damages = random_between_included(m.min_attack_power, m.max_attack_power);
    AttackResult res = {
            player_takes_damages(p, damages),
            m,
    };
    return res;
}

Player player_takes_damages(Player p, int8_t damages) {
    // TODO armor
    p.current_health = max(0, p.current_health - damages);
    log_info("Player tooks damages");
    return p;
}