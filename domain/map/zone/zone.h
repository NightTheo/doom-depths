
//
// Created by Theo OMNES on 28/09/2023.
//

#ifndef DOOMDEPTHS_ZONE_H
#define DOOMDEPTHS_ZONE_H

#include "stdbool.h"
#include "stdint.h"
#include "../../fight/fight.h"

typedef enum ZoneStatus ZoneStatus;
enum ZoneStatus {
    ZONE_EMPTY,
    NOT_DISCOVERED,
    DISCOVERED,
};

typedef struct Zone Zone;
struct Zone {
    ZoneStatus status;
    Fight fight;
};

Zone _zone(ZoneStatus status, Fight fight);
Zone empty_zone();
bool zone_is_empty(Zone zone);
Zone not_discovered_zone();
void free_zones(Zone** zones, uint16_t height, uint16_t width);

#endif //DOOMDEPTHS_ZONE_H
