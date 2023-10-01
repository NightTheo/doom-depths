
//
// Created by Theo OMNES on 27/09/2023.
//

#include <stdio.h>

#include "../../../../domain/fight/fight.h"

#include "../../../../application/port/in/cast_spell.h"

#include "../../../../application/port/out/log/log_info.h"

void display_grimoire(Grimoire g);

int16_t get_spell_index_to_cast_in_grimoire(Grimoire g, uint16_t max_mana);

Fight open_grimoire_in_fight(Fight f) {
    Spell s = get_spell_by_index(f.player.grimoire, get_spell_index_to_cast_in_grimoire(f.player.grimoire,
                                                                                        f.player.current_mana));
    if (spell_is_empty(s)) {
        log_info("Couln't get spell to cast.");
        return f;
    }
    f = cast_spell(f, s);
    return f;
}

void display_grimoire(Grimoire g) {
    log_info("Display grimoire.");
    char *grimoire_str = grimoire_to_string(g);
    fprintf(stdout, "%s\n", grimoire_str);
    free(grimoire_str);
}

int16_t get_spell_index_to_cast_in_grimoire(Grimoire g, uint16_t max_mana) {
    display_grimoire(g);
    uint8_t count_castable_spells = 0;
    for (int i = 0; i < g.number_of_spells; i++) {
        Spell s = g.spells[i];
        if (s.mana_consumption > max_mana) continue;
        fprintf(stdout, "%d. %s [%dm]\n", i + 1, s.name, s.mana_consumption);
        count_castable_spells += 1;
    }
    if (count_castable_spells == 0) return -1;

    int8_t input = -1;
    while (input < 1 || input > g.number_of_spells) {
        fflush(stdin);
        scanf("%hhd", &input);
    }
    char log[32];
    snprintf(log, 32, "Spell index is [%d]", input - 1);
    log_info(log);
    return input - 1;
}

