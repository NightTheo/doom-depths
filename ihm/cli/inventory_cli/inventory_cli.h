
//
// Created by Theo OMNES on 24/09/2023.
//

#ifndef DOOMDEPTHS_INVENTORY_CLI_H
#define DOOMDEPTHS_INVENTORY_CLI_H

#include "../../ihm.h"
#include "../cli_ihm.h"
#include "../../../domain/player/inventory/inventory.h"
#include "../../../domain/player/inventory/player_inventory_action/player_inventory_actions.h"

void display_inventory_items(Inventory inventory);
void display_inventory_actions();
void display_inventory_golds(uint16_t golds);
PlayerInventoryAction get_player_inventory_action();
uint8_t get_item_index_to_equip(Inventory inventory);

#endif //DOOMDEPTHS_INVENTORY_CLI_H
