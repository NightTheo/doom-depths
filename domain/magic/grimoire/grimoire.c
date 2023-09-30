
//
// Created by Theo OMNES on 26/09/2023.
//

#include <stdio.h>
#include "grimoire.h"
#include "../../../infrastructure/utils/utils.h"
#include "../../../infrastructure/utils/log/log.h"

#define GRIMOIRE_STRING_SIZE 1024

// -- Spells
Monster _fire(Monster m);
Player _heal(Player);
// --

Grimoire empty_grimoire() {
    Grimoire g = {0,{}};
    return g;
}

Grimoire start_grimoire() {
    Spell fire = spell("fire", 10, MONSTER_SPELL_TARGET, NULL, _fire);
    Spell heal = spell("heal", 9, PLAYER_SPELL_TARGET,_heal, NULL);

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

    char log[32];
    snprintf(log, 32, "Monster took %d damages", damages);
    log_info(log);

    return m;
}

Player _heal(Player p) {
    log_info("Casting Heal");
    uint8_t heal = 15;
    p.current_health = min(p.max_health, p.current_health + heal);
    return p;
}

char* grimoire_to_string(Grimoire g) {
    char* s = malloc(GRIMOIRE_STRING_SIZE);
    snprintf(s, GRIMOIRE_STRING_SIZE,
             "Grimoire {number_of_spells: %d, spells: [%s, %s]}",
             g.number_of_spells,
             g.spells[0].name, g.spells[1].name);
    return s;
}

Spell get_spell_by_index(Grimoire g, int16_t index) {
    if(index < 0 || index >= g.number_of_spells) {
        char log[32];
        snprintf(log, 32, "Index [%d] is not in grimoire.", index);
        log_info(log);
        return empty_spell();
    }
    return g.spells[index];
}