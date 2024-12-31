
//
// Created by Theo OMNES on 28/09/2023.
//

#include <stdint.h>
#include "stdbool.h"

#ifndef DOOMDEPTHS_POSITION_H
#define DOOMDEPTHS_POSITION_H


typedef struct Position Position;
struct Position {
    uint16_t zone_x;
    uint16_t zone_y;
};


Position no_position();

Position position(uint16_t x, uint16_t y);

char *position_to_string(Position);

Position up_from(Position);

Position down_from(Position);

Position left_from(Position);

Position right_from(Position);

bool positions_a_equals_b(Position a, Position b);

void log_position(Position p);

#endif //DOOMDEPTHS_POSITION_H
