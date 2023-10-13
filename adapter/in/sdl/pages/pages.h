
//
// Created by Theo OMNES on 13/10/2023.
//

#ifndef DOOMDEPTHS_PAGES_H
#define DOOMDEPTHS_PAGES_H

#include "in/sdl/pages/town/sdl_town_controller.h"
#include "in/sdl/pages/map/sdl_map_page.h"
#include "in/sdl/pages/fight/sdl_fight_page.h"

typedef enum CurrentPage {
    TOWN_PAGE,
    MAP_PAGE,
    FIGHT_PAGE,
} CurrentPage;

typedef union Page {
    TownWindow town;
    MapPage map;
    FightPage fight;
} Page;

#endif //DOOMDEPTHS_PAGES_H
