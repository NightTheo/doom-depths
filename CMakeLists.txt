cmake_minimum_required(VERSION 3.26)
set(CMAKE_C_STANDARD 23)
project(DoomDepths C)

execute_process( COMMAND /bin/bash -c "conan install ${CMAKE_SOURCE_DIR} --build=missing" )

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/build/Release/generators/conan_toolchain.cmake")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_COMPILER_VERSION 15)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)


add_subdirectory("domain")
add_subdirectory("utils")
include_directories(
        "${PROJECT_SOURCE_DIR}/application"
        "${PROJECT_SOURCE_DIR}/adapter"
        "${PROJECT_SOURCE_DIR}/application/port/out/log"
)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(DoomDepths main.c
        adapter/out/log/cli_log.c
        adapter/in/cli/cli_grimoire_controller.c
        adapter/in/cli/cli_map_controller.c
        application/port/in/command/new_run.h
        application/port/out/persistence/storage/restore_last_game.h
        application/port/out/persistence/intern_game_state/game_state.h
        application/port/out/persistence/storage/save_game_state.h
        application/port/out/persistence/storage/respository_status.c
        application/port/out/persistence/storage/respository_status.h
        adapter/out/custom_file_repository/restore_last_game.c
        adapter/out/custom_file_repository/save_game_state.c
        application/service/command/new_run.c
        application/port/out/log/log_info.h
        application/port/out/log/log_error.h
        application/port/out/log/log_monster.h
        application/port/out/log/log_player.h
        application/port/out/log/log_grimoire.h
        application/port/out/log/log_repository_status.h
        application/port/out/ihm/display_loot.h
        adapter/out/ihm/cli/cli_display_loot.c
        adapter/in/cli/cli_inventory_controller.c
        application/port/out/ihm/display_game_over.h
        adapter/out/ihm/cli/cli_display_game_over.c
        adapter/in/cli/cli_fight_controller.c
        application/port/in/command/continue_last_run.h
        application/service/command/continue_last_run.c
        application/port/in/command/attack_with_weapon.h
        application/service/command/player_use_weapon.c
        application/port/in/command/end_round.h
        application/service/command/end_round.c
        application/port/in/command/cast_spell.h
        application/service/command/cast_spell.c
        application/service/command/drink_potion.c
        application/port/in/command/drink_potion.h
        application/service/command/equip_item.c
        application/port/in/command/equip_item.h
        application/port/in/command/start_ihm.h
        adapter/out/in_memory_intern_game_state/in_memory_intern_game_state.c
        application/port/out/persistence/intern_game_state/set_intern_game_state.h
        application/port/out/persistence/intern_game_state/get_intern_game_state.h
        application/service/command/player_enter_zone.c
        application/port/in/command/player_enter_zone.h
        application/port/out/persistence/intern_game_state/get_map.h
        application/service/command/leave_town.c
        application/port/in/command/leave_town.h
        application/port/in/query/is_current_fight_finished.h
        application/port/out/persistence/intern_game_state/set_current_fight.h
        application/port/in/query/is_player_alive.h
        application/service/query/is_player_alive.c
        application/service/command/finish_current_zone.c
        application/port/out/persistence/intern_game_state/get_current_zone.h
        application/port/out/persistence/intern_game_state/set_current_map.h
        application/port/in/command/finish_current_zone.h
        application/service/query/is_current_fight_finished.c
        application/service/query/is_current_round_finished.c
        application/port/in/query/is_current_round_finished.h
        application/service/command/start_new_round.c
        application/port/in/command/start_new_round.h
        adapter/in/cli/cli_controllers.h
        application/port/out/persistence/intern_game_state/set_player.h
        adapter/in/cli/cli_town_controller.c
        application/service/event/player_killed_monster.c
        application/port/out/persistence/intern_game_state/get_player.h
        adapter/in/sdl/pages/town/sdl_town_controller.c
        adapter/in/sdl/sdl_controller.h
        adapter/in/sdl/pages/town/sdl_town_controller.h
        adapter/in/sdl/components/button/button.c
        adapter/in/sdl/components/button/button.h
        adapter/in/sdl/components/padding/padding.c
        adapter/in/sdl/components/padding/padding.h
        adapter/in/sdl/components/point/point.h
        adapter/in/sdl/components/color/sdl_color.h
        adapter/in/sdl/components/color/sdl_color.c
        adapter/in/sdl/components/button/button_events/button_events.h
        adapter/in/sdl/pages/map/sdl_map_page.c
        adapter/in/sdl/pages/map/sdl_map_page.h
        adapter/in/sdl/pages/map/zone/sdl_zone.c
        adapter/in/sdl/pages/map/zone/sdl_zone.h
        adapter/in/sdl/components/button/button_size/button_size.c
        adapter/in/sdl/components/button/button_size/button_size.h
        adapter/in/sdl/components/button/button_callback/button_callback.c
        adapter/in/sdl/components/button/button_callback/button_callback.h
        adapter/in/sdl/pages/fight/sdl_fight_page.c
        adapter/in/sdl/pages/fight/sdl_fight_page.h
        adapter/in/sdl/pages/pages.h
        adapter/in/sdl/pages/fight/health_bar/health_bar.c
        adapter/in/sdl/pages/fight/health_bar/health_bar.h
        adapter/in/sdl/components/button/button_events/button_events.c
        adapter/in/sdl/components/screen_position/screen_position.c
        adapter/in/sdl/components/screen_position/screen_position.h
        adapter/in/sdl/components/row/row.c
        adapter/in/sdl/components/row/row.h
        adapter/in/sdl/components/sprite_sheet/sprite_sheet.c
        adapter/in/sdl/components/sprite_sheet/sprite_sheet.h
        adapter/in/sdl/components/animation/animation.c
        adapter/in/sdl/components/animation/animation.h
        adapter/in/sdl/pages/fight/sdl_player/sdl_player.c
        adapter/in/sdl/pages/fight/sdl_player/sdl_player.h
        adapter/in/sdl/pages/fight/fight_action_buttons/fight_action_buttons.c
        adapter/in/sdl/pages/fight/fight_action_buttons/fight_action_buttons.h
        adapter/in/sdl/components/event/event.c
        adapter/in/sdl/components/event/event.h
        adapter/in/sdl/components/aria/aria.c
        adapter/in/sdl/components/aria/aria.h
        adapter/in/sdl/components/background/background.c
        adapter/in/sdl/components/background/background.h
        adapter/in/sdl/pages/fight/sdl_monsters/sdl_monster.c
        adapter/in/sdl/pages/fight/sdl_monsters/sdl_monster.h
        #adapter/in/cli/cli_controller.c
        adapter/in/sdl/sld_controller.c
)

target_link_libraries(DoomDepths SDL2::SDL2main)
target_link_libraries(DoomDepths sdl_ttf::sdl_ttf)
target_link_libraries(DoomDepths SDL2_image::SDL2_image)

target_include_directories(
        DoomDepths
        PUBLIC
        "${CMAKE_SOURCE_DIR}"
)

target_link_libraries(DoomDepths DOMAIN)
target_link_libraries(DoomDepths UTILS)
