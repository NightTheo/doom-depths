
//
// Created by Theo OMNES on 26/09/2023.
//

#ifndef DOOMDEPTHS_SPELL_H
#define DOOMDEPTHS_SPELL_H

#include "stdint.h"
#include "../../player/player.h"

typedef struct Spell {
    const char* name;
    uint16_t mana_consumption;
    uint16_t damages;
    Player (*cast_on_player)(Player p);
};

#endif //DOOMDEPTHS_SPELL_H
