
//
// Created by Theo OMNES on 11/09/2023.
//

#ifndef DOOMDEPTHS_MONSTERS_H
#define DOOMDEPTHS_MONSTERS_H

#include "monster.h"

int random_between_included(int min, int max);
Monster random_monster();
char* stringify_monster(Monster m);

#endif //DOOMDEPTHS_MONSTERS_H
