# p_setup.cpp

## File Purpose
This source file implements the level setup and initialization functionality in GZDoom. It contains the code for loading map data, setting up level structures, spawning players, and preparing the game world for play. This file is responsible for transforming raw map data into a playable game level with all necessary components initialized and ready for gameplay.

## Key Components

### Level Initialization Functions

- **`P_SetupLevel`**: The main function for setting up a level.
  - Loads map data, initializes level structures, spawns players, and prepares the game world.
  - Handles both new games and level transitions.
  - Processes map data through the MapLoader class.
  - Sets up special level features like lightning.

- **`P_Init`**: Initializes the play subsystem.
  - Calls initialization functions for effects, terrain types, key messages, and sprites.

- **`P_Shutdown`**: Shuts down the play subsystem.
  - Destroys thinkers, frees level data, and cleans up resources.

### Resource Management Functions

- **`P_FreeLevelData`**: Frees all level data from all loaded levels.
  - Optionally performs a full garbage collection.

- **`FLevelLocals::ClearLevelData`**: Clears all data for a specific level.
  - Destroys thinkers, clears arrays, and frees resources.

- **`FLevelLocals::ClearPortals`**: Clears all portal data for a new level start.
  - Resets portal structures and clears related rendering data.

### Precaching Functions

- **`PrecacheLevel`**: Preloads all relevant graphics for a level.
  - Builds lists of textures used in the level.
  - Calls renderer-specific precaching functions.

- **`AddToList`**: Helper function for adding textures to the precache list.
  - Handles animated textures, switches, and animated doors.

### Debug Commands

- **`dumpgeometry`**: Console command to dump level geometry information.
  - Outputs detailed information about sectors, subsectors, and segments.

- **`listmapsections`**: Console command to list map sections.
  - Shows the relationship between map sections, sectors, and lines.

### CVAR Handlers

- **`forcewater`**: Custom CVAR handler for forcing water effects.
  - Updates sector flags to force underwater effects when enabled.

## Technical Details

### Level Setup Process

1. **Preparation**:
   - Stops all sounds and clears previous level data.
   - Opens the map data file.
   - Initializes event handlers for the map.

2. **Map Loading**:
   - Creates a MapLoader instance.
   - Loads the map data through the MapLoader.
   - Generates a checksum for the level.

3. **Player Spawning**:
   - Spawns players according to game mode (deathmatch, coop, etc.).
   - Handles random player starts if enabled.
   - Moves unfriendly players to deathmatch spots if needed.

4. **Post-Processing**:
   - Processes monster counters based on game options.
   - Preprocesses FraggleScript scripts.
   - Precaches graphics and sounds if enabled.
   - Announces game start for deathmatch.

5. **Finalization**:
   - Sets up heightsec flags for 3D floors.
   - Creates a backup of map data for savegames.
   - Initializes the automap.
   - Starts special effects like lightning if needed.
   - Sets up dynamic lights.

### Texture Precaching

- The precaching system builds lists of textures used in the level to allow the renderer to preload them.
- It handles various texture types:
  - Wall textures from sidedefs
  - Flat textures from sectors
  - Sky textures
  - Animated textures and switches
  - Textures specified in MAPINFO

### Portal Management

- The portal system is reset at the start of each level.
- Default skybox and sky portals are created.
- Portal-related rendering data is cleared.

## Connections with Other Modules

- Works closely with the `MapLoader` class for loading and processing map data.
- Interfaces with the rendering system for precaching textures and setting up visual elements.
- Connects to the sound system for precaching sounds and managing audio.
- Interacts with the player system for spawning and positioning players.
- Uses the event system for map-specific event handlers.
- Interfaces with the scripting systems (ACS, FraggleScript) for level scripting.

## Notable Features

- Support for multiple map formats through the MapLoader class.
- Comprehensive precaching system for graphics and sounds.
- Handling of special level features like lightning and 3D floors.
- Debug commands for examining level geometry and structure.
- Support for both single-player and multiplayer game modes.
- Integration with the event system for map-specific scripting.
