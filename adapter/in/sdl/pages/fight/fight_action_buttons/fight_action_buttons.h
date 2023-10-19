
//
// Created by Theo OMNES on 19/10/2023.
//

#ifndef DOOMDEPTHS_FIGHT_ACTION_BUTTONS_H
#define DOOMDEPTHS_FIGHT_ACTION_BUTTONS_H

#include "in/sdl/components/button/button.h"
#include "in/sdl/components/row/row.h"
#include "in/sdl/pages/fight/sdl_fight_page.h"

Button fill_attack_button(SDL_IHM ihm, ButtonSize size);

Button fill_end_turn_button(SDL_IHM ihm, ButtonSize size);

Button fill_potion_button(SDL_IHM ihm, ButtonSize size);

void draw_action_buttons(SDL_Renderer *renderer, SDL_IHM ihm);

Row update_style_of_fight_action_buttons(FightPage fight);

SDL_IHM fight_action_buttons_handle_event(SDL_Event event, SDL_IHM ihm);


#endif //DOOMDEPTHS_FIGHT_ACTION_BUTTONS_H
