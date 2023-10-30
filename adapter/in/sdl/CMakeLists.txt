project(DoomDepthsSDL C)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(SDL
        sld_controller.c
        pages/town/sdl_town_controller.c
        components/button/button.c
        components/padding/padding.c
        components/color/sdl_color.c
        pages/map/sdl_map_page.c
        pages/map/zone/sdl_zone.c
        components/button/button_size/button_size.c
        components/button/button_callback/button_callback.c
        pages/fight/sdl_fight_page.c
        pages/fight/health_bar/health_bar.c
        components/button/button_events/button_events.c
        components/screen_position/screen_position.c
        components/row/row.c
        components/sprite_sheet/sprite_sheet.c
        components/animation/animation.c
        pages/fight/sdl_player/sdl_player.c
        pages/fight/fight_action_buttons/fight_action_buttons.c
        components/event/event.c
        components/aria/aria.c
        components/background/background.c
        pages/fight/sdl_monsters/sdl_monster.c
)

target_include_directories(SDL PRIVATE ".")

target_link_libraries(SDL SDL2::SDL2main)
target_link_libraries(SDL sdl_ttf::sdl_ttf)
target_link_libraries(SDL SDL2_image::SDL2_image)

target_link_libraries(SDL DOMAIN)
target_link_libraries(SDL APPLICATION)
target_link_libraries(SDL UTILS)
target_link_libraries(SDL INFRASTRUCTURE)