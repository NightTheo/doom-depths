
//
// Created by Theo OMNES on 28/09/2023.
//

#include "position.h"

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