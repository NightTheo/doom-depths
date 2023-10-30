project(DoomDepthsAdapter C)

add_library(ADAPTER
        ../utils/log/cli_log.c
        in/cli/cli_grimoire_controller.c
        in/cli/cli_map_controller.c
        out/custom_file_repository/restore_last_game.c
        out/custom_file_repository/save_game_state.c

        out/ihm/cli/cli_display_loot.c
        in/cli/cli_inventory_controller.c

        out/ihm/cli/cli_display_game_over.c
        in/cli/cli_fight_controller.c

        out/in_memory_intern_game_state/in_memory_intern_game_state.c

        in/cli/cli_controllers.h
        in/cli/cli_town_controller.c

        in/sdl/pages/town/sdl_town_controller.c
        in/sdl/sdl_controller.h
        in/sdl/pages/town/sdl_town_controller.h
        in/sdl/components/button/button.c
        in/sdl/components/button/button.h
        in/sdl/components/padding/padding.c
        in/sdl/components/padding/padding.h
        in/sdl/components/point/point.h
        in/sdl/components/color/sdl_color.h
        in/sdl/components/color/sdl_color.c
        in/sdl/components/button/button_events/button_events.h
        in/sdl/pages/map/sdl_map_page.c
        in/sdl/pages/map/sdl_map_page.h
        in/sdl/pages/map/zone/sdl_zone.c
        in/sdl/pages/map/zone/sdl_zone.h
        in/sdl/components/button/button_size/button_size.c
        in/sdl/components/button/button_size/button_size.h
        in/sdl/components/button/button_callback/button_callback.c
        in/sdl/components/button/button_callback/button_callback.h
        in/sdl/pages/fight/sdl_fight_page.c
        in/sdl/pages/fight/sdl_fight_page.h
        in/sdl/pages/pages.h
        in/sdl/pages/fight/health_bar/health_bar.c
        in/sdl/pages/fight/health_bar/health_bar.h
        in/sdl/components/button/button_events/button_events.c
        in/sdl/components/screen_position/screen_position.c
        in/sdl/components/screen_position/screen_position.h
        in/sdl/components/row/row.c
        in/sdl/components/row/row.h
        in/sdl/components/sprite_sheet/sprite_sheet.c
        in/sdl/components/sprite_sheet/sprite_sheet.h
        in/sdl/components/animation/animation.c
        in/sdl/components/animation/animation.h
        in/sdl/pages/fight/sdl_player/sdl_player.c
        in/sdl/pages/fight/sdl_player/sdl_player.h
        in/sdl/pages/fight/fight_action_buttons/fight_action_buttons.c
        in/sdl/pages/fight/fight_action_buttons/fight_action_buttons.h
        in/sdl/components/event/event.c
        in/sdl/components/event/event.h
        in/sdl/components/aria/aria.c
        in/sdl/components/aria/aria.h
        in/sdl/components/background/background.c
        in/sdl/components/background/background.h
        in/sdl/pages/fight/sdl_monsters/sdl_monster.c
        in/sdl/pages/fight/sdl_monsters/sdl_monster.h
        #in/cli/cli_controller.c
        in/sdl/sld_controller.c
)

target_link_libraries(ADAPTER SDL2::SDL2main)
target_link_libraries(ADAPTER sdl_ttf::sdl_ttf)
target_link_libraries(ADAPTER SDL2_image::SDL2_image)


target_include_directories(ADAPTER PRIVATE ".")

target_link_libraries(ADAPTER DOMAIN)
target_link_libraries(ADAPTER APPLICATION)
target_link_libraries(ADAPTER UTILS)