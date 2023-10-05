
//
// Created by Theo OMNES on 02/10/2023.
//

#include <port/in/query/is_player_alive.h>
#include <domain/fight/fight.h>
#include <port/out/persistence/intern_game_state/get_current_player.h>

bool current_player_is_alive() {
    return get_current_player().current_health > 0;
}