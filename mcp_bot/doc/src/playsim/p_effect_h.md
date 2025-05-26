# p_effect.h

## File Purpose
This header file defines the structures and functions for particle effects and visual enhancements in GZDoom. It provides the foundation for various visual effects like particle systems, rail trails, blood splashes, and other decorative elements that enhance the game's visual presentation without affecting gameplay mechanics directly.

## Key Components

### Particle Structure
```cpp
struct particle_t
{
    subsector_t* subsector;
    DVector3 Pos;
    FVector3 Vel;
    FVector3 Acc;
    float size, sizestep;
    float fadestep, alpha;
    int32_t ttl;
    int color;
    FTextureID texture;
    ERenderStyle style;
    float Roll, RollVel, RollAcc;
    uint16_t tnext, snext, tprev;
    uint16_t flags;
    FStandaloneAnimation animData;
};
```

The core structure that represents a particle in the game world. It contains all the information needed to render and update a particle, including:
- Position, velocity, and acceleration vectors
- Size and alpha (transparency) values, along with their change rates
- Time-to-live (ttl) counter
- Color and texture information
- Rendering style
- Roll (rotation) values and their change rates
- Linked list pointers for efficient management
- Animation data for animated particles

### Effect Flags
```cpp
enum
{
    FX_ROCKET           = 0x00000001,
    FX_GRENADE          = 0x00000002,
    FX_RESPAWNINVUL     = 0x00000020,
    FX_VISIBILITYPULSE  = 0x00000040
};
```

Flags that define different types of effects that can be applied to actors.

### Particle Style Enumeration
```cpp
enum EParticleStyle
{
    PT_DEFAULT  = -1, // Use gl_particles_style
    PT_SQUARE   = 0,
    PT_ROUND    = 1,
    PT_SMOOTH   = 2,
};
```

Defines the visual style of particles, controlling how they are rendered.

### Particle Flags
```cpp
enum EParticleFlags
{
    SPF_FULLBRIGHT              = 1 << 0,
    SPF_RELPOS                  = 1 << 1,
    SPF_RELVEL                  = 1 << 2,
    // ... more flags
};
```

Flags that control various aspects of particle behavior and rendering.

### Particle Management Functions
```cpp
void P_InitParticles(FLevelLocals *);
void P_ClearParticles(FLevelLocals *Level);
void P_FindParticleSubsectors(FLevelLocals *Level);
void P_ThinkParticles(FLevelLocals *Level);
```

Core functions for initializing, clearing, organizing, and updating particles in a level.

### Particle Spawning Functions
```cpp
particle_t *JitterParticle(FLevelLocals *Level, int ttl);
particle_t *JitterParticle(FLevelLocals *Level, int ttl, double drift);
void P_SpawnParticle(FLevelLocals *Level, const DVector3 &pos, const DVector3 &vel, const DVector3 &accel, PalEntry color, double startalpha, int lifetime, double size, double fadestep, double sizestep, int flags = 0, FTextureID texture = FNullTextureID(), ERenderStyle style = STYLE_None, double startroll = 0, double rollvel = 0, double rollacc = 0);
```

Functions for creating different types of particles with various properties.

### Effect Functions
```cpp
void P_InitEffects(void);
void P_RunEffect(AActor *actor, int effects);
void P_DrawRailTrail(AActor *source, TArray<SPortalHit> &portalhits, int color1, int color2, double maxdiff = 0, int flags = 0, PClassActor *spawnclass = NULL, DAngle angle = nullAngle, int duration = TICRATE, double sparsity = 1.0, double drift = 1.0, int SpiralOffset = 270, DAngle pitch = nullAngle);
void P_DrawSplash(FLevelLocals *Level, int count, const DVector3 &pos, DAngle angle, int kind);
void P_DrawSplash2(FLevelLocals *Level, int count, const DVector3 &pos, DAngle angle, int updown, int kind);
void P_DisconnectEffect(AActor *actor);
```

Functions for creating and managing various visual effects, such as:
- Rail trails (for railgun-like weapons)
- Splash effects (for impacts and explosions)
- Actor-specific effects (like rocket trails)
- Disconnect effects (when an actor is removed from the game)

### Portal Hit Structure
```cpp
struct SPortalHit
{
    DVector3 HitPos;
    DVector3 ContPos;
    DVector3 OutDir;
};
```

A structure used for tracking portal interactions with effects like rail trails, ensuring they properly traverse portals in the game world.

### Spawn Particle Parameters
```cpp
struct FSpawnParticleParams
{
    int color;
    FTextureID texture;
    int style;
    int flags;
    int lifetime;
    double size;
    double sizestep;
    DVector3 pos;
    DVector3 vel;
    DVector3 accel;
    double startalpha;
    double fadestep;
    double startroll;
    double rollvel;
    double rollacc;
};
```

A structure that encapsulates all parameters needed to spawn a particle, providing a convenient way to pass multiple parameters to particle creation functions.

### Visual Thinker Class Declaration
```cpp
class DVisualThinker;
```

Forward declaration of the `DVisualThinker` class, which is a specialized thinker for visual effects.

## Implementation Details

### Particle Management
The header defines a comprehensive system for managing particles, including:
- Initialization and clearing of particle systems
- Organization of particles by subsectors for efficient rendering
- Regular updates of particle properties (position, velocity, alpha, etc.)
- Creation of various types of particles with different behaviors

### Effect Types
Several types of visual effects are supported:
- Rocket and grenade trails
- Respawn invulnerability effects
- Visibility pulse effects
- Rail trails (for railgun-like weapons)
- Blood and impact splashes
- Disconnect effects

### Particle Rendering
Particles can be rendered in different styles:
- Square particles (simple quads)
- Round particles (textured quads with circular textures)
- Smooth particles (with alpha blending for smoother edges)

### Portal Awareness
The particle system is portal-aware, meaning effects can properly traverse portals in the game world. This is particularly important for effects like rail trails that might cross through portals.

### Memory Management
The particle system uses a fixed-size array of particles with linked lists for efficient management. Particles are allocated from this array and returned to it when they expire, avoiding dynamic memory allocation during gameplay.

## Connections with Other Modules
- Interfaces with the rendering system for displaying particles
- Connects to the actor system for actor-specific effects
- Interfaces with the level system for spatial organization of particles
- Connects to the portal system for portal-aware effects
- Used by weapon code for weapon effects
- Interfaces with the animation system for animated particles
