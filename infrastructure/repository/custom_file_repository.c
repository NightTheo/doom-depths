
//
// Created by Theo OMNES on 25/09/2023.
//

#include <stdio.h>
#include <string.h>
#include "../../domain/repository.h"
#include "../utils/log/log.h"

#define SAVE_FILE_PATH "doomdetphs.save"
#define MAX_LINE_SIZE 512
#define RESTORE_INT_ERROR INT8_MIN

Player restore_player();
MonstersList restore_monsters_list();
char* restore_string_by_key(const char* key);
char* restore_string_by_prefix(const char* prefix, const char* key);
int restore_int_by_key(const char* key);
int restore_int_by_prefix(const char* prefix, const char* key);
Equipment restore_equipment();
Inventory restore_inventory();
Weapon restore_equipment_weapon();
Armor restore_equipment_armor();
InventoryItem restore_inventory_item(uint8_t index);
void *restore_inventory_item_by_type(InventoryItemType type, uint8_t index);
Weapon* restore_inventory_weapon_by_index(uint8_t index);
Weapon restore_weapon_by_prefix_key(const char* prefix_key);

GameState restore_last_game() {
    GameState gs;
    gs.turn = restore_int_by_key("fight.turn");
    gs.player = restore_player();
    gs.monsters_list = restore_monsters_list();

    return gs;
}

char* restore_string_by_key(const char* key) {
    char log[MAX_LINE_SIZE];
    FILE* f = fopen(SAVE_FILE_PATH, "r");
    if(f == NULL) {
        log_error("Unable to open file '" SAVE_FILE_PATH "'.");
        return NULL;
    }

    char line[MAX_LINE_SIZE];
    char string[MAX_LINE_SIZE];
    while(fgets(line, MAX_LINE_SIZE, f) != NULL) {
        size_t key_len = strlen(key);
        bool line_has_key = strlen(line) > key_len+2 && strncmp(line, key, key_len) == 0 && line[key_len] == '=';
        if(line_has_key) {
            sprintf(log, "found key '%s'", key);log_info(log);
            strncpy(string, line+key_len+1, MAX_LINE_SIZE);
            uint16_t value_len = strlen(string);
            if(string[value_len-1] == '\n') string[value_len-1] = '\0';

            char* s = malloc(strlen(string));
            strncpy(s, string, strlen(string));
            sprintf(log, "Value is [%s]", s);log_info(log);
            fclose(f);
            return s;
        }
    }

    fclose(f);
    sprintf(log, "Key [%s] not found", key);log_info(log);
    return NULL;
}

char* restore_string_by_prefix(const char* prefix, const char* key) {
    char full_key[MAX_LINE_SIZE];
    snprintf(full_key, MAX_LINE_SIZE, "%s.%s", prefix, key);
    return restore_string_by_key(full_key);
}

int restore_int_by_key(const char* key) {
    char* str = restore_string_by_key(key);
    if(str == NULL) {
        log_error("Cannot restore int.");
        return RESTORE_INT_ERROR;
    }
    char* end;
    long parsed = strtol(str, &end, 10);
    if(str == end) {
        char log[MAX_LINE_SIZE];
        snprintf(log, MAX_LINE_SIZE, "Parsing string to int error, tried [%s]", str);
        log_error(log);
        return RESTORE_INT_ERROR;
    }

    free(str);
    return (int) parsed;
}

int restore_int_by_prefix(const char* prefix, const char* key) {
    char full_key[MAX_LINE_SIZE];
    snprintf(full_key, MAX_LINE_SIZE, "%s.%s", prefix, key);
    return restore_int_by_key(full_key);
}

Player restore_player() {
    Player p;
    p.current_health = restore_int_by_key("player.current_health");
    p.max_health = restore_int_by_key("player.max_health");
    p.remaining_number_of_attacks = restore_int_by_key("player.remaining_number_of_attacks");
    p.equipment = restore_equipment();
    p.inventory = restore_inventory();

    return p;
}

Equipment restore_equipment() {
    Equipment e = {
            restore_equipment_weapon(),
            restore_equipment_armor(),
    };
    return e;
}

Weapon restore_equipment_weapon() {
    return restore_weapon_by_prefix_key("player.equipment.weapon");
}

/**
 * @param prefix without the end dot
 */
Weapon restore_weapon_by_prefix_key(const char* prefix) {
    char* kind = restore_string_by_prefix(prefix, "kind");

    Weapon w;
    w.kind = weapon_kind_from_string(kind);
    w.min_damages = restore_int_by_prefix(prefix, "min_damages");
    w.max_damages = restore_int_by_prefix(prefix, "max_damages");
    w.max_number_of_attacks_per_turn = restore_int_by_prefix(prefix, "max_number_of_attacks_per_turn");

    free(kind);
    return w;
}

Armor restore_equipment_armor() {
    Armor a;
    char* kind_str = restore_string_by_key("player.equipment.armor.kind");
    a.kind = armor_kind_from_string(kind_str);
    a.defense = restore_int_by_key("player.equipment.armor.defense");

    free(kind_str);
    return a;
}

Inventory restore_inventory() {
    Inventory inventory;
    inventory.items_count = restore_int_by_key("player.inventory.items_count");
    inventory.capacity = restore_int_by_key("player.inventory.capacity");
    inventory.golds = restore_int_by_key("player.inventory.golds");
    inventory.items = malloc(sizeof(InventoryItem) * inventory.capacity);

    for(int i = 0; i < inventory.capacity; i++) {
        inventory.items[i] = restore_inventory_item(i);
    }

    return inventory;
}

InventoryItem restore_inventory_item(uint8_t index) {
    char key[MAX_LINE_SIZE];
    snprintf(key, MAX_LINE_SIZE, "player.inventory.items.%d.type", index);
    char* type_str = restore_string_by_key(key);
    if(type_str == NULL) {
        free(type_str);
        return (InventoryItem) {EMPTY_ITEM, NULL};
    }

    InventoryItem item;
    item.type = inventory_item_type_from_string(type_str);
    item.item = restore_inventory_item_by_type(item.type, index);

    free(type_str);
    return item;
}

void* restore_inventory_item_by_type(InventoryItemType type, uint8_t index) {
    switch (type) {

        case EMPTY_ITEM: return NULL;
        case WEAPON_ITEM: return restore_inventory_weapon_by_index(index);
        case ARMOR_ITEM:
            break;
    }
    return NULL;
}

Weapon* restore_inventory_weapon_by_index(uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    Weapon w = restore_weapon_by_prefix_key(prefix);
    return weapon_alloc(w);
}

MonstersList restore_monsters_list() {
    // TODO
    MonstersList list = {
            0,
            NULL,
    };
    return list;
}

bool save_game_state(GameState gameState) {
    // TODO
    log_info("Save game state");
    return false;
    char* player = player_to_string(gameState.player);
    FILE* f = fopen(SAVE_FILE_PATH, "w");
    if(f == NULL) {
        log_error("Couldn't open file '" SAVE_FILE_PATH "'.");
        return false;
    }
    fprintf(f, "%s", player);
    fclose(f);
    free(player);
    return true;
}