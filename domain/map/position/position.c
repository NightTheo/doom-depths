
//
// Created by Theo OMNES on 28/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "position.h"
#include "../../../infrastructure/utils/log/log.h"

Position no_position() {
    Position pp;
    pp.zone_x = -1;
    pp.zone_y = -1;
    return pp;
}

Position position(uint16_t x, uint16_t y) {
    Position p;
    p.zone_y = y;
    p.zone_x = x;
    return p;
}

char* position_to_string(Position p) {
    char* s = malloc(64);
    if(s == NULL) {
        log_allocation_error();
        return NULL;
    }
    snprintf(s, 64, "Position {x: %d, y: %d}", p.zone_x, p.zone_y);
    return s;
}