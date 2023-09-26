
//
// Created by Theo OMNES on 12/09/2023.
//

#include <stdio.h>
#include "fight.h"
#include "../../infrastructure/utils/random/random.h"
#include "../../infrastructure/utils/utils.h"
#include "../../infrastructure/utils/log/log.h"
#include "../../ihm/ihm.h"
#include "../repository.h"

Fight turn(Fight f);
Player decrement_player_remaining_attacks(Player p);
Fight player_makes_action(PlayerFightAction action, Fight f);

Fight start_fight(Fight f) {
    f.player.remaining_number_of_attacks = f.player.equipment.weapon.max_number_of_attacks_per_turn;
    while(player_is_alive(f.player)) {
        if(f.monsters_list.size <= 0) {
            f.monsters_list = random_list_of_monsters(random_between_included(2, 5));
        }
        f = turn(f);
        f.player = monsters_attack_player(f.monsters_list, f.player);
        f.player = restore_player_number_of_remaining_attacks(f.player);
        f.turn += 1;
    }

    display_game_over();
    return f;
}

Fight turn(Fight f) {
        char turn_log[16];sprintf(turn_log, "turn %d", f.turn);log_info(turn_log);

    while(f.monsters_list.size > 0) {
            log_player(f.player);
            log_monsters(f.monsters_list);
        PlayerFightAction action = ask_player_fight_action(f.player);
        if(action == END_TURN) break;
        f = player_makes_action(action, f);
        f.monsters_list = list_of_monster_without_dead_ones(f.monsters_list);
    }

    return f;
}

Fight player_makes_action(PlayerFightAction action, Fight f) {
    switch (action) {
        case END_TURN: return f;
        case ATTACK: {
            int8_t attacked_monster_index = get_monster_index_to_attack(f.monsters_list);
            AttackResult attackResult = player_attacks_monster(
                    f.player,
                    f.monsters_list.monsters[attacked_monster_index]
            );
            f.player = attackResult.player;
            f.monsters_list.monsters[attacked_monster_index] = attackResult.monster;
            display_loot(attackResult.loot);
            f.player.inventory = push_loot_in_inventory(f.player.inventory, attackResult.loot);
            break;
        }
        case SHOW_INVENTORY:
            f.player = enter_player_s_inventory(f.player);
            break;
        case SAVE_GAME:
            save_game_state((GameState) {f.turn, f.player, f.monsters_list});
            break;
        default:
            break;
    }
    return f;
}

Monster monster_takes_damages(Monster m, uint8_t damages) {
    int8_t damages_after_defense =  max(0, damages - m.defense);
    m.health = max(0, m.health - damages_after_defense);
    char log[64];
    sprintf(log, "Monster took %d damages", damages_after_defense);
    log_info(log);
    return m;
}

AttackResult player_attacks_monster(Player p, Monster m) {

    AttackResult res = {p,m, empty_loot()};
    if(p.remaining_number_of_attacks <= 0) {
        log_info("player has no remaining attack count");
        return res;
    }
    log_info("player attacks monsters");
    res.player = decrement_player_remaining_attacks(p);
    uint8_t damages = random_between_included(p.equipment.weapon.min_damages, p.equipment.weapon.max_damages);
    res.monster = monster_takes_damages(m, damages);
    if(monster_is_dead(res.monster)) res.loot = random_loot();
    return res;
}

Player decrement_player_remaining_attacks(Player p) {
    p.remaining_number_of_attacks = p.remaining_number_of_attacks > 0
            ? p.remaining_number_of_attacks - 1
            : 0;
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
    int8_t damages = random_between_included(m.min_attack_power, m.max_attack_power);
    char log[64]; snprintf(log, 64, "monsters attack player with %d damages.", damages);
    log_info(log);
    AttackResult res = {
            player_takes_damages(p, damages),
            m,
    };
    return res;
}

Player player_takes_damages(Player p, int8_t damages) {
    uint8_t defense = p.equipment.armor.defense;
    uint8_t damages_after_armor_defense = defense > damages ? 0 : damages - defense;
    uint8_t damages_taken = damages_after_armor_defense > p.current_health
            ? p.current_health
            : damages_after_armor_defense;
    p.current_health = p.current_health - damages_taken;

    char log[32];sprintf(log, "Player tooks %d damages", damages_taken);log_info(log);
    return p;
}