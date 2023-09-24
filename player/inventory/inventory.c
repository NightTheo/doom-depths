
//
// Created by Theo OMNES on 24/09/2023.
//

#include <stdio.h>
#include "inventory.h"
#include "string.h"

void free_inventory_item(InventoryItem item);
InventoryItem empty_inventory_item();

Inventory empty_inventory() {
    u_int8_t capacity = 10;
    Inventory inventory = {
            0,
            capacity,
            0,
            malloc(sizeof(InventoryItem) * capacity)
    };
    for(int i = 0; i < inventory.capacity; i++) {
        inventory.items[i] = empty_inventory_item();
    }
    return inventory;
}

InventoryItem empty_inventory_item() {
    return (InventoryItem){EMPTY_ITEM,NULL};
}

Inventory push_item_in_inventory(Inventory inventory, InventoryItem item) {
    if(inventory.size >= inventory.capacity) return inventory;

    inventory.items[inventory.size] = item;
    inventory.size++;

    return inventory;
}

Inventory add_golds_in_inventory(Inventory inventory, u_int16_t golds) {
    inventory.golds += golds;
    return inventory;
}

void free_inventory(Inventory inventory) {
    if(inventory.items == NULL) return;

    for(int i = 0; i < inventory.size; i++) {
        free_inventory_item(inventory.items[i]);
    }
    inventory.items = NULL;
}

void free_inventory_item(InventoryItem i) {
    if(i.item == NULL) return;
    free(i.item);
    i.item = NULL;
}

char* empty_item_to_string() {
    const char* empty_str = "_";
    char* s = malloc(strlen(empty_str) + 1);
    stpcpy(s, empty_str);
    return s;
}

char* item_to_string(InventoryItem item) {
    switch (item.type) {
        case EMPTY_ITEM: return empty_item_to_string();
        case WEAPON_ITEM: return weapon_to_string(*((Weapon*)item.item));
    }
}

char* inventory_to_string(Inventory inventory) {
    char* res = malloc(512);
    char str_items[512];
    for(int i = 0; i < inventory.capacity; i++) {
        char* item = item_to_string(inventory.items[i]);
        if(i < inventory.capacity-1) {
            const char* separator = ", ";
            item = realloc(item, strlen(item) + strlen(separator) + 1);
            strcat(item, separator);
        }
        strncat(str_items, item, 64);
        free(item);
    }
    snprintf(res, 256, "Inventory {%s}", str_items);
    return res;
}