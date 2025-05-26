# a_decals.cpp

## File Purpose
This file implements the decal system in GZDoom, which allows for visual marks (blood splats, bullet holes, scorch marks, etc.) to be placed on walls and other surfaces in the game world. The implementation handles decal creation, positioning, rendering properties, and lifecycle management.

## Key Components

### Decal Classes
- **DBaseDecal**: Base class for all decals
  - Handles basic decal properties like position, scale, alpha, etc.
  - Manages attachment to walls and sectors
  - Provides serialization support
  - Contains methods for positioning and removal

- **DImpactDecal**: Specialized decal class for impact effects
  - Extends DBaseDecal with impact-specific functionality
  - Manages the decal queue system
  - Handles spreading decals across multiple surfaces

### Key Functions
- **DBaseDecal::StickToWall**: Attaches a decal to a wall surface
- **DBaseDecal::GetRealZ**: Calculates the actual Z position based on wall properties
- **DBaseDecal::CalcFracPos**: Calculates the fractional position along a wall
- **DBaseDecal::Spread**: Spreads a decal across multiple walls if it doesn't fit on one
- **DBaseDecal::CloneSelf**: Creates a copy of the decal on another surface
- **DImpactDecal::StaticCreate**: Static factory method to create impact decals
- **SprayDecal**: Creates a decal in the direction an actor is facing
- **ShootDecal**: Creates a decal by shooting a ray from a point
- **SpawnDecal**: Creates a decal at an actor's position

### Decal Spreading System
- **SpreadLeft/SpreadRight**: Functions to spread decals to adjacent walls
- **SpreadInfo**: Structure to hold information during the spreading process
- Uses recursion to handle complex wall arrangements
- Prevents infinite loops by tracking visited walls

### Memory Management
- **DImpactDecal::CheckMax**: Enforces the maximum number of decals
- **DImpactDecal::Expired**: Called when a decal is removed
- Uses a queue system to remove oldest decals when the limit is reached

## Implementation Details

### Decal Positioning
- Decals are positioned along walls using a fractional distance system
- Z-positioning depends on wall type (upper, middle, lower)
- Handles special cases like 3D floors
- Adjusts for wall flags like ML_DONTPEGBOTTOM and ML_DONTPEGTOP

### Decal Properties
- Supports translucency via alpha and RenderStyle
- Handles coloration through AlphaColor
- Supports scaling in X and Y dimensions
- Can be flipped and rotated

### Decal Types
- System supports different types of decals through templates
- Decals can have "lower" variants that appear below the main decal
- Supports translatable decals for blood effects that match actor blood colors

### Optimization
- Uses a queue system to limit the number of decals
- Oldest decals are removed when the limit is reached
- Avoids creating decals on surfaces that don't support them

## Connections with Other Modules
- Integrates with the actor system through "actor.h"
- Uses the rendering system for decal visualization
- Connects to the level geometry system for wall and sector information
- Uses serialization for saving/loading decal states
- Exposes functionality to ZScript through action functions
- Interacts with the texture system for decal appearance
