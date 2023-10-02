
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>

#include "../../../domain/player/player.h"
#include "../../../domain/player/inventory/player_inventory_action/player_inventory_actions.h"

#include "../../../application/port/out/log/log_error.h"
#include "../../../application/port/out/log/log_info.h"
#include "../../../application/port/in/equip_item.h"
#include "../../../application/port/in/drink_potion.h"


void display_inventory_items(Inventory inventory);

void display_inventory_actions();

void display_inventory_golds(uint16_t golds);

PlayerInventoryAction get_player_inventory_action();

uint8_t get_item_index(Inventory inventory);

Player player_use_item_from_inventory(Player p, uint8_t index_item);


Player enter_player_inventory(Player p) {
    while (true) {
        char *equipment_str = equipment_to_string(p.equipment);
        fprintf(stdout, "%s\n", equipment_str);
        free(equipment_str);
        display_inventory_golds(p.inventory.golds);
        display_inventory_items(p.inventory);
        display_inventory_actions();
        PlayerInventoryAction action = get_player_inventory_action();
        char log[128];

        switch (action) {
            case EXIT_INVENTORY:
                return p;
            case EQUIP_ITEM:
                p = player_equip_item_from_inventory(p, get_item_index(p.inventory));
                break;
            case USE_ITEM:
                p = player_use_item_from_inventory(p, get_item_index(p.inventory));
                break;
            default:
                snprintf(log, 64, "unknown action [%d]", action);
                log_error(log);
                break;
        }
    }
}


void display_inventory_items(Inventory inventory) {
    for (int i = 0; i < inventory.capacity; i++) {
        char *item_str = item_to_string(inventory.items[i]);
        fprintf(stdout, "%d.\t%s\n", i + 1, item_str);
        free(item_str);
        item_str = NULL;
    }
}

void display_inventory_actions() {
    fputc('\n', stdout);
    for (PlayerInventoryAction a = 0; a < _player_inventory_action_count; a++) {
        fprintf(stdout, "%d. %s\n", a + 1, inventory_action_to_string(a));
    }
}

void display_inventory_golds(uint16_t golds) {
    fprintf(stdout, "Golds: %d\n", golds);
}

PlayerInventoryAction get_player_inventory_action() {
    int8_t input = -1;
    do {
        fflush(stdin);
        scanf("%hhd", &input);
    } while (input < 1 || input > _player_inventory_action_count);

    char log[32];
    sprintf(log, "player choose %s", inventory_action_to_string(input - 1));
    log_info(log);

    return (PlayerInventoryAction) input - 1;
}

uint8_t get_item_index(Inventory inventory) {
    int8_t input = -1;

    fprintf(stdout, "Select item an item (enter its number) [1-10]\n");
    do {
        fflush(stdin);
        scanf("%hhd", &input);
    } while (input < 1 || input > inventory.capacity);

    return input - 1;
}

Player player_use_item_from_inventory(Player p, uint8_t index_item) {
    char log[64];
    if (index_item < 0 || index_item >= p.inventory.capacity) {
        snprintf(log, 64, "Index [%d] is not in inventory", index_item);
        log_error(log);
        return p;
    }

    InventoryItem item_to_use = p.inventory.items[index_item];
    switch (item_to_use.type) {
        case EMPTY_ITEM:
            log_info("Empty item, nothing to do.");
            break;
        case POTION_ITEM:
            p = drink_potion_at_index(p, index_item);
            break;
        default:
            log_info("Item not usable.");
            break;
    }

    return p;
}