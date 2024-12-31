
//
// Created by Theo OMNES on 01/10/2023.
//

#include <fight.h>

#include <port/in/command/cast_spell.h>

#include "log/log_info.h"
#include "log/log_error.h"
#include <port/out/persistence/intern_game_state/set_current_fight.h>
#include <../domain/fight/event/player_killed_monster.h>
#include <port/out/persistence/intern_game_state/get_current_fight.h>

void cast_spell_on_monster_in_fight(Fight f, Spell s);

void cast_spell_on_player_in_fight(Fight f, Spell s);

void cast_spell(Spell s) {
    Fight f = get_current_fight();
    if (spell_is_empty(s)) {
        log_info("Couln't get spell to cast.");
        return;
    }
    if (s.mana_consumption > f.player.current_mana) {
        log_info("Player current mana is too low to cast spell.");
        return;
    }    

    f.player.current_mana -= s.mana_consumption;

    switch (s.target) {
        case PLAYER_SPELL_TARGET:
            return cast_spell_on_player_in_fight(f, s);
        case MONSTER_SPELL_TARGET:
            return cast_spell_on_monster_in_fight(f, s);
        default: {
            log_error("Unknown target [%d]", s.target);
        }
    }
}

void cast_spell_on_player_in_fight(Fight f, Spell s) {
    f.player = s.cast_on_player(f.player);
    set_current_fight(f);
}


void cast_spell_on_monster_in_fight(Fight f, Spell s) {
    Monster monster_attacked = f.monsters_list.monsters[0];
    monster_attacked = s.cast_on_monster(monster_attacked);
    f.monsters_list.monsters[0] = monster_attacked;
    set_current_fight(f);

    if (monster_is_dead(monster_attacked)) {
        player_killed_monster(random_loot());
    }
}