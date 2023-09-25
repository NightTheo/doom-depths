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
        fight/player_fight_action/player_fight_action.c
        fight/loot/loot.c
        fight/loot/loot.h
        fight/weapon/weapon.c
        player/inventory/inventory.c
        player/inventory/inventory.h
        ihm/cli/inventory_cli/inventory_cli.c
        ihm/cli/inventory_cli/inventory_cli.h
        player/inventory/player_inventory_action/player_inventory_actions.c
        player/inventory/player_inventory_action/player_inventory_actions.h
        player/equipment/equipment.c
        player/equipment/equipment.h)
