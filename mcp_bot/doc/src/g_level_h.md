# g_level.h

## File Purpose
This header file defines the interface for level management in GZDoom. It provides functions for initializing, loading, and transitioning between game levels. The file serves as a central point for level-related operations, including level initialization, deferred level loading, and snapshot management.

## Key Components

### Level Initialization Functions

- **`G_InitNew`**: Initializes a new game level with the specified map name.
- **`G_DeferedInitNew`**: Schedules a new game to be started on the next game tick, allowing for clean transitions.
- **`G_DoLoadLevel`**: Performs the actual loading of a level, setting up the game state for play.

### Level Transition Functions

- **`G_ClearSnapshots`**: Clears level snapshots, which are used for hub-based level transitions.
- **`G_ReadSnapshots`**: Reads level snapshots from a resource file.
- **`G_WriteSnapshots`**: Writes level snapshots to a resource file.
- **`G_WriteVisited`**: Serializes information about which levels have been visited.
- **`G_ReadVisited`**: Deserializes information about which levels have been visited.

### Cutscene Management

- **`CreateCutscene`**: Creates a cutscene based on a cutscene definition and map information.

### Level Change Flags

- **`CHANGELEVEL_KEEPFACING`**: Preserves the player's facing direction when changing levels.
- **`CHANGELEVEL_RESETINVENTORY`**: Resets the player's inventory when changing levels.
- **`CHANGELEVEL_NOMONSTERS`**: Disables monsters in the next level.
- **`CHANGELEVEL_CHANGESKILL`**: Changes the skill level for the next level.
- **`CHANGELEVEL_NOINTERMISSION`**: Skips the intermission when changing levels.
- **`CHANGELEVEL_RESETHEALTH`**: Resets the player's health when changing levels.
- **`CHANGELEVEL_PRERAISEWEAPON`**: Raises the player's weapon automatically when entering the next level.

## Technical Details

- Uses forward declarations for various structures and classes to minimize header dependencies.
- Includes `doomtype.h`, `vectors.h`, `sc_man.h`, and `g_mapinfo.h` for necessary types and definitions.
- Declares external variables like `savegamerestore` for use in level loading and saving.

## Connections with Other Modules

- Works with the game state management system (`g_game.h`) for level transitions.
- Interacts with the map information system (`g_mapinfo.h`) for level data.
- Connects to the serialization system for save/load operations.
- Used by the hub system (`g_hub.h`) for managing level transitions within hubs.
- Interfaces with the cutscene system for level-related cutscenes.
