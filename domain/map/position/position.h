
//
// Created by Theo OMNES on 28/09/2023.
//

#include <stdint.h>

#ifndef DOOMDEPTHS_POSITION_H
#define DOOMDEPTHS_POSITION_H


typedef struct Position Position;
struct Position {
    uint16_t zone_x;
    uint16_t zone_y;
};


Position no_position();
Position position(uint16_t x, uint16_t y);


#endif //DOOMDEPTHS_POSITION_H
