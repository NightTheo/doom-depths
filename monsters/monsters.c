
//
// Created by Theo OMNES on 11/09/2023.
//

#include "monsters.h"

#include <stdlib.h>
#include <stdio.h>
#include "../random/random.h"

Monster random_monster() {
    Monster m = {
            random_between_included(10, 20),
            random_between_included(5, 9),
            random_between_included(10, 20),
            random_between_included(10, 20)
    };
    return m;
}

char* stringify_monster(Monster m) {
    char* s = malloc(70);
    sprintf(s, "{health: %d, min_attack_power: %d, max_attack_power: %d, defense: %d}",
            m.health, m.min_attack_power, m.max_attack_power, m.defense);
    return s;
}