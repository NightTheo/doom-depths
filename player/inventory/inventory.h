
//
// Created by Theo OMNES on 24/09/2023.
//

#ifndef DOOMDEPTHS_INVENTORY_H
#define DOOMDEPTHS_INVENTORY_H

#include "stdint.h"
#include "../../fight/weapon/weapon.h"
#include "stdlib.h"

typedef struct Inventory {
    u_int8_t size;
    u_int8_t capacity;

    u_int16_t golds;
    void* items;
} Inventory;

typedef enum InventoryItemType {
    WEAPON_ITEM,
} InventoryItemType;

typedef struct InventoryItem {
    InventoryItemType type;
    void* next;
} InventoryItem;

typedef struct WeaponInventoryItem {
    InventoryItemType type;
    void* next;
    Weapon weapon;
} WeaponInventoryItem;

Inventory empty_inventory();
Inventory free_inventory(Inventory i);


#endif //DOOMDEPTHS_INVENTORY_H
