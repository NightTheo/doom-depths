
//
// Created by Theo OMNES on 26/09/2023.
//

#include <string.h>
#include "spell.h"

Spell spell(const char* name,
            uint16_t mana_consumption,
            SpellTarget target,
            Player (*cast_on_player)(Player),
            Monster (*cast_on_monster)(Monster)) {
    Spell s = {
            name,
            target,
            mana_consumption,
            cast_on_player,
            cast_on_monster,
    };
    return s;
}
Spell empty_spell() {
    Spell s = {
            "",
            -1,
            0,
            NULL,
            NULL,
    };
    return s;
}

bool spell_is_empty(Spell s) {
    return strcmp(s.name, "") == 0;
}

