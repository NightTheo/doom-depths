
//
// Created by Theo OMNES on 26/09/2023.
//

#ifndef DOOMDEPTHS_SPELL_H
#define DOOMDEPTHS_SPELL_H

#include "stdint.h"
#include "stdbool.h"

typedef struct Player Player;
typedef struct Monster Monster;

typedef enum {PLAYER_SPELL_TARGET, MONSTER_SPELL_TARGET} SpellTarget;

typedef struct Spell Spell;
struct Spell {
    const char* name;
    SpellTarget target; // TODO target array for spell on multi targets ?
    uint16_t mana_consumption;
    Player (*cast_on_player) (Player);
    Monster (*cast_on_monster) (Monster);
};

/**
 * @param cast_on_player pointer of the function to call when the target is a PLAYER
 * @param cast_on_monster pointer of the function to call when the target is a MONSTER
 */
Spell spell(const char* name,
            uint16_t mana_consumption,
            SpellTarget target,
            Player (*cast_on_player)(Player),
            Monster (*cast_on_monster)(Monster));
Spell empty_spell();
bool spell_is_empty(Spell s);

#endif //DOOMDEPTHS_SPELL_H
