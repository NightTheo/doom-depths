
//
// Created by Theo OMNES on 24/09/2023.
//

#include "inventory.h"

void free_inventory_item(InventoryItem* item);
void free_weapon_inventory_item(WeaponInventoryItem* item);

Inventory empty_inventory() {
    Inventory i = {
            0,
            10,
            0,
            NULL
    };
    return i;
}

Inventory free_inventory(Inventory i) {
    InventoryItem* item = i.items;
    while (item != NULL) {
        free(item);
        item = item->next;
    }

    i.items = NULL;
    return i;
}