# a_sharedglobal.h

## File Purpose
This header file defines several important shared classes and functions used throughout the GZDoom engine. It includes implementations for decals, screen fading effects, and earthquake effects. These components are considered "global" as they are used across multiple systems and are not specific to any one game feature.

## Key Components

### Decal Functions

#### ShootDecal
```cpp
DBaseDecal *ShootDecal(FLevelLocals *Level, const FDecalTemplate *tpl, sector_t *sec, double x, double y, double z, DAngle angle, double tracedist, bool permanent);
```

Creates a decal by shooting a ray from a point:
- Traces from the specified position in the given direction
- Places a decal where the ray hits a wall
- Returns the created decal or NULL if no suitable surface was found

#### SprayDecal
```cpp
void SprayDecal(AActor *shooter, const char *name, double distance = 172., DVector3 offset = DVector3(0., 0., 0.), DVector3 direction = DVector3(0., 0., 0.), bool useBloodColor = false, uint32_t decalColor = 0, FTranslationID translation = NO_TRANSLATION);
```

Creates a decal in the direction an actor is facing:
- Uses the actor's position and angle if no direction is specified
- Can use the actor's blood color for the decal
- Supports custom offsets, directions, and colors

### DBaseDecal Class
Base class for all decals in the game:

```cpp
class DBaseDecal : public DThinker
```

Key features:
- Inherits from DThinker for regular updates
- Manages decal properties like position, scale, alpha, color
- Handles attachment to walls and sectors
- Provides methods for spreading decals across surfaces
- Supports serialization for save/load

Important methods:
- `StickToWall`: Attaches a decal to a wall surface
- `GetRealZ`: Calculates the actual Z position based on wall properties
- `SetShade`: Sets the decal's color
- `Spread`: Spreads a decal across multiple walls if it doesn't fit on one
- `CloneSelf`: Creates a copy of the decal on another surface

### DImpactDecal Class
Specialized decal class for impact effects:

```cpp
class DImpactDecal : public DBaseDecal
```

Key features:
- Inherits from DBaseDecal
- Manages automatic decal creation from impacts
- Handles decal limits and cleanup
- Provides static creation methods

Important methods:
- `StaticCreate`: Factory methods for creating impact decals
- `CheckMax`: Enforces the maximum number of decals
- `Expired`: Called when a decal is removed

### DFlashFader Class
Handles screen blending/fading effects:

```cpp
class DFlashFader : public DThinker
```

Key features:
- Inherits from DThinker for regular updates
- Manages smooth transitions between different screen colors
- Supports timed fades with various parameters

Important methods:
- `Construct`: Initializes a fade effect with start/end colors and duration
- `SetBlend`: Updates the blend values based on progress
- `Cancel`: Immediately cancels the fade effect
- `Tick`: Updates the fade effect each game tick

### DEarthquake Class
Implements earthquake/screen shake effects:

```cpp
class DEarthquake : public DThinker
```

Key features:
- Inherits from DThinker for regular updates
- Creates screen shaking and rumbling effects
- Can damage actors within its radius
- Supports various customization flags

Important methods:
- `Construct`: Initializes an earthquake with various parameters
- `Tick`: Updates the earthquake effect each game tick
- `GetModIntensity`: Calculates modified intensity based on parameters
- `GetModWave`: Calculates wave effect for the earthquake
- `GetFalloff`: Calculates intensity falloff with distance
- `DoQuakeDamage`: Applies damage to actors within range
- `StaticGetQuakeIntensities`: Gets combined intensities of all active earthquakes

### FQuakeJiggers Structure
Holds earthquake effect parameters:

```cpp
struct FQuakeJiggers
```

Stores:
- Intensity values for different axes
- Offset values
- Roll intensity and wave parameters

### Earthquake Flags
Enumeration of flags that control earthquake behavior:
- `QF_RELATIVE`: Uses relative intensity
- `QF_SCALEDOWN`: Scales intensity down over time
- `QF_SCALEUP`: Scales intensity up over time
- `QF_MAX`: Uses maximum intensity
- `QF_FULLINTENSITY`: Always uses full intensity
- `QF_WAVE`: Uses wave pattern
- `QF_3D`: Applies in 3D space
- `QF_GROUNDONLY`: Only affects actors on the ground
- `QF_AFFECTACTORS`: Affects actors in range
- `QF_SHAKEONLY`: Only shakes the screen, no damage
- `QF_DAMAGEFALLOFF`: Damage decreases with distance

## Implementation Details

### Decal System
- Decals are attached to walls using a linked list structure
- Position is calculated using fractional distance along walls
- Z-positioning depends on wall type (upper, middle, lower)
- Supports spreading across multiple surfaces

### Flash Fader System
- Uses linear interpolation between start and end colors
- Timing is managed in game tics
- Directly modifies player's blend values

### Earthquake System
- Uses wave functions to create realistic shaking
- Supports damage with optional falloff
- Can affect both the camera and actors
- Multiple earthquakes can be active simultaneously

## Connections with Other Modules
- Includes "info.h" for class information
- Includes "actor.h" for the AActor class
- Connects to the rendering system for visual effects
- Interfaces with the sound system for earthquake sounds
- Uses the thinker system for regular updates
- Connects to the damage system for earthquake damage
