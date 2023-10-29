
//
// Created by Theo OMNES on 22/10/2023.
//

#include <SDL_image.h>
#include "sdl_monster.h"
#include "port/out/log/log_error.h"
#include "port/out/log/log_info.h"


SpriteSheet monster_sprite_sheet(SDL_Renderer *renderer);

SdlMonsters fill_fight_monsters(SDL_Renderer *renderer, MonstersList monsters_list) {

    SdlMonster *monsters = malloc(sizeof(SdlMonster) * monsters_list.size);
    int sprite_size = 130;
    int sprite_size_in_screen = sprite_size;
    SpriteSheet sprite_sheet = monster_sprite_sheet(renderer);
    Animation animation = {
            .sprite_rect = (SDL_Rect) {.w = sprite_size, .h = sprite_size, .x = 0, .y = 0},
            .screen_rect = (SDL_Rect) {.w = sprite_size_in_screen, .h = sprite_size_in_screen, .x = 10, .y = 300},
            .current_frame = 0,
            .number_of_frames = sprite_sheet.columns * sprite_sheet.rows,
            .start_frame = 0,
            .sprite_sheet = sprite_sheet,
            .fps = 10,
    };
    int offset = 0;
    for(int i = 0; i < monsters_list.size; i++) {
        HealthBar health_bar = create_health_bar(
                monsters_list.monsters[i].health,
                get_color(SDL_RED),
                (SDL_Rect ){}
        );
        monsters[i] = (SdlMonster) {
                .animation = animation,
                .health_bar = health_bar,
        };
        offset = 10;
    }

    SdlMonsters sdl_monsters = {
            .monsters_list = monsters_list,
            .monsters = monsters,
    };

    return sdl_monsters;
}

SpriteSheet monster_sprite_sheet(SDL_Renderer *renderer) {
    SpriteSheet sprite_sheet = {
            .texture = IMG_LoadTexture(renderer, "resources/assets/cat.png"),
            .rows = 11,
            .columns = 5,
    };
    if(sprite_sheet.texture == NULL) {
        log_error("IMG_LoadTexture Error: %s.", IMG_GetError());
        return sprite_sheet;
    }
    return sprite_sheet;
}


SdlMonsters update_fight_monsters(SdlMonsters monsters, MonstersList monsters_list) {
    for(int i = 0; i < monsters_list.size; i++) {
        monsters.monsters[i].health_bar.current_health = monsters_list.monsters[i].health;
    }
    monsters.monsters_list = monsters_list;
    return monsters;
}

void draw_monsters(SDL_Renderer *renderer, SdlMonsters monsters, TTF_Font *font) {
    uint8_t offset = 10;
    for(int i = 0; i < monsters.monsters_list.size; i++) {
        Animation animation = monsters.monsters[i].animation;
        animation.screen_rect.x += i * animation.screen_rect.w + i * offset;
        SDL_RenderCopy(
                renderer,
                animation.sprite_sheet.texture,
                &animation.sprite_rect,
                &animation.screen_rect
        );
        monsters.monsters[i].health_bar.rect = (SDL_Rect){
                .w = animation.screen_rect.w,
                .h = 15,
                .x = animation.screen_rect.x,
                .y = animation.screen_rect.y + animation.screen_rect.h,
        };
        draw_health_bar(renderer, monsters.monsters[i].health_bar, font);
    }
}