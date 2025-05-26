# g_levellocals.h

## File Purpose
This header file defines the `FLevelLocals` class, which serves as the central container for all level-specific data and functionality in GZDoom. It encapsulates the entire state of a game level, including geometry, actors, thinkers, and various subsystems. This class is designed to allow for potential multi-level support, where different levels could exist simultaneously.

## Key Components

### FLevelLocals Class

The `FLevelLocals` class is the primary component of this file, containing:

- **Level Geometry Data**: Arrays for vertices, sectors, lines, sides, nodes, subsectors, and other geometric elements that define the level structure.
- **Actor Management**: Systems for tracking and managing actors, including TID (Thing ID) hashing for efficient lookup.
- **Thinker Management**: Collections for both regular and clientside thinkers that handle game logic updates.
- **Portal Systems**: Data structures and methods for handling portals between sectors and across lines.
- **Lighting Systems**: Support for dynamic lights, lightmaps, and light probes.
- **Physics and Collision**: Methods for point-in-sector tests, collision detection, and movement calculations.
- **Game State Management**: Functions for level initialization, transitions, and serialization.
- **Player Management**: Access to player data and methods for player-related operations.

### Helper Structures

- **`FPortalBits`**: Used to mark processed portals during traversal operations.
- **`FGlobalDLightLists`**: Container for dynamic light lists used in rendering.

### Inline Accessor Methods

The file includes numerous inline accessor methods for:

- **Portal Operations**: Methods to check if portals block movement, sight, or sound.
- **Sector Operations**: Methods to access sector properties and perform sector-related tests.
- **Line Operations**: Methods to access line properties and perform line-related tests.
- **Player Operations**: Methods to check player status and relationships.

## Technical Details

### Level Data Organization

- The level geometry is stored in arrays of structures like `vertex_t`, `sector_t`, `line_t`, etc.
- Additional data like portals, polyobjects, and blockmap information is stored in separate containers.
- The class maintains references to various subsystems like behaviors, thinkers, and event managers.

### Memory Management

- The class overrides the `new` operator to ensure that newly allocated level instances start with zeroed memory.
- It uses smart pointers (`TObjPtr`) for many objects to ensure proper garbage collection.

### Iterator Support

- The class provides various iterator methods for traversing sectors, lines, actors, and thinkers.
- These iterators allow for efficient filtering by tags, IDs, or other criteria.

### Serialization Support

- Methods for saving and loading level state, including snapshots for hub-based level transitions.
- Support for comparing the current state with the original loaded state to optimize save files.

## Connections with Other Modules

- Interacts with the game state management system (`g_game.h`) for level transitions.
- Uses the map information system (`g_mapinfo.h`) for level data.
- Connects to the serialization system for save/load operations.
- Works with the rendering system for visual representation of the level.
- Interfaces with the physics system for collision detection and movement.
- Coordinates with the actor system for spawning and managing game objects.

## Notable Features

- Support for multiple lighting modes, including software and hardware rendering.
- Portal systems for connecting different parts of a level.
- Extensive support for tags and IDs for scripting and triggers.
- Snapshot system for preserving level state during hub transitions.
- Support for both server-side and client-side thinkers.
- Integration with various subsystems like ACS scripting, FraggleScript, and event handling.
