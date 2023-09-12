cmake_minimum_required(VERSION 3.26)
project(DoomDepths C)

set(CMAKE_C_STANDARD 23)

add_executable(DoomDepths main.c
        monsters/monsters.c
        random/random.c
        player/player.c
        fight/fight.c)
