
//
// Created by Theo OMNES on 26/09/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "grimoire.h"

#include "../../player/player.h"
#include "../../monsters/monsters.h"

#include "../../../infrastructure/utils/utils.h"
#include "../../../application/port/out/log/log_info.h"

#define GRIMOIRE_STRING_SIZE 1024

// -- Spells
Monster _fire(Monster m);

Player _heal(Player);
// --

Grimoire empty_grimoire() {
    Grimoire g = {0, {}};
    return g;
}

Grimoire start_grimoire() {
    Spell fire = spell("fire", 10, MONSTER_SPELL_TARGET, NULL, _fire);
    Spell heal = spell("heal", 9, PLAYER_SPELL_TARGET, _heal, NULL);

    Grimoire g = {
            2,
            {fire, heal},
    };
    return g;
}


Monster _fire(Monster m) {
    log_info("Casting Fire");
    uint8_t damages = 10;
    m.health = damages > m.health ? 0 : m.health - damages;

    log_info("Monster took %d damages", damages);

    return m;
}

Player _heal(Player p) {
    log_info("Casting Heal");
    uint8_t heal = 15;
    p.current_health = min(p.max_health, p.current_health + heal);
    return p;
}

char *grimoire_to_string(Grimoire g) {
    char *s = malloc(GRIMOIRE_STRING_SIZE);
    snprintf(s, GRIMOIRE_STRING_SIZE,
             "Grimoire {number_of_spells: %d, spells: [%s, %s]}",
             g.number_of_spells,
             g.spells[0].name, g.spells[1].name);
    return s;
}