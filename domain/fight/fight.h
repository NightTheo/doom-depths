
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_FIGHT_H
#define DOOMDEPTHS_FIGHT_H

#include "../monsters/monsters.h"
#include "../player/player.h"
#include "loot/loot.h"

typedef struct DoomDepths DoomDepths;

typedef struct Fight {
    int8_t turn;
    Player player;
    MonstersList monsters_list;
} Fight;

typedef struct AttackResult {
    Player player;
    Monster monster;
    Loot loot;
} AttackResult;

Fight empty_fight();

Fight turn(DoomDepths game);

Monster monster_takes_damages(Monster m, uint8_t damages);

Player player_takes_damages(Player p, int8_t damages);

AttackResult player_attacks_monster(Player p, Monster m);

AttackResult monster_attacks_player(Monster m, Player p);

Player monsters_attack_player(MonstersList monsters, Player p);

Fight cast_spell_in_fight(Fight f, Spell s);

Fight free_fight(Fight fight);

Fight init_new_fight(Player p, MonstersList m);

#endif //DOOMDEPTHS_FIGHT_H
