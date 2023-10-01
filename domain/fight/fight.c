
//
// Created by Theo OMNES on 12/09/2023.
//

#include <stdio.h>

#include "fight.h"
#include "player_fight_action/player_fight_actions.h"

#include "../../infrastructure/utils/random/random.h"
#include "../../infrastructure/utils/utils.h"
#include "../../application/port/out/persistence/save_game_state.h"
#include "../../application/port/out/log/log_info.h"
#include "../../application/port/out/log/log_player.h"
#include "../../application/port/out/log/log_grimoire.h"
#include "../../application/port/out/log/log_monster.h"
#include "../../application/port/out/log/log_repository_status.h"
#include "../../application/port/out/log/log_error.h"
#include "../../application/port/out/ihm/display_loot.h"
#include "../../application/port/out/ihm/display_player_inventory.h"
#include "../../application/port/out/ihm/display_grimoire.h"
#include "../../application/port/out/ihm/get_monster_to_attack.h"
#include "../../application/port/out/ihm/get_fight_action.h"

Fight turn(DoomDepths game);

Player decrement_player_remaining_attacks(Player p);

Fight player_makes_action(PlayerFightAction action, DoomDepths game);

Fight cast_spell_on_player_in_fight(Fight f, Spell s);

Fight cast_spell_on_monster_in_fight(Fight f, Spell s);

Fight player_attacks_monster_in_fight(Fight f);

Fight enter_player_s_inventory_in_fight(Fight f);

Fight save_game_in_fight(DoomDepths game);

Fight empty_fight() {
    Fight f;
    f.turn = 0;
    f.monsters_list = empty_monster_list();
    f.player = empty_player();
    return f;
}

Fight turn(DoomDepths game) {
    Fight f = get_current_fight_in_game(game);
    char turn_log[16];
    sprintf(turn_log, "turn %d", f.turn);
    log_info(turn_log);

    while (f.monsters_list.size > 0) {
        log_player(f.player);
        log_grimoire(f.player.grimoire);
        log_monsters(f.monsters_list);
        game = set_current_fight_in_game(game, f);
        PlayerFightAction action = ask_player_fight_action(f.player);
        if (action == END_TURN) break;
        f = player_makes_action(action, game);
        f.monsters_list = list_of_monster_without_dead_ones(f.monsters_list);
    }

    return f;
}

Fight player_makes_action(PlayerFightAction action, DoomDepths game) {
    Fight f = get_current_fight_in_game(game);
    switch (action) {
        case END_TURN:
            return f;
        case ATTACK:
            return player_attacks_monster_in_fight(f);
        case OPEN_GRIMOIRE:
            return open_grimoire_in_fight(f);
        case SHOW_INVENTORY:
            return enter_player_s_inventory_in_fight(f);
        case SAVE_GAME:
            return save_game_in_fight(game);
        default:
            break;
    }
    return f;
}

Fight player_attacks_monster_in_fight(Fight f) {
    int8_t attacked_monster_index = get_monster_index_to_attack(f.monsters_list);
    AttackResult attackResult = player_attacks_monster(
            f.player,
            f.monsters_list.monsters[attacked_monster_index]
    );
    f.player = attackResult.player;
    f.monsters_list.monsters[attacked_monster_index] = attackResult.monster;
    f.player.inventory = push_loot_in_inventory(f.player.inventory, attackResult.loot);
    return f;
}

Fight enter_player_s_inventory_in_fight(Fight f) {
    f.player = display_player_inventory(f.player);
    return f;
}

Fight save_game_in_fight(DoomDepths game) {
    RepositoryStatus status = save_game_state((GameState) {REPOSITORY_NOT_USED, game});
    log_repository_status(status);
    return get_current_fight_in_game(game);
}

Monster monster_takes_damages(Monster m, uint8_t damages) {
    int8_t damages_after_defense = max(0, damages - m.defense);
    m.health = max(0, m.health - damages_after_defense);
    char log[64];
    sprintf(log, "Monster took %d damages", damages_after_defense);
    log_info(log);
    return m;
}

AttackResult player_attacks_monster(Player p, Monster m) {

    AttackResult res = {p, m, empty_loot()};
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
        display_loot(res.loot);
    }
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
    char log[64];
    snprintf(log, 64, "monsters attack player with %d damages.", damages);
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

    char log[32];
    sprintf(log, "Player tooks %d damages", damages_taken);
    log_info(log);
    return p;
}

Fight cast_spell_in_fight(Fight f, Spell s) {
    if (s.mana_consumption > f.player.current_mana) {
        log_info("Player current mana is too low to cast spell.");
        return f;
    }
    f.player.current_mana = f.player.current_mana - s.mana_consumption;

    char log[64];
    switch (s.target) {
        case PLAYER_SPELL_TARGET:
            return cast_spell_on_player_in_fight(f, s);
        case MONSTER_SPELL_TARGET:
            return cast_spell_on_monster_in_fight(f, s);
        default:
            snprintf(log, 64, "Unknown target [%d]", s.target);
            log_error(log);
            return f;
    }
}

Fight cast_spell_on_player_in_fight(Fight f, Spell s) {
    f.player = s.cast_on_player(f.player);
    return f;
}

// TODO struct CastSpellResult ? equivalent to AttackResult
Fight cast_spell_on_monster_in_fight(Fight f, Spell s) {
    uint8_t monster_index = get_monster_index_to_attack(f.monsters_list);
    Monster monster_attacked = f.monsters_list.monsters[monster_index];
    monster_attacked = s.cast_on_monster(monster_attacked);
    if (monster_is_dead(monster_attacked)) {
        Loot loot = random_loot();
        f.player.inventory = push_loot_in_inventory(f.player.inventory, loot);
    }

    f.monsters_list.monsters[monster_index] = monster_attacked;
    return f;
}

Fight free_fight(Fight fight) {
    fight.player = free_player(fight.player);
    fight.monsters_list = free_monsters_list(fight.monsters_list);
    return fight;
}

Fight init_new_fight(Player p, MonstersList m) {
    Fight f;
    f.player = p;
    f.turn = 1;
    f.monsters_list = m;
    return f;
}