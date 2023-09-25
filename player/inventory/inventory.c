
//
// Created by Theo OMNES on 24/09/2023.
//

#include <stdio.h>
#include "inventory.h"
#include "string.h"
#include "../../utils/log/log.h"

void free_inventory_item(InventoryItem item);
InventoryItem empty_inventory_item();

Inventory empty_inventory() {
    u_int8_t capacity = INVENTORY_CAPACITY;
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

InventoryItem weapon_inventory_item(Weapon w) {
    if(w.kind == EMPTY_WEAPON) return empty_inventory_item();
    return (InventoryItem) {
            WEAPON_ITEM,
            weapon_alloc(w),
    };
}

InventoryItem armor_inventory_item(Armor a) {
    if(a.kind == EMPTY_ARMOR) return empty_inventory_item();
    return (InventoryItem ) {
        ARMOR_ITEM,
        armor_alloc(a),
    };
}

Inventory push_loot_in_inventory(Inventory inventory, Loot loot) {
    inventory = add_golds_in_inventory(inventory, loot.gold);
    inventory = push_item_in_inventory(inventory, weapon_inventory_item(loot.weapon));
    inventory = push_item_in_inventory(inventory, armor_inventory_item(loot.armor));
    return inventory;
}

int8_t get_index_of_first_empty_inventory_item(Inventory inventory) {
    int8_t index = -1;
    for(int i = 0; i < inventory.capacity; i++) {
        if(inventory.items[i].type == EMPTY_ITEM) return i;
    }
    return index;
}

Inventory push_item_in_inventory(Inventory inventory, InventoryItem item) {
    if(inventory.items_count >= inventory.capacity) {
        log_info("The inventory is full, item not pushed");
        return inventory;
    }

    if(item.type == EMPTY_ITEM) {
        log_info("Empty item no pushed into inventory.");
        return inventory;
    }

    int8_t index_to_add = get_index_of_first_empty_inventory_item(inventory);
    if(index_to_add == -1) {
        log_error("No empty item in inventory");
        return inventory;
    }
    inventory.items[index_to_add] = item;
    inventory.items_count += 1;

    char* item_str = item_to_string(item);
    char log[64];snprintf(log, 64, "Item %s pushed at %d.", item_str, index_to_add+1);
    log_info(log);
    free(item_str);
    return inventory;
}

Inventory add_golds_in_inventory(Inventory inventory, u_int16_t golds) {
    inventory.golds += golds;
    return inventory;
}

void free_inventory(Inventory inventory) {
    if(inventory.items == NULL) return;

    for(int i = 0; i < inventory.items_count; i++) {
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
        case ARMOR_ITEM: return armor_to_string(*((Armor *)item.item));
    }
}

char* inventory_to_string(Inventory inventory) {
    char* res = malloc(1500);
    char str_items[1024];
    for(int i = 0; i < inventory.capacity; i++) {
        char* item = item_to_string(inventory.items[i]);
        if(i < inventory.capacity-1) {
            const char* separator = ", ";
            item = realloc(item, strlen(item) + strlen(separator) + 1);
            strcat(item, separator);
        }
        strncat(str_items, item, 128);
        free(item);
    }
    snprintf(res, 1500, "Inventory {golds: %d, items: [%s]}", inventory.golds, str_items);
    return res;
}