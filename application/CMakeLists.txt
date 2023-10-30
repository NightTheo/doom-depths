project(DoomDepthsApplication C)

get_filename_component(PARENT_DIR ../ ABSOLUTE)

add_library(APPLICATION
        port/in/command/new_run.h
        port/out/persistence/storage/restore_last_game.h
        port/out/persistence/intern_game_state/game_state.h
        port/out/persistence/storage/save_game_state.h
        port/out/persistence/storage/respository_status.c
        port/out/persistence/storage/respository_status.h
        service/command/new_run.c
        port/out/log/log_info.h
        port/out/log/log_error.h
        port/out/log/log_monster.h
        port/out/log/log_player.h
        port/out/log/log_grimoire.h
        port/out/log/log_repository_status.h
        port/out/ihm/display_loot.h
        port/out/ihm/display_game_over.h
        port/in/command/continue_last_run.h
        service/command/continue_last_run.c
        port/in/command/attack_with_weapon.h
        service/command/player_use_weapon.c
        port/in/command/end_round.h
        service/command/end_round.c
        port/in/command/cast_spell.h
        service/command/cast_spell.c
        service/command/drink_potion.c
        port/in/command/drink_potion.h
        service/command/equip_item.c
        port/in/command/equip_item.h
        port/in/command/start_ihm.h
        port/out/persistence/intern_game_state/set_intern_game_state.h
        port/out/persistence/intern_game_state/get_intern_game_state.h
        service/command/player_enter_zone.c
        port/in/command/player_enter_zone.h
        port/out/persistence/intern_game_state/get_map.h
        service/command/leave_town.c
        port/in/command/leave_town.h
        port/in/query/is_current_fight_finished.h
        port/out/persistence/intern_game_state/set_current_fight.h
        port/in/query/is_player_alive.h
        service/query/is_player_alive.c
        service/command/finish_current_zone.c
        port/out/persistence/intern_game_state/get_current_zone.h
        port/out/persistence/intern_game_state/set_current_map.h
        port/in/command/finish_current_zone.h
        service/query/is_current_fight_finished.c
        service/query/is_current_round_finished.c
        port/in/query/is_current_round_finished.h
        service/command/start_new_round.c
        port/in/command/start_new_round.h
        port/out/persistence/intern_game_state/set_player.h
        service/event/player_killed_monster.c
        port/out/persistence/intern_game_state/get_player.h
)

target_include_directories(APPLICATION PRIVATE ".")

target_link_libraries(APPLICATION DOMAIN)
target_link_libraries(APPLICATION UTILS)