# a_dynlight.cpp

## File Purpose
This source file implements the dynamic lighting system for GZDoom. It provides the functionality for creating, managing, and updating various types of dynamic lights in the game world. The implementation handles light behavior, positioning, linking to game geometry, and interaction with actors.

## Key Components

### Memory Management
- Uses a custom memory arena (`FMemArena`) for efficient allocation of dynamic lights
- Maintains a free list for recycling light objects
- Provides functions for creating and releasing light objects

### Light Creation and Management
- `GetLight`: Creates or recycles a dynamic light object
- `AttachLight`: Attaches a dynamic light to an actor
- `ActivateLight`: Activates lights attached to an actor
- `DeactivateLight`: Deactivates lights attached to an actor
- `SetOffset`: Sets the offset position for lights attached to an actor

### FDynamicLight Implementation
- `ReleaseLight`: Releases a light back to the free list
- `Activate`: Activates a light and initializes its properties
- `Tick`: Updates the light state each game tick
- `UpdateLocation`: Updates the light's position relative to its owner
- `AddLightNode`: Adds a light node to the appropriate lists
- `LinkLight`: Links the light to affected world geometry
- `UnlinkLight`: Removes the light from world geometry links
- `CollectWithinRadius`: Collects surfaces within the light's radius
- `DistToSeg`: Calculates distance from light to a line segment

### Actor Light Management
- `AActor::AttachLight`: Attaches a light to an actor
- `AActor::SetDynamicLights`: Sets up lights based on actor state
- `AActor::DeleteAttachedLights`: Removes all lights from an actor
- Functions for finding, attaching, and removing user-defined lights

### ZScript Interface
- Native functions exposed to ZScript for light manipulation:
  - `A_AttachLight`: Creates a light with specified parameters
  - `A_AttachLightDef`: Attaches a predefined light
  - `A_RemoveLight`: Removes a light by ID
  - `AttachLight`: Attaches a light to an actor
  - `ActivateLight`: Activates lights on an actor
  - `DeactivateLight`: Deactivates lights on an actor
  - `SetOffset`: Sets light offset position

### Level-wide Light Management
- `FLevelLocals::DeleteAllAttachedLights`: Removes all lights before saving
- `FLevelLocals::RecreateAllAttachedLights`: Recreates lights after loading

## Implementation Details

### Light Behavior Types
The file implements different light behaviors:
- **Point Light**: Static intensity
- **Pulse Light**: Smoothly cycles between intensity values
- **Flicker Light**: Randomly switches between two intensities
- **Random Flicker Light**: Randomly varies intensity within a range
- **Sector Light**: Derives intensity from sector light level

### Light Positioning
- Calculates light position based on owner position and offset
- Applies rotation to offset based on owner's angle
- Prevents lights from getting too close to floors or ceilings
- Handles portal-aware positioning

### Light-Surface Interaction
- Uses spatial partitioning to efficiently find affected surfaces
- Calculates distance from light to walls and sectors
- Handles one-sided walls for shadow mapping
- Supports cross-portal lighting effects

### Memory Optimization
- Uses a memory arena for efficient allocation
- Recycles light objects to reduce memory fragmentation
- Maintains touch lists to avoid redundant calculations

## Connections with Other Modules
- Integrates with the actor system through "actor.h"
- Uses cyclers from "cycler.h" for smooth light transitions
- Connects to level data through "g_levellocals.h"
- Interfaces with the rendering system for light visualization
- Uses serialization for saving/loading light states
- Exposes functionality to ZScript through action functions
- Interacts with the sector system for sector-based lighting
