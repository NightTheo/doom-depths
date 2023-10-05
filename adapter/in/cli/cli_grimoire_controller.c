
//
// Created by Theo OMNES on 27/09/2023.
//

#include <stdio.h>

#include <domain/fight/fight.h>

#include <application/port/in/command/cast_spell.h>

#include <application/port/out/log/log_info.h>

void display_grimoire(Grimoire g, uint16_t max_mana);

int16_t get_spell_index_to_cast_in_grimoire_or_exit(Grimoire g, uint16_t max_mana);

Spell get_spell_by_index(Grimoire g, int16_t index);


void open_grimoire_in_fight(Fight f) {
    Grimoire g = f.player.grimoire;
    display_grimoire(g, f.player.current_mana);
    uint16_t index = get_spell_index_to_cast_in_grimoire_or_exit(g, f.player.current_mana);

    bool exit_grimoire = index == g.number_of_spells;
    if (exit_grimoire) return;

    Spell s = get_spell_by_index(g, index);
    cast_spell(s);
}

void display_grimoire(Grimoire g, uint16_t max_mana) {
    log_info("Display grimoire.");

    for (int i = 0; i < g.number_of_spells; i++) {
        Spell s = g.spells[i];
        const char *to_display = s.mana_consumption <= max_mana
                                 ? "%d. %s [%dm]\n"
                                 : "%d. ~ %s ~ [%dm (not enough mana)]\n";
        fprintf(stdout, to_display, i + 1, s.name, s.mana_consumption);
    }
    fprintf(stdout, "%d. Exit grimoire\n", g.number_of_spells + 1);
}

int16_t get_spell_index_to_cast_in_grimoire_or_exit(Grimoire g, uint16_t max_mana) {
    int8_t input = -1;
    while (input < 1 || input > g.number_of_spells + 1) {
        fflush(stdin);
        scanf("%hhd", &input);
    }
    uint8_t index = input - 1;
    index < g.number_of_spells
    ? log_info("Spell index is [%d]", index)
    : log_info("Exit grimoire.");

    return index;
}

Spell get_spell_by_index(Grimoire g, int16_t index) {
    if (index < 0 || index >= g.number_of_spells) {
        log_info("Index [%d] is not in grimoire.", index);
        return empty_spell();
    }
    return g.spells[index];
}