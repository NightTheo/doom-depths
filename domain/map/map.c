
//
// Created by Theo OMNES on 28/09/2023.
//

#include <string.h>
#include <stdio.h>
#include "map.h"
#include "../../infrastructure/utils/log/log.h"

Map _map(uint16_t height, uint16_t width, Position playerPosition, Zone **zones) {
    char log[64];
    if (zones == NULL) {
        log_error("Invalid argument : zones are NULL");
        return empty_map();
    }

    if (height < 1 || width < 1) {
        log_error("Invalid argument : height and width should be greater or equal to 1.");
        return empty_map();
    }
    bool player_position_is_in_map = playerPosition.zone_x >= 0
                                     && playerPosition.zone_x < width
                                     && playerPosition.zone_y >= 0
                                     && playerPosition.zone_y < height;
    if (player_position_is_in_map == false) {
        log_error("Player position is not in map");
        return empty_map();
    }

    Zone *row = zones[playerPosition.zone_y];
    if (row == NULL || zone_is_empty(row[playerPosition.zone_x])) {
        snprintf(log, 64, "Zone [x:%d,y:%d] NULL or empty", playerPosition.zone_x, playerPosition.zone_y);
        log_error(log);
        return empty_map();
    }

    Map m;
    m.player_position = playerPosition;
    m.height = height;
    m.width = width;
    m.zones = zones;
    return m;
}

Map empty_map() {
    Map m;
    m.height = 0;
    m.width = 0;
    m.player_position = no_position();
    m.zones = NULL;
    return m;
}

bool map_is_empty(Map m) {
    return m.width == 0 || m.height == 0 || m.zones == NULL;
}

Map basic_map() {
    uint8_t height = 3;
    uint8_t width = 3;
    Position playerPosition = position(1, 1);
    return _map(height, width, playerPosition, basic_map_zones(height, width));
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
    map.zones = NULL;
}

bool position_is_in_map_and_not_empty(Position p, Map m){
    bool is_not_in_map_or_is_empty = position_is_in_map(p, m) == false
                                    || zone_is_empty(m.zones[p.zone_y][p.zone_x]);
    if(is_not_in_map_or_is_empty) {
        char log[64];
        snprintf(log, 64, "Zone [x:%d,y:%d] is empty", p.zone_x, p.zone_y);
        log_info(log);
        return false;
    }
    return true;
}

bool position_is_in_map(Position p, Map m){
    bool player_position_is_in_map = p.zone_x >= 0
                                     && p.zone_x < m.width
                                     && p.zone_y >= 0
                                     && p.zone_y < m.height;
    if (player_position_is_in_map == false) {
        log_info("Player position is not in map");
        return false;
    }

    char log[64];
    if(m.zones[p.zone_y] == NULL) {
        snprintf(log, 64, "Map row [%d] is NULL", p.zone_y);
        log_error(log);
        return false;
    }
    return true;
}


Map spawn_player_on_map_at_position(Player player, Map m, Position position) {
    if(position_is_in_map_and_not_empty(position, m) == false) {
        return m;
    }

    m.player_position = position;
    Zone z = m.zones[position.zone_y][position.zone_x];
    z.fight.player = player;
    // TODO init fight (monsters by zone);
    m.zones[position.zone_y][position.zone_x] = z;
    return m;
}

Zone get_zone_in_map_by_position(Map map, Position position) {
    if(position_is_in_map(position, map) == false) {
        return empty_zone();
    }
    return map.zones[position.zone_y][position.zone_x];
}


Zone get_zone_of_player_current_zone_in_map(Map m) {
    return get_zone_in_map_by_position(m, m.player_position);
}