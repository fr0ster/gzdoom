# g_level.cpp

## File Purpose
This source file implements the level management system for GZDoom. It handles the initialization, loading, and transitioning between game levels, as well as managing level state persistence through snapshots. The file provides the core functionality for moving players between levels, handling level-specific settings, and coordinating the various subsystems involved in level transitions.

## Key Components

### Level Initialization and Loading

- **`G_InitNew`**: Initializes a new game level, setting up the game state, player classes, and other level-specific settings.
- **`G_DeferedInitNew`**: Schedules a new game to be started on the next game tick, allowing for clean transitions.
- **`G_DoLoadLevel`**: Performs the actual loading of a level, setting up the game state for play.
- **`FLevelLocals::DoLoadLevel`**: Member function that handles the level loading process for a specific level.
- **`FLevelLocals::Init`**: Initializes a level's properties based on its map information.

### Level Transitions

- **`FLevelLocals::ChangeLevel`**: Initiates a level change to a new map.
- **`FLevelLocals::ExitLevel`**: Exits the current level to the next map.
- **`FLevelLocals::SecretExitLevel`**: Exits the current level to the secret exit map.
- **`FLevelLocals::DoCompleted`**: Handles the completion of a level, preparing for the next level or intermission.
- **`G_DoCompleted`**: Global function that calls the level's DoCompleted method and sets up the intermission.

### Level State Management

- **`FLevelLocals::StartTravel`**: Prepares players and their inventory for travel to another level in a hub.
- **`FLevelLocals::FinishTravel`**: Completes the travel process, moving players to their new positions in the destination level.
- **`G_WriteSnapshots`**: Writes level snapshots to a resource file for later restoration.
- **`G_ReadSnapshots`**: Reads level snapshots from a resource file.
- **`G_WriteVisited`**: Serializes information about which levels have been visited.
- **`G_ReadVisited`**: Deserializes information about which levels have been visited.

### Console Commands

- **`map`**: Command to change to a specified map in single-player mode.
- **`recordmap`**: Command to record a demo starting on a specified map.
- **`open`**: Command to open a map file directly.

### Cutscene Management

- **`CreateCutscene`**: Creates a cutscene based on a cutscene definition and map information.
- **`RunIntermission`**: Sets up and runs an intermission sequence between levels.

### Player Management

- **`FLevelLocals::PlayerReborn`**: Reinitializes a player after death.
- **`FLevelLocals::DeathMatchSpawnPlayer`**: Spawns a player at a deathmatch start point.
- **`FLevelLocals::QueueBody`**: Adds a player's corpse to the body queue.

## Technical Details

### Level Locals

- The `FLevelLocals` class encapsulates all level-specific data and functionality.
- Each level has its own instance of `FLevelLocals`, with `primaryLevel` being the main level.
- The class provides methods for level initialization, player spawning, level transitions, and more.

### Level Snapshots

- Level snapshots are used to preserve the state of a level when leaving it temporarily (e.g., in a hub).
- Snapshots are stored in compressed form and can be written to and read from save files.
- The `G_WriteSnapshots` and `G_ReadSnapshots` functions handle the serialization of level snapshots.

### Level Change Flags

- Various flags control how level transitions behave, such as whether to reset inventory, preserve facing direction, etc.
- These flags are defined in `g_level.h` and used by the `ChangeLevel` function.

### Intermission and Cutscenes

- The `RunIntermission` function sets up intermission screens between levels.
- Cutscenes can be played at the start or end of levels, or when entering or leaving clusters.

## Connections with Other Modules

- Interacts with the game state management system (`g_game.h`) for level transitions.
- Uses the map information system (`g_mapinfo.h`) for level data.
- Connects to the serialization system for save/load operations.
- Works with the hub system (`g_hub.h`) for managing level transitions within hubs.
- Interfaces with the player system for spawning and managing players.
- Coordinates with the rendering, sound, and input systems during level transitions.

## Notable Features

- Support for hub-based level transitions, where player state is preserved between levels.
- Handling of level snapshots for preserving level state when temporarily leaving a level.
- Support for various level transition types, including normal exits, secret exits, and hub transitions.
- Integration with the cutscene and intermission systems for seamless level transitions.
- Console commands for changing levels and recording demos.
