
//
// Created by Theo OMNES on 13/10/2023.
//

#ifndef DOOMDEPTHS_PAGES_H
#define DOOMDEPTHS_PAGES_H

#include "pages/town/sdl_town_controller.h"
#include "pages/map/sdl_map_page.h"
#include "pages/fight/sdl_fight_page.h"

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
