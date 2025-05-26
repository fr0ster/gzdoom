# p_effect.cpp

## File Purpose
This implementation file provides the core functionality for particle effects and visual enhancements in GZDoom. It implements the structures and functions declared in `p_effect.h`, handling the creation, management, and rendering of particles, as well as various special effects like rail trails, blood splashes, and actor-specific effects. The file is essential for the game's visual presentation, adding dynamic and decorative elements that enhance the gameplay experience without directly affecting mechanics.

## Key Components

### Color Management
```cpp
static int grey1, grey2, grey3, grey4, red, green, blue, yellow, black,
           red1, green1, blue1, yellow1, purple, purple1, white,
           rblue1, rblue2, rblue3, rblue4, orange, yorange, dred, grey5,
           maroon1, maroon2, blood1, blood2;

static const struct ColorList {
    int *color;
    uint8_t r, g, b;
} Colors[] = {
    // ... color definitions
};
```

A comprehensive color management system that defines a palette of colors used by particles and effects. The `ParticleColor` function converts RGB values to the internal color format used by the renderer.

### Particle Memory Management
```cpp
static void FreeParticle(FLevelLocals* Level, particle_t* particle)
static particle_t *NewParticle(FLevelLocals *Level, bool replace = false)
```

Functions that handle the allocation and deallocation of particles from a fixed-size pool. `NewParticle` obtains a particle from the inactive list or, if necessary, replaces the oldest active particle. `FreeParticle` returns a particle to the inactive list.

### Particle System Initialization
```cpp
void P_InitParticles(FLevelLocals *Level)
void P_ClearParticles(FLevelLocals *Level)
void P_InitEffects(void)
```

Functions that initialize the particle system, clear all particles, and set up the color palette for effects.

### Particle Organization
```cpp
void P_FindParticleSubsectors(FLevelLocals *Level)
```

Organizes particles by subsectors for efficient rendering. This function is called each frame to update the spatial organization of particles based on their current positions.

### Particle Update
```cpp
void P_ThinkParticles(FLevelLocals *Level)
```

The main update function for particles, called each game tick. It updates particle positions, velocities, and other properties, handles portal traversal, and removes expired particles.

### Particle Creation
```cpp
particle_t *JitterParticle(FLevelLocals *Level, int ttl)
particle_t *JitterParticle(FLevelLocals *Level, int ttl, double drift)
void P_SpawnParticle(FLevelLocals *Level, const DVector3 &pos, const DVector3 &vel, const DVector3 &accel, PalEntry color, double startalpha, int lifetime, double size, double fadestep, double sizestep, int flags, FTextureID texture, ERenderStyle style, double startroll, double rollvel, double rollacc)
```

Functions for creating different types of particles. `JitterParticle` creates particles with random velocities and accelerations, while `P_SpawnParticle` provides full control over all particle properties.

### Effect Functions
```cpp
void P_RunEffect(AActor *actor, int effects)
void P_DrawRailTrail(AActor *source, TArray<SPortalHit> &portalhits, int color1, int color2, double maxdiff, int flags, PClassActor *spawnclass, DAngle angle, int duration, double sparsity, double drift, int SpiralOffset, DAngle pitch)
void P_DrawSplash(FLevelLocals *Level, int count, const DVector3 &pos, DAngle angle, int kind)
void P_DrawSplash2(FLevelLocals *Level, int count, const DVector3 &pos, DAngle angle, int updown, int kind)
void P_DisconnectEffect(AActor *actor)
```

Functions for creating various special effects:
- `P_RunEffect` applies actor-specific effects like rocket trails
- `P_DrawRailTrail` creates railgun-like beam effects
- `P_DrawSplash` and `P_DrawSplash2` create splash effects for impacts
- `P_DisconnectEffect` creates a visual effect when an actor is removed

### Visual Thinker Implementation
```cpp
class DVisualThinker : public DThinker
{
    // ... class implementation
};
```

A specialized thinker class for visual effects that don't fit the traditional particle model. This class provides a more flexible framework for complex visual effects that need to interact with the game world.

## Implementation Details

### Particle Lifecycle
The implementation manages particles through a complete lifecycle:
1. Allocation from a fixed-size pool
2. Initialization with specific properties
3. Regular updates to position, velocity, alpha, etc.
4. Portal traversal handling
5. Expiration when time-to-live reaches zero or alpha fades out
6. Deallocation back to the pool

### Memory Management
The particle system uses a fixed-size array of particles with linked lists for efficient management:
- Active particles are linked in a list starting at `ActiveParticles`
- Inactive particles are linked in a list starting at `InactiveParticles`
- The oldest active particle is tracked for replacement when the pool is full

### Portal Awareness
Particles are portal-aware, meaning they can properly traverse portals in the game world:
- Line portals are handled by checking for portal crossings based on movement
- Sector portals (floor and ceiling) are handled by checking if particles cross portal planes
- When a portal is crossed, the particle's position is adjusted by the portal displacement

### Effect Types
The implementation provides several types of effects:

#### Rocket Trails
Created for actors with the `FX_ROCKET` flag, consisting of yellow particles at the center and grey particles around the edges.

#### Grenade Trails
Created for actors with the `FX_GRENADE` flag, consisting of smoke particles behind the grenade.

#### Particle Fountains
Created for actors with a non-zero `fountaincolor` property, consisting of colored particles emanating from the actor.

#### Respawn Protection
Created for actors with the `FX_RESPAWNINVUL` flag, consisting of yellow and white particles surrounding the actor.

#### Rail Trails
Complex beam effects with inner and outer spirals of particles, used for railgun-like weapons.

#### Splash Effects
Various splash effects for impacts, blood, and other events.

#### Disconnect Effects
Special effects created when an actor is removed from the game.

### Visual Thinker
The `DVisualThinker` class provides a more flexible framework for visual effects:
- Inherits from `DThinker` for integration with the game's update system
- Maintains its own linked list for efficient management
- Supports custom rendering styles, translations, and animations
- Handles portal traversal and sector changes
- Provides interpolation for smooth rendering between frames
- Supports ZScript extensions for custom visual effects

## Connections with Other Modules
- Interfaces with the rendering system for displaying particles and visual thinkers
- Connects to the actor system for actor-specific effects
- Interfaces with the level system for spatial organization
- Connects to the portal system for portal-aware effects
- Used by weapon code for weapon effects
- Interfaces with the animation system for animated particles
- Connects to the sound system for effect sounds
- Interfaces with the ZScript system for custom visual effects
