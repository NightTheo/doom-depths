
//
// Created by Theo OMNES on 28/09/2023.
//

#ifndef DOOMDEPTHS_ZONE_H
#define DOOMDEPTHS_ZONE_H

#include "stdbool.h"
#include "stdint.h"
#include <fight.h>

typedef enum ZoneStatus ZoneStatus;
enum ZoneStatus {
    ZONE_EMPTY,
    ZONE_NOT_DISCOVERED,
    ZONE_FINISHED,
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

Zone **free_zones(Zone **zones, uint16_t height, uint16_t width);

Zone set_zone_status(Zone zone, ZoneStatus status);

#endif //DOOMDEPTHS_ZONE_H
