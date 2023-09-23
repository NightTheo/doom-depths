cmake_minimum_required(VERSION 3.26)
project(DoomDepths C)

set(CMAKE_C_STANDARD 23)

add_executable(DoomDepths main.c
        utils/log/log.c
        utils/utils.c
        monsters/monsters.c
        utils/random/random.c
        player/player.c
        fight/fight.c
        ihm/cli/cli_ihm.c
        player/player_action/player_action.c)
