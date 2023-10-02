
//
// Created by Theo OMNES on 02/10/2023.
//

#ifndef DOOMDEPTHS_CLI_CONTROLLERS_H
#define DOOMDEPTHS_CLI_CONTROLLERS_H

typedef struct Fight Fight;
typedef enum LeaveTownAction LeaveTownAction;


void open_grimoire_in_fight(Fight f);

void enter_player_inventory(Player p);

Position enter_map(Map m);

void fight();

void display_leave_town_actions();

LeaveTownAction get_leave_town_action();

#endif //DOOMDEPTHS_CLI_CONTROLLERS_H
