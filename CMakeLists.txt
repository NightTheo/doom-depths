cmake_minimum_required(VERSION 3.26)
project(DoomDepths C)

set(CMAKE_C_STANDARD 23)

add_executable(DoomDepths main.c
        infrastructure/utils/log/log.c
        infrastructure/utils/utils.c
        domain/monsters/monsters.c
        infrastructure/utils/random/random.c
        domain/player/player.c
        domain/fight/fight.c
        ihm/cli/cli_ihm.c
        domain/fight/player_fight_action/player_fight_action.c
        domain/fight/loot/loot.c
        domain/fight/loot/loot.h
        domain/fight/weapon/weapon.c
        domain/player/inventory/inventory.c
        domain/player/inventory/inventory.h
        ihm/cli/inventory_cli/inventory_cli.c
        ihm/cli/inventory_cli/inventory_cli.h
        domain/player/inventory/player_inventory_action/player_inventory_actions.c
        domain/player/inventory/player_inventory_action/player_inventory_actions.h
        domain/player/equipment/equipment.c
        domain/player/equipment/equipment.h
        domain/fight/armor/armor.c
        domain/fight/armor/armor.h
        domain/repository.h
        domain/repository.h
        infrastructure/repository/custom_file_repository.c)
