
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>

#include "../../domain/fight/fight.h"

#include "../port/in/cast_spell.h"

#include "../port/out/log/log_info.h"
#include "../port/out/log/log_error.h"

Fight cast_spell_on_monster_in_fight(Fight f, Spell s);

Fight cast_spell_on_player_in_fight(Fight f, Spell s);

Fight cast_spell(Fight f, Spell s) {
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
            f.player.current_mana += s.mana_consumption; // reset mana if unknown target
            return f;
        }
    }
}

Fight cast_spell_on_player_in_fight(Fight f, Spell s) {
    f.player = s.cast_on_player(f.player);
    return f;
}

// TODO struct CastSpellResult ? equivalent to AttackResult
Fight cast_spell_on_monster_in_fight(Fight f, Spell s) {
    Monster monster_attacked = f.monsters_list.monsters[0];
    monster_attacked = s.cast_on_monster(monster_attacked);
    if (monster_is_dead(monster_attacked)) {
        Loot loot = random_loot();
        f.player.inventory = push_loot_in_inventory(f.player.inventory, loot);
    }

    f.monsters_list.monsters[0] = monster_attacked;
    return f;
}