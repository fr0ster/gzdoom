# g_hub.cpp

## File Purpose
This source file implements the hub-based level transition system in GZDoom. It manages the collection, aggregation, and persistence of player statistics and level information when moving between levels within a hub structure. Hub-based level transitions allow players to move between levels while maintaining their inventory, health, and other statistics, creating a more interconnected game world.

## Key Components

### Data Structures

- **`FHubInfo`**: A structure that stores level statistics for a hub level, including:
  - Level number
  - Kill counts (total and maximum)
  - Item counts (maximum)
  - Secret counts (maximum)
  - Frag counts (maximum)
  - Player statistics for each player

### Global Data

- **`hubdata`**: A dynamic array of `FHubInfo` structures that stores statistics for all levels in the current hub.

### Functions

- **`G_LeavingHub`**: Handles the transition when a player leaves a hub level. It:
  - Stores the current level's statistics in the `hubdata` array
  - Updates player statistics for non-multiplayer games
  - Aggregates statistics across all hub levels when leaving the hub entirely
  - Sets up the intermission screen with appropriate statistics

- **`G_SerializeHub`**: Serializes hub data during save/load operations to ensure hub information is preserved.

- **`G_ClearHubInfo`**: Clears the hub data array, typically when leaving a hub entirely.

### Serialization Support

- Custom serialization functions for `wbplayerstruct_t` and `FHubInfo` structures to support save/load operations.

## Technical Details

### Hub Statistics Management

- When a player completes a level within a hub, their statistics for that level are stored in the `hubdata` array.
- If the player is leaving the hub entirely, the statistics from all levels in the hub are aggregated to show total progress.
- For single-player games, the system directly uses the level's counters for kills, items, and secrets rather than the intermission counters, which don't work correctly in hubs.

### Hub Transition Modes

- **`FINISH_SameHub`**: Player is moving to another level within the same hub.
- Other modes (implied from the code): Player is leaving the hub entirely.

### Cluster Information

- The system uses cluster information to determine if a level is part of a hub and to display appropriate names during the intermission.

## Connections with Other Modules

- Interacts with the game state management system (`g_game.h`) for level transitions.
- Uses the serialization system (`serializer.h`) for save/load operations.
- Connects to the intermission system (`wi_stuff.h`) to display appropriate statistics.
- Accesses level-specific data through `FLevelLocals`.
- Uses string resources (`gstrings.h`) for localized cluster names.

## Notable Features

- Supports both single-player and multiplayer hub transitions.
- Maintains separate statistics for each level within a hub.
- Aggregates statistics when leaving a hub entirely.
- Handles localized cluster names for the intermission screen.
