
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
#define WRITE_BUFFER_SIZE 4096

// READ ---------
Player restore_player();
MonstersList restore_monsters_list();
Monster restore_monster_by_index(uint8_t index);
char* restore_string_by_key(const char* key);
char* restore_string_by_prefix(const char* prefix, const char* key);
int restore_int_by_key(const char* key);
int restore_int_by_prefix(const char* prefix, const char* key);
Equipment restore_equipment();
Inventory restore_inventory();
Weapon restore_equipment_weapon();
Armor restore_equipment_armor();
Armor restore_armor_by_prefix_key(const char* prefix);
InventoryItem restore_inventory_item(uint8_t index);
void *restore_inventory_item_by_type(InventoryItemType type, uint8_t index);
Weapon* restore_inventory_weapon_by_index(uint8_t index);
Weapon restore_weapon_by_prefix_key(const char* prefix_key);
Armor* restore_inventory_armor_by_index(uint8_t index);
bool file_exists(const char* path);
ManaPotion* restore_inventory_potion_by_index(uint8_t index);
ManaPotion restore_potion_by_prefix_key(const char* prefix);
Position restore_player_position();

// WRITE ---------
char* player_to_save_string(Player player);
char* turn_to_save_string(uint8_t turn);
char* monsters_list_to_save_string(MonstersList m);
char* inventory_to_save_string(Inventory inventory);
char *item_to_save_string(InventoryItem item, uint8_t index);
const char* item_type_to_string(InventoryItemType type);
char* item_to_save_string_by_type(InventoryItem item, uint8_t index);
char* weapon_to_save_string_with_prefix(Weapon w, const char* prefix);
char* equipment_to_save_string(Equipment e);
const char* weapon_kind_to_save_string(WeaponKind k);
char* armor_to_save_string_with_prefix(Armor a, const char* prefix);
const char* armor_kind_to_save_string(ArmorKind k);
char* monster_to_save_string_at_index(Monster m, uint8_t index);
char* potion_to_save_string_with_prefix(ManaPotion p, const char* prefix);
char* map_to_save_string(Map);


GameState restore_last_game() {
    log_info("Restore last game");
    if(!file_exists(SAVE_FILE_PATH)) {
        log_error("Save file [" SAVE_FILE_PATH "] not found.");
        return (GameState){RESTORE_LAST_GAME_FAILED};
    }

    GameState gs;
    gs.game = restore_doom_depths();
    gs.repository_status = RESTORE_LAST_GAME_SUCCEEDED; // TODO check last game is valid
    return gs;
}

bool file_exists(const char* path) {
    FILE* f = fopen(path, "r");
    if(f == NULL) return false;

    fclose(f);
    return true;
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
        bool line_has_key = strlen(line) > key_len+1 && strncmp(line, key, key_len) == 0 && line[key_len] == '=';
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

DoomDepths restore_doom_depths() {
    DoomDepths game;
    game.player = restore_player();
    game.map = basic_map(); // TODO restore and save map
    Position position = restore_player_position();
    game.map.playerPosition = position;
    Fight fight;
    fight.turn = (int8_t)restore_int_by_key("fight.turn");
    fight.player = game.player;
    fight.monsters_list = restore_monsters_list();
    game.map.zones[position.zone_y][position.zone_x].fight = fight;

    return game;
}

Position restore_player_position() {
    Position p;
    p.zone_x = restore_int_by_key("map.playerPosition.zone_x");
    p.zone_y = restore_int_by_key("map.playerPosition.zone_y");

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
    return restore_armor_by_prefix_key("player.equipment.armor");
}

Armor restore_armor_by_prefix_key(const char* prefix) {
    Armor a;
    char* kind_str = restore_string_by_prefix(prefix, "kind");
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
    char log[MAX_LINE_SIZE];
    switch (type) {
        case EMPTY_ITEM: return NULL;
        case WEAPON_ITEM: return restore_inventory_weapon_by_index(index);
        case ARMOR_ITEM: return restore_inventory_armor_by_index(index);
        case POTION_ITEM: return restore_inventory_potion_by_index(index);
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown InventoryItemType [%d]", type);
            log_error(log);
            return NULL;
    }
}

Weapon* restore_inventory_weapon_by_index(uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    return weapon_alloc(restore_weapon_by_prefix_key(prefix));
}

Armor* restore_inventory_armor_by_index(uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    return armor_alloc(restore_armor_by_prefix_key(prefix));
}

ManaPotion* restore_inventory_potion_by_index(uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    return mana_potion_alloc(restore_potion_by_prefix_key(prefix));
}

ManaPotion restore_potion_by_prefix_key(const char* prefix) {
    ManaPotion p;
    p.is_full = restore_int_by_prefix(prefix, "is_full");
    return p;
}

MonstersList restore_monsters_list() {
    MonstersList list;
    list.size = (int8_t) restore_int_by_key("monsters_list.size");
    list.monsters = malloc(sizeof(Monster) * list.size);
    for(int i = 0; i < list.size; i++) {
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




RepositoryStatus save_game_state(GameState gameState) {
    log_info("Save game state");

    Map map = gameState.game.map;
    Zone current_zone = get_zone_of_player_current_zone_in_map(map);
    char* player_str = player_to_save_string(current_zone.fight.player);
    char* turn_str = turn_to_save_string(current_zone.fight.turn);
    char* monsters_str = monsters_list_to_save_string(current_zone.fight.monsters_list);
    char* map_str = map_to_save_string(gameState.game.map);

    FILE* f = fopen(SAVE_FILE_PATH, "w");
    if(f == NULL) {
        log_error("Couldn't open file '" SAVE_FILE_PATH "'.");
        return SAVE_LAST_GAME_FAILED;
    }

    fprintf(f, "%s\n"
               "%s\n"
               "%s\n"
               "%s"
               ,
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

void log_repository_status(RepositoryStatus status) {
    char log[64];
    const char* status_str = repository_status_to_string(status);
    snprintf(log, 64, "Repository status: [%s]", status_str);
}

char* player_to_save_string(Player p) {
    char* s = malloc(WRITE_BUFFER_SIZE);
    char* equipment_str = equipment_to_save_string(p.equipment);
    char* inventory_str = inventory_to_save_string(p.inventory);

    snprintf(s, WRITE_BUFFER_SIZE,
             "\n@PLAYER@\n"
             "player.current_health=%d\n"
             "player.max_health=%d\n"
             "player.remaining_number_of_attacks=%d\n"
             "%s\n"
             "%s\n"
             "player.max_mana=%d\n"
             "player.current_mana=%d"
             ,
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

char* equipment_to_save_string(Equipment e) {
    char* weapon_str = weapon_to_save_string_with_prefix(e.weapon, "player.equipment.weapon");
    char* armor_str = armor_to_save_string_with_prefix(e.armor, "player.equipment.armor");
    char* s = malloc(WRITE_BUFFER_SIZE);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s\n"
             "%s"
             ,
             weapon_str,
             armor_str
             );
    free(weapon_str);
    free(armor_str);
    return s;
}

char* inventory_to_save_string(Inventory inventory) {
    char* s = malloc(WRITE_BUFFER_SIZE);
    snprintf(s, WRITE_BUFFER_SIZE,
             "player.inventory.items_count=%d\n"
             "player.inventory.capacity=%d\n"
             "player.inventory.golds=%d\n"
             ,
             inventory.items_count,
             inventory.capacity,
             inventory.golds
             );
    for(int i = 0; i < inventory.capacity; i++) {
        if(inventory.items[i].type == EMPTY_ITEM) continue;
        char* item_str = item_to_save_string(inventory.items[i], i);
        strcat(s, item_str);
        free(item_str);
    }
    return s;
}

char *item_to_save_string(InventoryItem item, uint8_t index) {
    uint16_t item_buffer_size = 256;
    char *s = malloc(item_buffer_size);
    const char* type_str = item_type_to_string(item.type);
    char* item_str = item_to_save_string_by_type(item, index);
    snprintf(s, item_buffer_size,
             "player.inventory.items.%d.type=%s\n"
             "%s\n"
             ,
             index, type_str,
             item_str);

    return s;
}

const char* item_type_to_string(InventoryItemType type) {
    char log[MAX_LINE_SIZE];
    switch (type) {
        case EMPTY_ITEM: return "EMPTY_ITEM";
        case WEAPON_ITEM: return "WEAPON_ITEM";
        case ARMOR_ITEM: return "ARMOR_ITEM";
        case POTION_ITEM: return "POTION_ITEM";
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown InventoryItemType [%d]", type);
            log_error(log);
            return "Unknown InventoryItemType";
    }
}

char* item_to_save_string_by_type(InventoryItem item, uint8_t index) {
    char log[MAX_LINE_SIZE];
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "player.inventory.items.%d.item", index);
    switch (item.type) {
        case EMPTY_ITEM: return NULL;
        case WEAPON_ITEM: return weapon_to_save_string_with_prefix(*((Weapon *) item.item), prefix);
        case ARMOR_ITEM: return armor_to_save_string_with_prefix(*((Armor *) item.item), prefix);
        case POTION_ITEM: return potion_to_save_string_with_prefix(*((ManaPotion *) item.item), prefix);
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown InventoryItemType [%d]", item.type);
            log_error(log);
            return NULL;
    }
}

char* weapon_to_save_string_with_prefix(Weapon w, const char* prefix) {
    char* s = malloc(WRITE_BUFFER_SIZE);
    const char* kind_str = weapon_kind_to_save_string(w.kind);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s.kind=%s\n"
             "%s.min_damages=%d\n"
             "%s.max_damages=%d\n"
             "%s.max_number_of_attacks_per_turn=%d"
             ,
             prefix, kind_str,
             prefix, w.min_damages,
             prefix, w.max_damages,
             prefix, w.max_number_of_attacks_per_turn
             );
    return s;
}

const char* weapon_kind_to_save_string(WeaponKind k) {
    char log[MAX_LINE_SIZE];
    switch (k) {
        case EMPTY_WEAPON: return "EMPTY_WEAPON";
        case SWORD: return "SWORD";
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown WeaponKind [%d]", k);
            log_error(log);
            return "Unknown WeaponKind";;
    }
}

char* armor_to_save_string_with_prefix(Armor a, const char* prefix) {
    char* s = malloc(WRITE_BUFFER_SIZE);
    const char* kind_str = armor_kind_to_save_string(a.kind);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s.kind=%s\n"
             "%s.defense=%d"
             ,
             prefix, kind_str,
             prefix, a.defense
    );
    return s;
}

const char* armor_kind_to_save_string(ArmorKind k) {
    char log[MAX_LINE_SIZE];
    switch (k) {
        case EMPTY_ARMOR: return "EMPTY_ARMOR";
        case CHEST_PLATE: return "CHEST_PLATE";
        default:
            snprintf(log, MAX_LINE_SIZE, "Unknown ArmorKind [%d]", k);
            log_error(log);
            return "Unknown ArmorKind";
    }
}

char* turn_to_save_string(uint8_t turn) {
    char* s = malloc(MAX_LINE_SIZE);
    snprintf(s, MAX_LINE_SIZE, "fight.turn=%d", turn);

    return s;
}

char* monsters_list_to_save_string(MonstersList m) {
    char* s = malloc(WRITE_BUFFER_SIZE);

    snprintf(s, WRITE_BUFFER_SIZE,
             "\n@MONSTERS@\n"
             "monsters_list.size=%d\n",m.size
    );
    for(int i = 0; i < m.size; i++) {
        char* monster_str = monster_to_save_string_at_index(m.monsters[i], i);
        strcat(s, monster_str);
        free(monster_str);
    }
    return s;
}

char* monster_to_save_string_at_index(Monster m, uint8_t index) {
    char prefix[MAX_LINE_SIZE];
    snprintf(prefix, MAX_LINE_SIZE, "monsters_list.monsters.%d", index);
    char* s = malloc(WRITE_BUFFER_SIZE);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s.health=%d\n"
             "%s.min_attack_power=%d\n"
             "%s.max_attack_power=%d\n"
             "%s.defense=%d\n"
             ,
             prefix, m.health,
             prefix, m.min_attack_power,
             prefix, m.max_attack_power,
             prefix, m.defense
             );
    return s;
}


char* potion_to_save_string_with_prefix(ManaPotion p, const char* prefix) {
    char* s = malloc(MAX_LINE_SIZE);
    snprintf(s, WRITE_BUFFER_SIZE,
             "%s.is_full=%d",
             prefix, p.is_full
    );
    return s;
}

const char* repository_status_to_string(RepositoryStatus status) {
    char log[64];
    switch (status) {
        case REPOSITORY_NOT_USED: return "REPOSITORY_NOT_USED";
        case RESTORE_LAST_GAME_SUCCEEDED: return "RESTORE_LAST_GAME_SUCCEEDED";
        case RESTORE_LAST_GAME_FAILED: return "RESTORE_LAST_GAME_FAILED";
        case SAVE_LAST_GAME_SUCCEEDED: return "SAVE_LAST_GAME_SUCCEEDED";
        case SAVE_LAST_GAME_FAILED: return "SAVE_LAST_GAME_FAILED";
        default:
            snprintf(log, 64, "Unknown RepositoryStatus [%d]", status);
            log_error(log);
            return "?";
    }
}

char* map_to_save_string(Map map) {
    char* s = malloc(WRITE_BUFFER_SIZE);

    snprintf(s, WRITE_BUFFER_SIZE, "MAP // TODO");

    return s;
}