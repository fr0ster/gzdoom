# p_saveg.cpp

## File Purpose
This source file implements the game state serialization system in GZDoom, responsible for saving and loading game state to and from archives. It contains the code for serializing various game objects, structures, and states, enabling save game functionality and preserving game state during level transitions in hub-based games.

## Key Components

### Serialization Functions

The file contains numerous serialization functions for different game objects and structures:

- **Line Serialization**: Functions to serialize `line_t` structures, which represent level lines.
- **Side Serialization**: Functions to serialize `side_t` structures, which represent line sides.
- **Sector Serialization**: Functions to serialize `sector_t` structures, which represent level sectors.
- **Plane Serialization**: Functions to serialize `secplane_t` structures, which represent sector planes.
- **Portal Serialization**: Functions to serialize line and sector portals.
- **Polyobject Serialization**: Functions to serialize polyobjects.
- **Texture Manipulation Serialization**: Functions to serialize texture manipulation data.
- **Colormap Serialization**: Functions to serialize colormap data.

### Level Serialization Methods

- **`FLevelLocals::Serialize`**: The main method for serializing an entire level's state.
  - Handles serialization of all level components, including lines, sides, sectors, portals, thinkers, and more.
  - Manages the process of saving and loading game state.
  - Handles special cases for hub transitions.

- **`FLevelLocals::SerializeSubsectors`**: Serializes subsector visibility information.
  - Uses a compact encoding scheme to efficiently store which subsectors have been seen by the player.

- **`FLevelLocals::SerializePlayers`**: Serializes player data.
  - Handles both single-player and multiplayer scenarios.
  - Manages the matching of saved players to current players in multiplayer games.

- **`FLevelLocals::SerializeSounds`**: Serializes sound state.
  - Saves and restores active sounds and music.

### Helper Methods

- **`FLevelLocals::ReadOnePlayer`**: Reads a single player's data during deserialization.
- **`FLevelLocals::ReadMultiplePlayers`**: Reads multiple players' data during deserialization.
- **`FLevelLocals::CopyPlayer`**: Copies player data from one player to another.
- **`FLevelLocals::SpawnExtraPlayers`**: Spawns additional players if there are more players now than in the saved game.
- **`FLevelLocals::RecalculateDrawnSubsectors`**: Reconstructs subsector visibility information if the saved data is unusable.

### Snapshot Methods

- **`FLevelLocals::SnapshotLevel`**: Creates a snapshot of the current level state.
  - Used for hub transitions and quick saves.

- **`FLevelLocals::UnSnapshotLevel`**: Restores a level from a snapshot.
  - Used when returning to a hub level or loading a save.

## Technical Details

### Serialization System

- The file uses the `FSerializer` class as the core of its serialization system.
- Serialization is performed using a structured format that can be either binary or text-based.
- The system supports versioning to handle compatibility between different game versions.
- Special care is taken to handle pointers and references correctly during serialization.

### Player Handling

- The player serialization system can handle both single-player and multiplayer scenarios.
- In multiplayer, it attempts to match saved players to current players based on names.
- If exact matches aren't found, it assigns saved player data on a first-come, first-served basis.
- Special handling is provided for bot players.

### Hub Transitions

- Hub transitions require special handling to preserve certain game state between levels.
- The level snapshot system is used to store and restore level state when moving between hub levels.
- Certain thinkers and game objects are preserved during hub transitions.

### Checksum Verification

- The system uses MD5 checksums to verify that a saved game matches the current level.
- This prevents loading saves from different levels, which could cause corruption or crashes.

## Connections with Other Modules

- Works closely with the serialization framework (`serializer_doom.h`, `serialize_obj.h`).
- Interfaces with the thinker system for managing active game objects.
- Connects to the ACS scripting system for handling deferred scripts.
- Interacts with the player system for saving and loading player state.
- Interfaces with the sound system for saving and restoring sound state.
- Works with the level structure system for serializing level geometry.

## Notable Features

- Support for both binary and text-based serialization formats.
- Efficient encoding of subsector visibility information.
- Robust handling of multiplayer scenarios.
- Support for hub-based level transitions.
- Checksum verification to prevent loading incompatible saves.
- Comprehensive serialization of game state, including complex structures like portals and polyobjects.
