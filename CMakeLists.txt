cmake_minimum_required(VERSION 3.26)
project(DoomDepths C)

set(CMAKE_C_STANDARD 23)

add_executable(DoomDepths main.c
        adapter/out/log/cli_log.c
        infrastructure/utils/utils.c
        domain/monsters/monsters.c
        infrastructure/utils/random/random.c
        domain/player/player.c
        domain/fight/fight.c
        ihm/cli/cli_ihm.c
        domain/fight/player_fight_action/player_fight_action.c
        domain/fight/loot/loot.c
        domain/fight/weapon/weapon.c
        domain/player/inventory/inventory.c
        ihm/cli/inventory_cli/inventory_cli.c
        domain/player/inventory/player_inventory_action/player_inventory_actions.c
        domain/player/equipment/equipment.c
        domain/fight/armor/armor.c
        domain/magic/spell/spell.c
        domain/magic/mana_potion/mana_potion.c
        domain/magic/grimoire/grimoire.c
        ihm/cli/grimoire_cli/grimoire_cli.c
        domain/map/map.c
        domain/map/map.h
        domain/map/zone/zone.c
        domain/map/zone/zone.h
        domain/map/position/position.c
        domain/map/position/position.h
        ihm/cli/map_cli/map_cli.c
        domain/doom_detpths/doom_depths.c
        domain/doom_detpths/doom_depths.h
        infrastructure/utils/time/time_util.c
        infrastructure/utils/time/time_util.h
        application/port/in/new_game.h
        application/port/out/persistence/restore_last_game.h
        application/port/out/persistence/game_state.h
        application/port/out/persistence/save_game_state.h
        application/port/out/persistence/repository_status/respository_status.c
        application/port/out/persistence/repository_status/respository_status.h
        adapter/out/custom_file_repository/restore_last_game.c
        adapter/out/custom_file_repository/save_game_state.c
        application/service/new_game.c
        application/port/in/start_fight.h
        application/service/start_fight.c
        application/port/out/log/log_info.h
        application/port/out/log/log_error.h
        application/port/out/log/log_monster.h
        application/port/out/log/log_player.h
        application/port/out/log/log_grimoire.h
        application/port/out/log/log_repository_status.h
)
