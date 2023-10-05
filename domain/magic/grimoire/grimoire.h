
//
// Created by Theo OMNES on 26/09/2023.
//

#ifndef DOOMDEPTHS_GRIMOIRE_H
#define DOOMDEPTHS_GRIMOIRE_H

#include <domain/magic/spell/spell.h>
#include "stdint.h"

typedef struct Grimoire {
    uint8_t number_of_spells;
    Spell spells[2];
} Grimoire;

Grimoire empty_grimoire();

Grimoire start_grimoire();

char *grimoire_to_string(Grimoire g);

#endif //DOOMDEPTHS_GRIMOIRE_H
