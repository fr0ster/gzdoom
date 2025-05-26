# p_openmap.cpp

## File Purpose
This source file implements the functionality for loading map data from resource files in GZDoom. It creates the necessary data structures to access map lumps from WAD files or other resource containers. The file handles both traditional Doom-format maps and UDMF (Universal Doom Map Format) text maps, providing a unified interface for the rest of the engine to access map data regardless of the underlying format.

## Key Components

### MapData Structure

The file works with the `MapData` structure (defined elsewhere) which contains:
- Readers for each map lump
- Names of each map lump
- Flags indicating map format (text-based or binary)
- Resource file references

### Map Opening Functions

- **`P_OpenMapData`**: The main function for opening a map.
  - Takes a map name and a flag indicating whether to just check for existence.
  - Returns a `MapData` structure with readers for all map lumps.
  - Handles maps from different sources (internal WADs, external files).
  - Supports both traditional binary maps and UDMF text maps.

- **`P_CheckMapData`**: A helper function to check if a map exists.
  - Uses `P_OpenMapData` with the check flag set to true.
  - Returns a boolean indicating whether the map exists.

### Map Lump Processing

- **`GetMapIndex`**: Determines the type of map lump based on its name.
  - Maps lump names to indices in the `MapData` structure.
  - Checks for required lumps and reports errors if they're missing.
  - Returns the lump index or error codes.

### Map Checksum Generation

- **`MapData::GetChecksum`**: Generates an MD5 checksum for a map.
  - Includes the header, THINGS, LINEDEFS, SIDEDEFS, SECTORS, and BEHAVIOR lumps.
  - Excludes node-builder generated lumps.
  - Used for map identification and verification.

## Technical Details

### Map Format Detection

- The code detects the map format based on the presence of specific lumps:
  - Traditional binary maps have THINGS, LINEDEFS, etc.
  - UDMF text maps have TEXTMAP and ENDMAP markers.
  - Build engine maps are detected but not fully supported in this implementation.

### Map Lump Requirements

- The file defines which lumps are required for a valid map:
  - THINGS, LINEDEFS, SIDEDEFS, VERTEXES, and SECTORS are required.
  - SEGS, SSECTORS, NODES, REJECT, and BLOCKMAP are optional.
  - BEHAVIOR is required for Hexen-format maps.

### Resource Handling

- Maps can be loaded from:
  - Internal WAD files (using the resource system)
  - External WAD files (specified with "file:" prefix)
  - Direct lump access (for maps embedded in the main WAD)

### UDMF Support

- UDMF maps are detected by the presence of a TEXTMAP lump.
- Special handling is provided for UDMF-specific lumps like ZNODES.
- The code maintains compatibility with both formats through the `MapData` abstraction.

## Connections with Other Modules

- Interfaces with the file system (`filesystem.h`) for resource access.
- Connected to the map setup system (`p_setup.h`) for level initialization.
- Uses the MD5 system (`md5.h`) for map checksums.
- Interacts with the resource system for WAD file handling.
- Used by the game engine to load maps during level transitions.

## Notable Features

- Support for multiple map formats (traditional binary, UDMF text).
- Flexible map loading from various sources.
- Error checking for required map lumps.
- Map checksum generation for verification.
- Handling of special cases like maps directly embedded in WADs.
- Support for external map files.
