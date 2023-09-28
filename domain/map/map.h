
//
// Created by Theo OMNES on 28/09/2023.
//

#ifndef DOOMDEPTHS_MAP_H
#define DOOMDEPTHS_MAP_H

#include "zone/zone.h"
#include "stdint.h"
#include "position/position.h"
#include "stdbool.h"

typedef struct Map Map;
struct Map {
    Position playerPosition;
    uint16_t height;
    uint16_t width;
    Zone** zones;
};

Map _map(uint16_t height, uint16_t width, Position playerPosition, Zone **zones);
Map basic_map();
Zone** basic_map_zones(uint8_t height, uint8_t width);
void free_map(Map map);
Map spawn_player_on_map_at_position(Player, Map, Position);
bool position_is_in_map(Position p, Map m);
bool position_is_in_map_and_not_empty(Position p, Map m);
Zone get_zone_in_map_by_position(Map map, Position position);

#endif //DOOMDEPTHS_MAP_H
