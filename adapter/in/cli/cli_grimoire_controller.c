
//
// Created by Theo OMNES on 27/09/2023.
//

#include <stdio.h>

#include "../../../domain/fight/fight.h"

#include "../../../application/port/in/command/cast_spell.h"

#include "../../../application/port/out/log/log_info.h"

void display_grimoire(Grimoire g);

int16_t get_spell_index_to_cast_in_grimoire(Grimoire g, uint16_t max_mana);

Spell get_spell_by_index(Grimoire g, int16_t index);


void open_grimoire_in_fight(Fight f) {
    Spell s = get_spell_by_index(
            f.player.grimoire,
            get_spell_index_to_cast_in_grimoire(f.player.grimoire, f.player.current_mana)
    );
    cast_spell(s);
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
    log_info("Spell index is [%d]", input - 1);
    return input - 1;
}

Spell get_spell_by_index(Grimoire g, int16_t index) {
    if (index < 0 || index >= g.number_of_spells) {
        log_info("Index [%d] is not in grimoire.", index);
        return empty_spell();
    }
    return g.spells[index];
}