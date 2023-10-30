project(DoomDepthsApplication C)

add_library(APPLICATION
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

target_include_directories(APPLICATION PUBLIC ".")

target_link_libraries(APPLICATION DOMAIN)
target_link_libraries(APPLICATION UTILS)