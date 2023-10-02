
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include <string.h>
#include "../../../application/port/out/persistence/storage/save_game_state.h"
#include "../../../application/port/out/log/log_info.h"
#include "../../../application/port/out/log/log_error.h"


#define SAVE_FILE_PATH "doomdetphs.save"
#define MAX_LINE_SIZE 512
#define RESTORE_INT_ERROR INT8_MIN
#define WRITE_BUFFER_SIZE 4096


char *player_to_save_string(Player player);

char *turn_to_save_string(uint8_t turn);

char *monsters_list_to_save_string(MonstersList m);

char *inventory_to_save_string(Inventory inventory);

char *item_to_save_string(InventoryItem item, uint8_t index);

const char *item_type_to_string(InventoryItemType type);

char *item_to_save_string_by_type(InventoryItem item, uint8_t index);

char *weapon_to_save_string_with_prefix(Weapon w, const char *prefix);

char *equipment_to_save_string(Equipment e);

const char *weapon_kind_to_save_string(WeaponKind k);

char *armor_to_save_string_with_prefix(Armor a, const char *prefix);

const char *armor_kind_to_save_string(ArmorKind k);

char *monster_to_save_string_at_index(Monster m, uint8_t index);

char *potion_to_save_string_with_prefix(ManaPotion p, const char *prefix);

char *map_to_save_string(Map);

char *map_zones_to_save_string(Map map);

char *zone_to_save_string(Zone z, uint8_t x, uint8_t y);

const char *zone_status_to_save_string(ZoneStatus status);

RepositoryStatus save_game_state(DoomDepths game) {
    log_info("Save game state");

    Zone current_zone = get_player_current_zone_in_map(game.map);
    char *player_str = player_to_save_string(current_zone.fight.player);
    char *turn_str = turn_to_save_string(current_zone.fight.turn);
    char *monsters_str = monsters_list_to_save_string(current_zone.fight.monsters_list);
    char *map_str = map_to_save_string(game.map);

    FILE *f = fopen(SAVE_FILE_PATH, "w");
    if (f == NULL) {
        log_error("Couldn't open file '" SAVE_FILE_PATH "'.");
        return SAVE_LAST_GAME_FAILED;
    }

    fprintf(f, "%s\n"
               "%s\n"
               "%s\n"
               "%s",
            turn_str,
            player_str,
            monsters_str,
            map_str
    );

    free(turn_str);
    free(player_str);
    free(monsters_str);
    free(map_str);
    fclose(f);
    return SAVE_LAST_GAME_SUCCEEDED;
}

char *player_to_save_string(Player p) {
    char *s = malloc(WRITE_BUFFER_SIZE);
    char *equipment_str = equipment_to_save_string(p.equipment);
    char *inventory_str = inventory_to_save_string(p.inventory);

    snprintf(s, WRITE_BUFFER_SIZE,
             "\n@PLAYER@\n"
             "player.current_health=%d\n"
             "player.max_health=%d\n"
             "player.remaining_number_of_attacks=%d\n"
             "%s\n"
             "%s\n"
             "player.max_mana=%d\n"
             "player.current_mana=%d",
             p.current_health,
             p.max_health,
             p.remaining_number_of_attacks,
             equipment_str,
             inventory_str,
             p.max_mana,
             p.current_mana
    );

    free(equipment_str);
    free(inventory_str);
    return s;
}

char *equipment_to_save_string(Equipment e) {
    char *weapon_str = weapon_to_save_string_with_prefix(e.weapon, "player.equipment.weapon");
    char *armor_str = armor_to_save_string_with_prefix(e.armor, "player.equipment.armor");
    char *s = malloc(WRITE_BUFFER_SIZE);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s\n"
             "%s",
             weapon_str,
             armor_str
    );
    free(weapon_str);
    free(armor_str);
    return s;
}

char *inventory_to_save_string(Inventory inventory) {
    char *s = malloc(WRITE_BUFFER_SIZE);
    snprintf(s, WRITE_BUFFER_SIZE,
             "player.inventory.items_count=%d\n"
             "player.inventory.capacity=%d\n"
             "player.inventory.golds=%d\n",
             inventory.items_count,
             inventory.capacity,
             inventory.golds
    );
    if (inventory.items_count == 0) strcat(s, "// empty inventory");
    for (int i = 0; i < inventory.capacity; i++) {
        if (inventory.items[i].type == EMPTY_ITEM) continue;
        char *item_str = item_to_save_string(inventory.items[i], i);
        strcat(s, item_str);
        free(item_str);
    }
    return s;
}

char *item_to_save_string(InventoryItem item, uint8_t index) {
    uint16_t item_buffer_size = 256;
    char *s = malloc(item_buffer_size);
    const char *type_str = item_type_to_string(item.type);
    char *item_str = item_to_save_string_by_type(item, index);
    snprintf(s, item_buffer_size,
             "player.inventory.items.%d.type=%s\n"
             "%s\n",
             index, type_str,
             item_str);

    return s;
}

const char *item_type_to_string(InventoryItemType type) {
    char log[MAX_LINE_SIZE];
    switch (type) {
        case EMPTY_ITEM:
            return "EMPTY_ITEM";
        case WEAPON_ITEM:
            return "WEAPON_ITEM";
        case ARMOR_ITEM:
            return "ARMOR_ITEM";
        case POTION_ITEM:
            return "POTION_ITEM";
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown InventoryItemType [%d]", type);
            log_error(log);
            return "Unknown InventoryItemType";
    }
}

char *item_to_save_string_by_type(InventoryItem item, uint8_t index) {
    char log[MAX_LINE_SIZE];
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    switch (item.type) {
        case EMPTY_ITEM:
            return NULL;
        case WEAPON_ITEM:
            return weapon_to_save_string_with_prefix(*((Weapon *) item.item), prefix);
        case ARMOR_ITEM:
            return armor_to_save_string_with_prefix(*((Armor *) item.item), prefix);
        case POTION_ITEM:
            return potion_to_save_string_with_prefix(*((ManaPotion *) item.item), prefix);
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown InventoryItemType [%d]", item.type);
            log_error(log);
            return NULL;
    }
}

char *weapon_to_save_string_with_prefix(Weapon w, const char *prefix) {
    char *s = malloc(WRITE_BUFFER_SIZE);
    const char *kind_str = weapon_kind_to_save_string(w.kind);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s.kind=%s\n"
             "%s.min_damages=%d\n"
             "%s.max_damages=%d\n"
             "%s.max_number_of_attacks_per_turn=%d",
             prefix, kind_str,
             prefix, w.min_damages,
             prefix, w.max_damages,
             prefix, w.max_number_of_attacks_per_turn
    );
    return s;
}

const char *weapon_kind_to_save_string(WeaponKind k) {
    char log[MAX_LINE_SIZE];
    switch (k) {
        case EMPTY_WEAPON:
            return "EMPTY_WEAPON";
        case SWORD:
            return "SWORD";
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown WeaponKind [%d]", k);
            log_error(log);
            return "Unknown WeaponKind";;
    }
}

char *armor_to_save_string_with_prefix(Armor a, const char *prefix) {
    char *s = malloc(WRITE_BUFFER_SIZE);
    const char *kind_str = armor_kind_to_save_string(a.kind);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s.kind=%s\n"
             "%s.defense=%d",
             prefix, kind_str,
             prefix, a.defense
    );
    return s;
}

const char *armor_kind_to_save_string(ArmorKind k) {
    char log[MAX_LINE_SIZE];
    switch (k) {
        case EMPTY_ARMOR:
            return "EMPTY_ARMOR";
        case CHEST_PLATE:
            return "CHEST_PLATE";
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown ArmorKind [%d]", k);
            log_error(log);
            return "Unknown ArmorKind";
    }
}

char *turn_to_save_string(uint8_t turn) {
    char *s = malloc(MAX_LINE_SIZE);
    snprintf(s, MAX_LINE_SIZE, "fight.round=%d", turn);

    return s;
}

char *monsters_list_to_save_string(MonstersList m) {
    char *s = malloc(WRITE_BUFFER_SIZE);

    snprintf(s, WRITE_BUFFER_SIZE,
             "\n@MONSTERS@\n"
             "monsters_list.size=%d\n", m.size
    );
    for (int i = 0; i < m.size; i++) {
        char *monster_str = monster_to_save_string_at_index(m.monsters[i], i);
        strcat(s, monster_str);
        free(monster_str);
    }
    return s;
}

char *monster_to_save_string_at_index(Monster m, uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "monsters_list.monsters.%d", index);
    char *s = malloc(WRITE_BUFFER_SIZE);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s.health=%d\n"
             "%s.min_attack_power=%d\n"
             "%s.max_attack_power=%d\n"
             "%s.defense=%d\n",
             prefix, m.health,
             prefix, m.min_attack_power,
             prefix, m.max_attack_power,
             prefix, m.defense
    );
    return s;
}


char *potion_to_save_string_with_prefix(ManaPotion p, const char *prefix) {
    char *s = malloc(MAX_LINE_SIZE);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s.is_full=%d",
             prefix, p.is_full
    );
    return s;
}

char *map_to_save_string(Map map) {
    char *s = malloc(WRITE_BUFFER_SIZE);
    if (s == NULL) {
        log_allocation_error();
        return NULL;
    }
    char *zones_str = map_zones_to_save_string(map);

    snprintf(s, WRITE_BUFFER_SIZE,
             "\n@MAP@\n"
             "map.width=%d\n"
             "map.height=%d\n"
             "map.spawn.zone_x=%d\n"
             "map.spawn.zone_y=%d\n"
             "%s",
             map.width,
             map.height,
             map.spawn.zone_x,
             map.spawn.zone_y,
             zones_str
    );

    free(zones_str);
    return s;
}

char *map_zones_to_save_string(Map map) {
    char *s = malloc(WRITE_BUFFER_SIZE);
    if (s == NULL) {
        log_allocation_error();
        return NULL;
    }
    strncpy(s, "", 4);
    for (int x = 0; x < map.width; x++) {
        for (int y = 0; y < map.height; y++) {
            char *zone_str = zone_to_save_string(map.zones[y][x], x, y);
            strcat(s, zone_str);
            free(zone_str);
        }
    }
    return s;
}

char *zone_to_save_string(Zone z, uint8_t x, uint8_t y) {
    char *s = malloc(MAX_LINE_SIZE);
    strcpy(s, "");
    const char *status_str = zone_status_to_save_string(z.status);
    snprintf(s, MAX_LINE_SIZE, "map.zones.x[%d].y[%d].status=%s\n", x, y, status_str);
    return s;
}

const char *zone_status_to_save_string(ZoneStatus status) {
    switch (status) {
        case ZONE_EMPTY:
            return "ZONE_EMPTY";
        case ZONE_NOT_DISCOVERED:
            return "ZONE_NOT_DISCOVERED";
        case ZONE_FINISHED:
            return "ZONE_FINISHED";
        default: {
            char log[32];
            snprintf(log, 32, "Unknown ZoneStatus [%d]", status);
            log_error(log);
            return "?";
        }
    }
}
