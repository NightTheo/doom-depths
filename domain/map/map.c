
//
// Created by Theo OMNES on 28/09/2023.
//

#include <string.h>
#include "map.h"
#include <log_error.h>
#include <log_info.h>
#include <random/random.h>

Map _map(uint16_t height, uint16_t width, Position spawn, Zone **zones) {
    if (zones == NULL) {
        log_error("Invalid argument : zones are NULL");
        return empty_map();
    }

    if (height < 1 || width < 1) {
        log_error("Invalid argument : height and width should be greater or equal to 1.");
        return empty_map();
    }

    Zone *row = zones[spawn.zone_y];
    if (row == NULL || zone_is_empty(row[spawn.zone_x])) {
        log_error("Zone [x:%d,y:%d] NULL or empty", spawn.zone_x, spawn.zone_y);
        return empty_map();
    }

    Map m;
    m.spawn = spawn;
    m.height = height;
    m.width = width;
    m.zones = zones;

    if (!position_is_in_map_and_not_empty(spawn, m)) {
        log_error("Bad Spawn.");
        return empty_map();
    }

    return m;
}

Map empty_map() {
    Map m;
    m.height = 0;
    m.width = 0;
    m.spawn = no_position();
    m.zones = NULL;
    return m;
}

bool map_is_empty(Map m) {
    return m.width == 0 || m.height == 0 || m.zones == NULL;
}

Map basic_map() {
    uint8_t height = 3;
    uint8_t width = 3;
    Position spawn = position(2, 0);
    return _map(height, width, spawn, basic_map_zones(height, width));
}

Zone **basic_map_zones(uint8_t height, uint8_t width) {
    Zone **rows = malloc(sizeof(Zone *) * height);
    if (rows == NULL) {
        log_allocation_error();
        return NULL;
    }
    Zone zones[3][3] = {
            {empty_zone(),          empty_zone(),          not_discovered_zone()},
            {not_discovered_zone(), not_discovered_zone(), not_discovered_zone()},
            {not_discovered_zone(), empty_zone(),          empty_zone()},
    };
    for (int y = 0; y < height; y++) {
        rows[y] = NULL;
    }
    for (int y = 0; y < height; y++) {
        rows[y] = malloc(sizeof(Zone) * width);
        if (rows[y] == NULL) {
            log_allocation_error();
            free_zones(rows, height, width);
            return NULL;
        }
        for (int x = 0; x < width; x++) {
            rows[y][x] = zones[y][x];
        }
    }
    return rows;
}

void free_map(Map map) {
    free_zones(map.zones, map.height, map.width);
}

bool position_is_in_map_and_not_empty(Position p, Map m) {
    bool is_not_in_map_or_is_empty = position_is_in_map(p, m) == false
                                     || zone_is_empty(m.zones[p.zone_y][p.zone_x]);
    if (is_not_in_map_or_is_empty) {
        return false;
    }
    return true;
}

bool position_is_in_map(Position p, Map m) {
    bool player_position_is_in_map = p.zone_x >= 0
                                     && p.zone_x < m.width
                                     && p.zone_y >= 0
                                     && p.zone_y < m.height;

    if (player_position_is_in_map == false) return false;
    if (m.zones[p.zone_y] == NULL) {
        log_error("Map row [%d] is NULL", p.zone_y);
        return false;
    }
    return true;
}


Map spawn_player_on_map_at_position(Player player, Map m, Position position) {
    if (position_is_in_map_and_not_empty(position, m) == false) {
        return m;
    }

    Position old_position = m.spawn;

    m.spawn = position;
    Zone z = m.zones[position.zone_y][position.zone_x];
    if (!positions_a_equals_b(old_position, position)) {
        free_fight(z.fight);
    }
    z.fight.player = restore_player_number_of_remaining_attacks(player);
    z.fight.monsters_list = random_list_of_monsters(random_between_included(2, 5));
    z.fight.turn = 0;
    m.zones[position.zone_y][position.zone_x] = z;
    return m;
}

Zone get_zone_in_map_by_position(Map map, Position position) {
    if (position_is_in_map(position, map) == false) {
        return empty_zone();
    }
    return map.zones[position.zone_y][position.zone_x];
}

Map set_zone_in_map_by_position(Zone zone, Map map, Position position) {
    if (position_is_in_map(position, map) == false) {
        return empty_map();
    }
    map.zones[position.zone_y][position.zone_x] = zone;
    return map;
}


Zone get_player_current_zone_in_map(Map m) {
    return get_zone_in_map_by_position(m, m.spawn);
}

bool position_is_finished(Position p, Map m) {
    return get_zone_in_map_by_position(m, p).status == ZONE_FINISHED;
}

bool player_can_move_to_position_in_map(Position p, Map m) {
    if (position_is_in_map_and_not_empty(p, m) == false) return false;
    if (position_is_finished(p, m)) return false;
    if (positions_a_equals_b(m.spawn, p)) return true;

    bool player_can_move = position_is_finished(up_from(p), m)
                           || position_is_finished(down_from(p), m)
                           || position_is_finished(right_from(p), m)
                           || position_is_finished(left_from(p), m);

    if (player_can_move == false) {
        char *position_str = position_to_string(p);
        log_info("Player cannot move to %s.", position_str);
        free(position_str);
    }
    return player_can_move;
}