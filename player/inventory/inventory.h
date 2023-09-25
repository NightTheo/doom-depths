
//
// Created by Theo OMNES on 24/09/2023.
//

#ifndef DOOMDEPTHS_INVENTORY_H
#define DOOMDEPTHS_INVENTORY_H

#include "stdint.h"
#include "../../fight/weapon/weapon.h"
#include "stdlib.h"
#include "../../fight/loot/loot.h"

#define INVENTORY_CAPACITY 10

typedef enum InventoryItemType {
    EMPTY_ITEM = 0,
    WEAPON_ITEM,
    ARMOR_ITEM,
} InventoryItemType;

typedef struct InventoryItem {
    InventoryItemType type;
    void* item;
} InventoryItem;

typedef struct Inventory {
    u_int8_t items_count;
    u_int8_t capacity;

    u_int16_t golds;
    InventoryItem* items;
} Inventory;

Inventory empty_inventory();
void free_inventory(Inventory inventory);
Inventory add_golds_in_inventory(Inventory inventory, u_int16_t golds);
Inventory push_item_in_inventory(Inventory inventory, InventoryItem item);
Inventory push_loot_in_inventory(Inventory inventory, Loot loot);
char* inventory_to_string(Inventory inventory);
char* item_to_string(InventoryItem item);
InventoryItem weapon_inventory_item(Weapon w);
InventoryItem armor_inventory_item(Armor a);

#endif //DOOMDEPTHS_INVENTORY_H
