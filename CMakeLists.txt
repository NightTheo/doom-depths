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
add_subdirectory("application")
include_directories(
        "${PROJECT_SOURCE_DIR}/adapter"
        "${PROJECT_SOURCE_DIR}/application/port/out/log"
)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(DoomDepths main.c
        adapter/out/log/cli_log.c
        adapter/in/cli/cli_grimoire_controller.c
        adapter/in/cli/cli_map_controller.c
        adapter/out/custom_file_repository/restore_last_game.c
        adapter/out/custom_file_repository/save_game_state.c

        adapter/out/ihm/cli/cli_display_loot.c
        adapter/in/cli/cli_inventory_controller.c

        adapter/out/ihm/cli/cli_display_game_over.c
        adapter/in/cli/cli_fight_controller.c

        adapter/out/in_memory_intern_game_state/in_memory_intern_game_state.c

        adapter/in/cli/cli_controllers.h
        adapter/in/cli/cli_town_controller.c

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
target_link_libraries(DoomDepths APPLICATION)
