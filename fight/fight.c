
//
// Created by Theo OMNES on 12/09/2023.
//

#include "fight.h"

Monster monster_takes_damages(Monster m, int8_t damages) {
    int8_t health_after_damages = m.health + m.defense - damages;

    if(health_after_damages < 0) health_after_damages = 0;

    m.health = health_after_damages;
    return m;
}

AttackResult player_attacks_monster(Player p, Monster m) {
    AttackResult res = {
            p,
            monster_takes_damages(m, p.weapon.damages),
    };
    return res;
}
