# g_hub.h

## File Purpose
This header file defines the interface for managing hub-based level transitions in GZDoom. It provides functions for serializing hub data and handling the transition between levels within a hub structure. Hub-based level transitions allow players to move between levels while maintaining their inventory, health, and other statistics.

## Key Components

### Function Declarations

- **`G_SerializeHub`**: Function for serializing hub data during save/load operations. This ensures that hub-related information is preserved when saving or loading a game.
- **`G_LeavingHub`**: Function called when a player is leaving a hub level. It handles the collection and management of statistics and other data that needs to be preserved across hub transitions.

## Technical Details

- The file includes forward declarations for structures and classes used in the implementation:
  - `cluster_info_t`: Structure containing information about a level cluster (a group of levels forming a hub).
  - `wbstartstruct_t`: Structure containing information needed for the intermission screen.
  - `FSerializer`: Class used for serializing game data.
  - `FLevelLocals`: Class containing level-specific data and state.

## Connections with Other Modules

- Works with the game state management system to handle level transitions.
- Interacts with the serialization system for save/load operations.
- Connects to the intermission system to display appropriate statistics when moving between hub levels.
- Used by the level management system to maintain player state across hub transitions.
