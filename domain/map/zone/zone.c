
//
// Created by Theo OMNES on 28/09/2023.
//

#include <stdint.h>
#include <string.h>
#include "zone.h"
#include "stdlib.h"

Zone _zone(ZoneStatus status, Fight fight) {
    Zone z;
    z.status = status;
    z.fight = fight;
    return z;
}

Zone empty_zone() {
    return _zone(ZONE_EMPTY, empty_fight());
}

Zone not_discovered_zone() {
    return _zone(ZONE_NOT_DISCOVERED, empty_fight());
}

bool zone_is_empty(Zone zone) {
    return zone.status == ZONE_EMPTY;
}

Zone **free_zones(Zone **zones, uint16_t height, uint16_t width) {
    if (zones == NULL) return zones;
    for (int row = 0; row < height; row++) {
        if (zones[row] == NULL) continue;
        for (int col = 0; col < width; col++) {
            Zone z = zones[row][col];
            z.fight = free_fight(z.fight);
        }
        free(zones[row]);
        zones[row] = NULL;
    }
    free(zones);
    zones = NULL;
    return zones;
}

Zone set_zone_status(Zone zone, ZoneStatus status) {
    zone.status = status;
    return zone;
}