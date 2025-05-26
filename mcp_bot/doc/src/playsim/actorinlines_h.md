# actorinlines.h

## File Purpose
This header file contains inline function implementations for the `AActor` class that depend on both `actor.h` and `r_defs.h`. These functions are placed in a separate file to avoid circular dependencies between those two headers. The file primarily focuses on position calculations, portal handling, and various utility functions that need to access both actor and rendering data.

## Key Components

### Position Calculation Functions

#### PosRelative Functions
A set of functions that calculate an actor's position relative to different reference points:

```cpp
DVector3 PosRelative(int portalgroup) const;
DVector3 PosRelative(const AActor *other) const;
DVector3 PosRelative(sector_t *sec) const;
DVector3 PosRelative(const line_t *line) const;
```

These functions handle portal offsets between different sectors, allowing for seamless positioning across portal boundaries.

#### Vector Calculation Functions
Functions that calculate positions at offsets from the actor:

```cpp
DVector2 Vec2Offset(double dx, double dy, bool absolute);
DVector3 Vec2OffsetZ(double dx, double dy, double atz, bool absolute);
DVector2 Vec2Angle(double length, DAngle angle, bool absolute);
DVector3 Vec3Offset(double dx, double dy, double dz, bool absolute);
DVector3 Vec3Offset(const DVector3 &ofs, bool absolute);
DVector3 Vec3Angle(double length, DAngle angle, double dz, bool absolute);
```

These functions handle both absolute positioning and portal-aware positioning based on the `absolute` parameter.

### Interpolation Functions

```cpp
void ClearInterpolation();
void ClearFOVInterpolation();
```

These functions reset interpolation data for smooth movement and FOV changes between frames.

### Utility Functions

#### GetBobOffset
```cpp
double GetBobOffset(double ticfrac) const;
```

Calculates the vertical bobbing offset for floating actors, using sine functions to emulate the old floatbob offset table.

#### GetCameraHeight
```cpp
double GetCameraHeight() const;
```

Returns the camera height for this actor, using either a custom height or half the actor's height.

#### GetDropItems
```cpp
FDropItem *GetDropItems() const;
```

Returns the list of items this actor can drop when killed.

#### GetGravity
```cpp
double GetGravity() const;
```

Calculates the effective gravity for this actor, taking into account the level gravity, sector gravity, and actor-specific gravity.

#### AttackOffset
```cpp
double AttackOffset(double offset);
```

Calculates the vertical offset for attacks, adjusting for player crouching if applicable.

#### isFrozen
```cpp
bool isFrozen() const;
```

Determines if an actor is currently frozen, either by its own freeze timer or by a level-wide time freeze effect.

#### GetLightLevel
```cpp
int GetLightLevel(sector_t* rendersector);
```

Calculates the light level for rendering this actor, using either the sector's light level or the actor's custom light level.

### Helper Functions

#### P_IsBlockedByLine
```cpp
bool P_IsBlockedByLine(AActor* actor, line_t* line);
```

Determines if a line blocks the movement of an actor, considering various line flags and actor properties.

#### GetMBFBounceFactor and GetWallBounceFactor
```cpp
double GetMBFBounceFactor(AActor* actor);
double GetWallBounceFactor(AActor* actor);
```

Calculate bounce factors for actors, with special handling for MBF (Marine's Best Friend) compatibility.

#### CanJump
```cpp
bool CanJump(AActor* actor);
```

Determines if an actor can jump, considering both modern flags and MBF compatibility.

#### BobSin
```cpp
double BobSin(double fb);
```

Helper function that calculates a sine wave value for bobbing effects.

### Sector Plane Extensions

```cpp
double secplane_t::ZatPoint(const AActor *ac) const;
```

Extension to the `secplane_t` class that calculates the Z height of a plane at an actor's position.

### Sector Extensions

```cpp
double sector_t::HighestCeilingAt(AActor *a, sector_t **resultsec);
double sector_t::LowestFloorAt(AActor *a, sector_t **resultsec);
```

Extensions to the `sector_t` class that find the highest ceiling or lowest floor at an actor's position.

## Implementation Details

### Portal Handling
Many functions in this file handle portal offsets, which are essential for seamless movement and positioning across portal boundaries. The `absolute` parameter in vector calculation functions determines whether portal offsets should be applied.

### MBF Compatibility
Several functions provide special handling for MBF (Marine's Best Friend) compatibility, particularly for bounce factors and jumping behavior.

### Optimization
As these are inline functions, they are optimized for performance by being expanded at the call site rather than requiring a function call.

## Connections with Other Modules
- Includes `actor.h` for the `AActor` class definition
- Includes `r_defs.h` for rendering-related structures
- Includes `g_levellocals.h` for level-specific data
- Includes `d_player.h` for player-specific functionality
- Connects to the portal system through displacement calculations
- Interfaces with the physics system for gravity and bouncing
- Links to the rendering system for light level calculations
