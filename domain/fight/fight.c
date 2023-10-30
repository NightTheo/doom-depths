
//
// Created by Theo OMNES on 12/09/2023.
//

#include <stdio.h>

#include "fight.h"

#include "random/random.h"
#include "utils.h"
#include "log/log_info.h"
#include "log/log_monster.h"

Player decrement_player_remaining_attacks(Player p);

void cast_spell_on_player_in_fight(Fight f, Spell s);

void cast_spell_on_monster_in_fight(Fight f, Spell s);

Fight empty_fight() {
    Fight f;
    f.turn = 0;
    f.monsters_list = empty_monster_list();
    f.player = empty_player();
    return f;
}

Monster monster_takes_damages(Monster m, uint8_t damages) {
    int8_t damages_after_defense = max(0, damages - m.defense);
    m.health = max(0, m.health - damages_after_defense);
    log_info("Monster took %d damages", damages_after_defense);
    return m;
}

AttackResult player_attacks_monster(Player p, Monster m) {
    AttackResult res = {p, m, empty_loot()};
    if (monster_is_dead(m)) {
        log_info("Monster already dead.");
        return res;
    }
    if (p.remaining_number_of_attacks <= 0) {
        log_info("player has no remaining attack count");
        return res;
    }
    log_info("player attacks monsters");
    res.player = decrement_player_remaining_attacks(p);
    uint8_t damages = random_between_included(p.equipment.weapon.min_damages, p.equipment.weapon.max_damages);
    res.monster = monster_takes_damages(m, damages);
    if (monster_is_dead(res.monster)) {
        res.loot = random_loot();
    }
    log_info("Monster health is now : %d", res.monster.health);
    return res;
}

Player decrement_player_remaining_attacks(Player p) {
    p.remaining_number_of_attacks = p.remaining_number_of_attacks > 0
                                    ? p.remaining_number_of_attacks - 1
                                    : 0;
    return p;
}

Player monsters_attack_player(MonstersList monsters, Player p) {
    for (int i = 0; i < monsters.size; i++) {
        p = monster_attacks_player(monsters.monsters[i], p).player;
        if (player_is_dead(p)) return p;
    }
    return p;
}

AttackResult monster_attacks_player(Monster m, Player p) {
    int8_t damages = random_between_included(m.min_attack_power, m.max_attack_power);
    log_info("monsters attack sdl_player with %d damages.", damages);
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

    log_info("Player tooks %d damages", damages_taken);
    return p;
}

Fight free_fight(Fight fight) {
    fight.player = free_player(fight.player);
    fight.monsters_list = free_monsters_list(fight.monsters_list);
    return fight;
}
