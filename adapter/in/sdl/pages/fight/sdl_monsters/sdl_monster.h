
//
// Created by Theo OMNES on 22/10/2023.
//

#ifndef DOOMDEPTHS_SDL_MONSTER_H
#define DOOMDEPTHS_SDL_MONSTER_H

#include "domain/monsters/monsters.h"
#include "in/sdl/components/animation/animation.h"
#include "in/sdl/pages/fight/health_bar/health_bar.h"
#include "in/sdl/components/row/row.h"

typedef struct {
    Animation animation;
    HealthBar health_bar;
} SdlMonster;

typedef struct {
    MonstersList monsters_list;
    SdlMonster *monsters;
    Row row_monsters;
} SdlMonsters;

SdlMonsters fill_fight_monsters(SDL_Renderer *renderer, MonstersList monsters_list);

SdlMonsters update_fight_monsters(SdlMonsters monsters, MonstersList monsters_list);

void draw_monsters(SDL_Renderer *renderer, SdlMonsters monsters, TTF_Font *font);


#endif //DOOMDEPTHS_SDL_MONSTER_H

