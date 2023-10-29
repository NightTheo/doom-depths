project(DoomDepthsDomain C)

include_directories(
        "doom_depths"
        "fight"
        "magic"
        "map"
        "monsters"
        "player"
)

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(
        "${PARENT_DIR}/utils"
        "${PARENT_DIR}/application/port/out/log"
)

add_library(DOMAIN
        monsters/monsters.c
        player/player.c
        fight/fight.c
        fight/player_fight_action/player_fight_action.c
        fight/loot/loot.c
        fight/weapon/weapon.c
        player/inventory/inventory.c
        player/inventory/player_inventory_action/player_inventory_actions.c
        player/equipment/equipment.c
        fight/armor/armor.c
        magic/spell/spell.c
        magic/mana_potion/mana_potion.c
        magic/grimoire/grimoire.c
        map/map.c
        map/zone/zone.c
        map/position/position.c
        doom_depths/doom_depths.c
        "${PARENT_DIR}/utils/utils.c"
        "${PARENT_DIR}/utils/random/random.c"
        "${PARENT_DIR}/utils/time/time_util.c"
        "${PARENT_DIR}/adapter/out/log/cli_log.c"
)

target_include_directories(DOMAIN PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/doom_depths"
        "${CMAKE_CURRENT_SOURCE_DIR}/fight"
        "${CMAKE_CURRENT_SOURCE_DIR}/magic"
        "${CMAKE_CURRENT_SOURCE_DIR}/map"
        "${CMAKE_CURRENT_SOURCE_DIR}/monsters"
        "${CMAKE_CURRENT_SOURCE_DIR}/player"
)