project(DoomDepthsBasicCli C)

add_library(BASIC_CLI
        cli_controller.c
        cli_grimoire_controller.c
        cli_map_controller.c
        cli_inventory_controller.c
        cli_fight_controller.c
        cli_town_controller.c
)

target_link_libraries(BASIC_CLI DOMAIN)
target_link_libraries(BASIC_CLI APPLICATION)
target_link_libraries(BASIC_CLI UTILS)