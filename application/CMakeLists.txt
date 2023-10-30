project(DoomDepthsApplication C)


add_library(APPLICATION
        port/out/log/log_info.h
        port/out/log/log_error.h
        port/out/log/log_monster.h
        port/out/log/log_player.h
        port/out/log/log_grimoire.h
        port/out/log/log_repository_status.h
        port/out/ihm/display_loot.h
        port/out/ihm/display_game_over.h
        port/out/persistence/storage/restore_last_game.h
        port/out/persistence/storage/save_game_state.h
        port/out/persistence/storage/respository_status.c
        port/out/persistence/storage/respository_status.h
        port/out/persistence/intern_game_state/game_state.h
        port/out/persistence/intern_game_state/set_intern_game_state.h
        port/out/persistence/intern_game_state/get_intern_game_state.h
        port/out/persistence/intern_game_state/get_map.h
        port/out/persistence/intern_game_state/set_current_fight.h
        port/out/persistence/intern_game_state/get_current_zone.h
        port/out/persistence/intern_game_state/set_current_map.h
        port/out/persistence/intern_game_state/get_player.h
        port/out/persistence/intern_game_state/set_player.h

        port/in/command/continue_last_run.h
        port/in/command/new_run.h
        port/in/command/attack_with_weapon.h
        port/in/command/end_round.h
        port/in/command/cast_spell.h
        port/in/command/drink_potion.h
        port/in/command/equip_item.h
        port/in/command/start_ihm.h
        port/in/command/player_enter_zone.h
        port/in/command/leave_town.h
        port/in/command/finish_current_zone.h
        port/in/command/start_new_round.h
        port/in/query/is_current_fight_finished.h
        port/in/query/is_player_alive.h
        port/in/query/is_current_round_finished.h

        service/command/new_run.c
        service/command/continue_last_run.c
        service/command/player_use_weapon.c
        service/command/end_round.c
        service/command/cast_spell.c
        service/command/drink_potion.c
        service/command/equip_item.c
        service/command/player_enter_zone.c
        service/command/leave_town.c
        service/command/finish_current_zone.c
        service/command/start_new_round.c
        service/query/is_player_alive.c
        service/query/is_current_fight_finished.c
        service/query/is_current_round_finished.c
        service/event/player_killed_monster.c
)

target_include_directories(APPLICATION PRIVATE ".")

target_link_libraries(APPLICATION DOMAIN)
target_link_libraries(APPLICATION UTILS)