
//
// Created by Theo OMNES on 28/09/2023.
//

#ifndef DOOMDEPTHS_MAP_H
#define DOOMDEPTHS_MAP_H

#include "stdbool.h"
#include <domain/map/zone/zone.h>
#include "stdint.h"
#include <domain/map/position/position.h>

typedef struct Map Map;
struct Map {
    Position spawn;
    uint16_t height;
    uint16_t width;
    Zone **zones;
};

Map _map(uint16_t height, uint16_t width, Position spawn, Zone **zones);

Map basic_map();

Map empty_map();

bool map_is_empty(Map m);

Zone **basic_map_zones(uint8_t height, uint8_t width);

void free_map(Map map);

Map spawn_player_on_map_at_position(Player, Map, Position);

bool position_is_in_map(Position p, Map m);

bool position_is_in_map_and_not_empty(Position p, Map m);

Zone get_zone_in_map_by_position(Map map, Position position);

Map set_zone_in_map_by_position(Zone zone, Map map, Position position);

Zone get_player_current_zone_in_map(Map m);

bool position_is_finished(Position p, Map m);

bool player_can_move_to_position_in_map(Position, Map);

#endif //DOOMDEPTHS_MAP_H
