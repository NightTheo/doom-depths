
//
// Created by Theo OMNES on 29/09/2023.
//

#ifndef DOOMDEPTHS_DOOM_DEPTHS_H
#define DOOMDEPTHS_DOOM_DEPTHS_H

#include "../map/map.h"
#include "stdbool.h"

typedef struct DoomDepths DoomDepths;
struct DoomDepths {
    Map map;
    Player player;
};

DoomDepths new_doom_depths(Position spawn, Map map, Player p);
Fight get_current_fight_in_game(DoomDepths game);
DoomDepths set_current_fight_in_game(DoomDepths game, Fight f);
void free_doom_depths(DoomDepths game);
bool doom_depths_is_empty(DoomDepths game);
DoomDepths set_current_zone_in_game(DoomDepths game, Zone zone);

#endif //DOOMDEPTHS_DOOM_DEPTHS_H
