
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>

#include "../../../domain/fight/fight.h"

#include "../../port/in/command/cast_spell.h"

#include "../../port/out/log/log_info.h"
#include "../../port/out/log/log_error.h"
#include "../../port/out/persistence/intern_game_state/set_current_fight.h"
#include "../../../domain/fight/event/player_killed_monster.h"

Fight cast_spell_on_monster_in_fight(Fight f, Spell s);

Fight cast_spell_on_player_in_fight(Fight f, Spell s);

Fight cast_spell(Fight f, Spell s) {
    if (spell_is_empty(s)) {
        log_info("Couln't get spell to cast.");
        return f;
    }
    if (s.mana_consumption > f.player.current_mana) {
        log_info("Player current mana is too low to cast spell.");
        return f;
    }
    f.player.current_mana -= s.mana_consumption;

    switch (s.target) {
        case PLAYER_SPELL_TARGET:
            return cast_spell_on_player_in_fight(f, s);
        case MONSTER_SPELL_TARGET:
            return cast_spell_on_monster_in_fight(f, s);
        default: {
            char log[64];
            snprintf(log, 64, "Unknown target [%d]", s.target);
            log_error(log);
        }
    }
}

Fight cast_spell_on_player_in_fight(Fight f, Spell s) {
    f.player = s.cast_on_player(f.player);
    return set_current_fight(f);
}

// TODO struct CastSpellResult ? equivalent to AttackResult
Fight cast_spell_on_monster_in_fight(Fight f, Spell s) {
    Monster monster_attacked = f.monsters_list.monsters[0];
    monster_attacked = s.cast_on_monster(monster_attacked);
    if (monster_is_dead(monster_attacked)) {
        player_killed_monster(random_loot());
    }

    f.monsters_list.monsters[0] = monster_attacked;
    return set_current_fight(f);
}