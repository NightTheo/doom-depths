
//
// Created by Theo OMNES on 10/10/2023.
//

#ifndef DOOMDEPTHS_SDL_ZONE_H
#define DOOMDEPTHS_SDL_ZONE_H

#include "map/zone/zone.h"
#include "in/sdl/components/button/button.h"
#include "map/map.h"

typedef struct {
    Zone zone;
    Button button;
    Position position;
} SdlZone;

SdlZone style_zone(SdlZone zone, Map map);

#endif //DOOMDEPTHS_SDL_ZONE_H
