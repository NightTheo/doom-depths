
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include <string.h>
#include "../../../application/port/out/persistence/restore_last_game.h"
#include "../../../application/port/out/log/log_error.h"
#include "../../../application/port/out/log/log_info.h"


#define SAVE_FILE_PATH "doomdetphs.save"
#define MAX_LINE_SIZE 512
#define RESTORE_INT_ERROR INT8_MIN
#define WRITE_BUFFER_SIZE 4096

DoomDepths restore_doom_depths();

Player restore_player();

MonstersList restore_monsters_list();

Monster restore_monster_by_index(uint8_t index);

char *restore_string_by_key(const char *key);

char *restore_string_by_prefix(const char *prefix, const char *key);

int restore_int_by_key(const char *key);

int restore_int_by_prefix(const char *prefix, const char *key);

Equipment restore_equipment();

Inventory restore_inventory();

Weapon restore_equipment_weapon();

Armor restore_equipment_armor();

Armor restore_armor_by_prefix_key(const char *prefix);

InventoryItem restore_inventory_item(uint8_t index);

void *restore_inventory_item_by_type(InventoryItemType type, uint8_t index);

Weapon *restore_inventory_weapon_by_index(uint8_t index);

Weapon restore_weapon_by_prefix_key(const char *prefix_key);

Armor *restore_inventory_armor_by_index(uint8_t index);

bool file_exists(const char *path);

ManaPotion *restore_inventory_potion_by_index(uint8_t index);

ManaPotion restore_potion_by_prefix_key(const char *prefix);

Position restore_player_position();

ZoneStatus zone_status_from_save_string(const char *str);

Map restore_map();

Zone **restore_map_zones(uint16_t height, uint16_t width);

Zone restore_zone_by_position(Position position);

Zone restore_zone_by_prefix(const char *prefix);


bool file_exists(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) return false;

    fclose(f);
    return true;
}

char *restore_string_by_key(const char *key) {
    char log[MAX_LINE_SIZE];
    FILE *f = fopen(SAVE_FILE_PATH, "r");
    if (f == NULL) {
        log_error("Unable to open file '" SAVE_FILE_PATH "'.");
        return NULL;
    }

    char line[MAX_LINE_SIZE];
    char string[MAX_LINE_SIZE];
    while (fgets(line, MAX_LINE_SIZE, f) != NULL) {
        size_t key_len = strlen(key);
        bool line_has_key = strlen(line) > key_len + 1 && strncmp(line, key, key_len) == 0 && line[key_len] == '=';
        if (line_has_key) {
            sprintf(log, "found key '%s'", key);
            log_info(log);
            strncpy(string, line + key_len + 1, MAX_LINE_SIZE);
            uint16_t value_len = strlen(string);
            if (string[value_len - 1] == '\n') string[value_len - 1] = '\0';

            char *s = malloc(strlen(string));
            strncpy(s, string, strlen(string));
            sprintf(log, "Value is [%s]", s);
            log_info(log);
            fclose(f);
            return s;
        }
    }

    fclose(f);
    sprintf(log, "Key [%s] not found", key);
    log_info(log);
    return NULL;
}

char *restore_string_by_prefix(const char *prefix, const char *key) {
    char full_key[MAX_LINE_SIZE];
    snprintf(full_key, MAX_LINE_SIZE, "%s.%s", prefix, key);
    return restore_string_by_key(full_key);
}

int restore_int_by_key(const char *key) {
    char *str = restore_string_by_key(key);
    if (str == NULL) {
        log_error("Cannot restore int.");
        return RESTORE_INT_ERROR;
    }
    char *end;
    long parsed = strtol(str, &end, 10);
    if (str == end) {
        char log[MAX_LINE_SIZE];
        snprintf(log, MAX_LINE_SIZE, "Parsing string to int error, tried [%s]", str);
        log_error(log);
        return RESTORE_INT_ERROR;
    }

    free(str);
    return (int) parsed;
}

int restore_int_by_prefix(const char *prefix, const char *key) {
    char full_key[MAX_LINE_SIZE];
    snprintf(full_key, MAX_LINE_SIZE, "%s.%s", prefix, key);
    return restore_int_by_key(full_key);
}


GameState restore_last_game() {
    log_info("Restore last game");
    if (!file_exists(SAVE_FILE_PATH)) {
        log_error("Save file [" SAVE_FILE_PATH "] not found.");
        return (GameState) {RESTORE_LAST_GAME_FAILED};
    }

    GameState gs;
    gs.game = restore_doom_depths();
    gs.repository_status = RESTORE_LAST_GAME_SUCCEEDED; // TODO check last game is valid
    return gs;
}

DoomDepths restore_doom_depths() {
    DoomDepths game;
    game.player = restore_player();
    game.map = restore_map();
    Fight fight;
    fight.turn = (int8_t) restore_int_by_key("fight.turn");
    fight.player = game.player;
    fight.monsters_list = restore_monsters_list();

    Position position = game.map.spawn;
    game.map.zones[position.zone_y][position.zone_x].fight = fight;

    return game;
}

Position restore_player_position() {
    Position p;
    p.zone_x = restore_int_by_key("map.spawn.zone_x");
    p.zone_y = restore_int_by_key("map.spawn.zone_y");

    if (p.zone_x < 0 || p.zone_y < 0) return no_position();

    return p;
}

Player restore_player() {
    Player p;
    p.current_health = restore_int_by_key("player.current_health");
    p.max_health = restore_int_by_key("player.max_health");
    p.remaining_number_of_attacks = restore_int_by_key("player.remaining_number_of_attacks");
    p.equipment = restore_equipment();
    p.inventory = restore_inventory();
    p.max_mana = restore_int_by_key("player.max_mana");
    p.current_mana = restore_int_by_key("player.current_mana");
    p.grimoire = start_grimoire();

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
Weapon restore_weapon_by_prefix_key(const char *prefix) {
    char *kind = restore_string_by_prefix(prefix, "kind");

    Weapon w;
    w.kind = weapon_kind_from_string(kind);
    w.min_damages = restore_int_by_prefix(prefix, "min_damages");
    w.max_damages = restore_int_by_prefix(prefix, "max_damages");
    w.max_number_of_attacks_per_turn = restore_int_by_prefix(prefix, "max_number_of_attacks_per_turn");

    free(kind);
    return w;
}

Armor restore_equipment_armor() {
    return restore_armor_by_prefix_key("player.equipment.armor");
}

Armor restore_armor_by_prefix_key(const char *prefix) {
    Armor a;
    char *kind_str = restore_string_by_prefix(prefix, "kind");
    a.kind = armor_kind_from_string(kind_str);
    a.defense = restore_int_by_prefix(prefix, "defense");

    free(kind_str);
    return a;
}

Inventory restore_inventory() {
    Inventory inventory;
    inventory.items_count = restore_int_by_key("player.inventory.items_count");
    inventory.capacity = restore_int_by_key("player.inventory.capacity");
    inventory.golds = restore_int_by_key("player.inventory.golds");
    inventory.items = malloc(sizeof(InventoryItem) * inventory.capacity);

    for (int i = 0; i < inventory.capacity; i++) {
        inventory.items[i] = restore_inventory_item(i);
    }

    return inventory;
}

InventoryItem restore_inventory_item(uint8_t index) {
    char key[MAX_LINE_SIZE];
    snprintf(key, MAX_LINE_SIZE, "player.inventory.items.%d.type", index);
    char *type_str = restore_string_by_key(key);
    if (type_str == NULL) {
        free(type_str);
        return (InventoryItem) {EMPTY_ITEM, NULL};
    }

    InventoryItem item;
    item.type = inventory_item_type_from_string(type_str);
    item.item = restore_inventory_item_by_type(item.type, index);

    free(type_str);
    return item;
}

void *restore_inventory_item_by_type(InventoryItemType type, uint8_t index) {
    char log[MAX_LINE_SIZE];
    switch (type) {
        case EMPTY_ITEM:
            return NULL;
        case WEAPON_ITEM:
            return restore_inventory_weapon_by_index(index);
        case ARMOR_ITEM:
            return restore_inventory_armor_by_index(index);
        case POTION_ITEM:
            return restore_inventory_potion_by_index(index);
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown InventoryItemType [%d]", type);
            log_error(log);
            return NULL;
    }
}

Weapon *restore_inventory_weapon_by_index(uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    return weapon_alloc(restore_weapon_by_prefix_key(prefix));
}

Armor *restore_inventory_armor_by_index(uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    return armor_alloc(restore_armor_by_prefix_key(prefix));
}

ManaPotion *restore_inventory_potion_by_index(uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    return mana_potion_alloc(restore_potion_by_prefix_key(prefix));
}

ManaPotion restore_potion_by_prefix_key(const char *prefix) {
    ManaPotion p;
    p.is_full = restore_int_by_prefix(prefix, "is_full");
    return p;
}

Map restore_map() {
    Map map;
    map.width = restore_int_by_key("map.width");
    map.height = restore_int_by_key("map.height");
    map.spawn = restore_player_position();
    map.zones = restore_map_zones(map.height, map.width);

    return map;
}

Zone **restore_map_zones(uint16_t height, uint16_t width) {
    Zone **zones = malloc(sizeof(Zone *) * height);
    if (zones == NULL) {
        log_allocation_error();
        return NULL;
    }

    for (int row = 0; row < height; row++) {
        zones[row] = NULL;
    }

    for (int y = 0; y < height; y++) {
        zones[y] = malloc(sizeof(Zone) * width);
        if (zones[y] == NULL) {
            log_allocation_error();
            free_zones(zones, height, width);
            return NULL;
        }
        for (int x = 0; x < width; x++) {
            zones[y][x] = restore_zone_by_position((Position) {x, y});
        }
    }
    return zones;
}

Zone restore_zone_by_position(Position position) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "map.zones.x[%d].y[%d]", position.zone_x, position.zone_y);
    return restore_zone_by_prefix(prefix);

}

Zone restore_zone_by_prefix(const char *prefix) {
    char *status_str = restore_string_by_prefix(prefix, "status");
    if (status_str == NULL) {
        log_error("Could not restore zone");
        return empty_zone();
    }
    Zone z;
    z.fight = empty_fight();
    z.status = zone_status_from_save_string(status_str);

    free(status_str);
    return z;
}


MonstersList restore_monsters_list() {
    MonstersList list;
    list.size = (int8_t) restore_int_by_key("monsters_list.size");
    list.monsters = malloc(sizeof(Monster) * list.size);
    for (int i = 0; i < list.size; i++) {
        list.monsters[i] = restore_monster_by_index(i);
    }
    return list;
}

Monster restore_monster_by_index(uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "monsters_list.monsters.%d", index);
    Monster m;
    m.health = (int8_t) restore_int_by_prefix(prefix, "health");
    m.min_attack_power = (int8_t) restore_int_by_prefix(prefix, "min_attack_power");
    m.max_attack_power = (int8_t) restore_int_by_prefix(prefix, "max_attack_power");
    m.defense = (int8_t) restore_int_by_prefix(prefix, "defense");
    return m;
}

ZoneStatus zone_status_from_save_string(const char *str) {
    if (strcmp(str, "ZONE_EMPTY") == 0) return ZONE_EMPTY;
    if (strcmp(str, "ZONE_NOT_DISCOVERED") == 0) return ZONE_NOT_DISCOVERED;
    if (strcmp(str, "ZONE_FINISHED") == 0) return ZONE_FINISHED;
    char log[32];
    snprintf(log, 32, "Unknown ZoneStatus [%s]", str);
    log_error(log);
    return ZONE_EMPTY;
}