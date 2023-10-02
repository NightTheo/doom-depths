
//
// Created by Theo OMNES on 02/10/2023.
//

#include "../../../domain/map/map.h"
#include "../../port/out/persistence/intern_game_state/get_current_zone.h"
#include "../../port/out/persistence/intern_game_state/get_map.h"
#include "../../port/out/persistence/intern_game_state/set_current_map.h"

Map finish_current_zone() {
    Map map = get_map();
    Zone zone = set_zone_status(get_player_current_zone_in_map(map), ZONE_FINISHED);
    map = set_zone_in_map_by_position(zone, map, map.spawn);
    return set_current_map(map);
}