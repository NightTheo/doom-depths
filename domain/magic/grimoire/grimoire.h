
//
// Created by Theo OMNES on 26/09/2023.
//

#ifndef DOOMDEPTHS_GRIMOIRE_H
#define DOOMDEPTHS_GRIMOIRE_H

#include "../spell/spell.h"
#include "stdint.h"

typedef struct Grimoire {
    uint8_t number_of_spells;
    Spell spells[2];
} Grimoire;

Grimoire empty_grimoire();
Grimoire start_grimoire();
char* grimoire_to_string(Grimoire g);
Spell get_spell_by_index(Grimoire g, uint8_t index);

#endif //DOOMDEPTHS_GRIMOIRE_H
