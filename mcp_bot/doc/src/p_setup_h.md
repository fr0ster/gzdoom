# p_setup.h

## File Purpose
This header file defines the structures and functions for setting up and loading game levels in GZDoom. It provides the interface for map data handling, level initialization, and related utilities. The file is a crucial component of the engine's level management system, enabling the game to load, process, and prepare maps for gameplay.

## Key Components

### MapData Structure

The `MapData` class is the central component of this file, serving as a container for map data:

- **Resource Management**: Contains a `ResourceHolder` nested structure to manage the lifecycle of resource files.
- **Map Lump Management**: Stores readers for each map lump (THINGS, LINEDEFS, SIDEDEFS, etc.) in the `MapLumps` array.
- **Format Tracking**: Maintains flags to indicate map format details, such as whether it's a text-based UDMF map or contains behavior scripts.
- **Data Access Methods**: Provides methods for reading and accessing map data, including:
  - `Reader`: Returns a FileReader for a specific lump index
  - `Read`: Reads data from a specific lump
  - `Size`: Returns the size of a specific lump
  - `CheckName`: Verifies the name of a specific lump
  - `GetChecksum`: Calculates an MD5 checksum for the map

### Map Loading Functions

- **`P_OpenMapData`**: Opens a map for reading.
  - Takes a map name and a boolean flag indicating whether to just check for existence.
  - Returns a `MapData` structure with readers for all map components.

- **`P_CheckMapData`**: Checks if a map exists and can be loaded.
  - Uses `P_OpenMapData` with the "justcheck" flag to verify map existence.
  - Returns true if the map can be loaded, false otherwise.

### Level Setup Functions

- **`P_SetupLevel`**: The main function for setting up a level.
  - Takes a level object, a position indicator for spawn location, and a flag indicating if this is a new game.
  - Handles the entire process of loading and initializing a level.

- **`P_LoadLightmap`**: Loads lightmap data for a map.

- **`P_FreeLevelData`**: Frees all level data, optionally performing a full garbage collection.

- **`P_Init`**: Initializes the play subsystem.

### UDMF Utility Functions

- **`GetUDMFInt`**: Retrieves an integer value from UDMF (Universal Doom Map Format) data.
- **`GetUDMFFloat`**: Retrieves a floating-point value from UDMF data.
- **`GetUDMFString`**: Retrieves a string value from UDMF data.

### Miniseg Utility Functions

- **`FixMinisegReferences`**: Fixes references to minisegs.
- **`FixHoles`**: Fixes holes in the BSP tree.
- **`ReportUnpairedMinisegs`**: Reports unpaired minisegs for debugging.

## Technical Details

### Map Format Support

The file is designed to handle multiple map formats:

- **Traditional Binary Format**: The classic Doom map format with separate lumps for THINGS, LINEDEFS, SIDEDEFS, etc.
- **UDMF Text Format**: A more modern, text-based format that offers greater flexibility.
- **Build Engine Format**: Support for maps from the Build engine (though implementation details are not fully present in this file).

### Resource Management

- The `ResourceHolder` nested structure ensures proper cleanup of resource files.
- The design separates resource management from data access, allowing for clean handling of resources.

### Map Data Access

- The `MapData` class provides a unified interface for accessing map data, regardless of the source or format.
- Methods like `Reader`, `Read`, and `Size` abstract away the details of how map data is stored and accessed.

## Connections with Other Modules

- Works closely with the `p_setup.cpp` implementation file which contains the actual level setup code.
- Interfaces with the file system (`fs_filesystem.h`) for file access and resource management.
- Connects to the node builder (`nodebuild.h`) for BSP tree construction.
- Used by the game's level transition and initialization code.
- Provides data that will be used by the rendering, physics, and gameplay systems.

## Notable Features

- Support for multiple map formats (traditional binary, UDMF text, potentially Build engine).
- Efficient resource management through the `ResourceHolder` structure.
- Unified interface for map data access through the `MapData` class.
- Checksum generation for map identification and verification.
- Utilities for working with UDMF data and fixing BSP issues.
