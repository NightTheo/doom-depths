
//
// Created by Theo OMNES on 01/10/2023.
//

#ifndef DOOMDEPTHS_EQUIP_ITEM_H
#define DOOMDEPTHS_EQUIP_ITEM_H

#include <stdint.h>

typedef struct Player Player;

Player player_equip_item_from_inventory(Player p, uint8_t index_item);

#endif //DOOMDEPTHS_EQUIP_ITEM_H
