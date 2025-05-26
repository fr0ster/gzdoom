# g_dumpinfo.cpp

## File Purpose
This source file implements various console commands (CCMDs) that provide diagnostic information about the current game state. These commands allow developers and players to inspect and debug different aspects of the GZDoom engine, such as lights, decals, portals, and other game elements. The file serves as a collection of utility functions for outputting detailed information about the game's internal state.

## Key Components

### Light-Related Commands

- **`listlights`**: Lists all dynamic lights in the game world, including their position, color, radius, and affected walls and sectors.

### Decal-Related Commands

- **`countdecals`**: Counts and displays the number of impact decals in each level.
- **`spray`**: Creates a decal at the player's current position and orientation.

### Map Information Commands

- **`mapchecksum`**: Calculates and displays MD5 checksums for maps, useful for verifying map integrity.
- **`hiddencompatflags`**: Shows compatibility flags that are automatically set for each level.
- **`listmaps`**: Lists all defined maps in the loaded WADs, with their names and source files.

### Portal and 3D Floor Commands

- **`dumpportals`**: Displays detailed information about portal groups in the game world.
- **`dumplinktable`**: Prints the portal displacement table to the console.
- **`dump3df`**: Shows information about 3D floors in a specified sector.

### Inventory Commands

- **`printinv`**: Prints the console player's current inventory.
- **`targetinv`**: Prints the inventory of the actor the player is aiming at.

### Miscellaneous Commands

- **`printsections`**: Prints information about level sections.
- **`dumptags`**: Dumps all defined tags in the level.
- **`skyfog`**: Gets or sets the sky fog density.
- **`listsnapshots`**: Lists all level snapshots and their sizes.

## Technical Details

### Command Implementation

- Uses the `CCMD` macro to define console commands.
- Many commands iterate through `AllLevels()` to provide information for all loaded levels.
- Commands often use the `Printf` function to output formatted text to the console.

### Debugging Features

- Provides detailed information about game objects and structures.
- Allows inspection of internal game state that is not normally visible.
- Supports wildcards for filtering in some commands (e.g., `listmaps`).

### Statistics Tracking

- The `ADD_STAT` macro is used to add a statistics counter for interpolations.
- Some commands count and report on game elements (lights, decals, etc.).

## Connections with Other Modules

- Includes headers from various subsystems:
  - `c_dispatch.h` for console command handling
  - `g_levellocals.h` for level data access
  - `a_dynlight.h` for dynamic light information
  - `p_setup.h` for map setup functions
  - `filesystem.h` for file system access
  - `texturemanager.h` for texture information
  - And others for specific functionality

## Notable Features

- Commands provide both high-level summaries and detailed breakdowns of game elements.
- Many commands support examining multiple levels when more than one is loaded.
- Some commands have special debug functionality (e.g., `printinv` with player number in debug builds).
- The file demonstrates how to access and traverse various game data structures.
