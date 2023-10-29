project(DoomDepthsDomain C)

add_executable(DOMAIN
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
)