# actor.h

## File Purpose
This header file defines the core `AActor` class, which is the foundation of all game objects in GZDoom. It serves as the base class for everything that can exist in the game world, including monsters, players, projectiles, items, decorations, and special effects. The file contains extensive flag definitions, property declarations, and method prototypes that govern how actors behave, interact, and are rendered in the game.

## Key Components

### AActor Class
The primary class defined in this file, inheriting from `DThinker`:

```cpp
class AActor final : public DThinker
{
    DECLARE_CLASS_WITH_META(AActor, DThinker, PClassActor)
    HAS_OBJECT_POINTERS
    // ... extensive member variables and methods
};
```

This massive class contains all the properties and behaviors needed for game objects, including:
- Position, velocity, and movement handling
- Rendering properties
- Collision detection
- State management
- Inventory handling
- Damage and health tracking
- Actor interactions
- Special effects

### Actor Flags
The file defines numerous flag enumerations that control various aspects of actor behavior:

#### ActorFlag (flags)
Basic actor properties like solidity, shootability, and movement characteristics:
- `MF_SOLID`: Actor is solid and blocks movement
- `MF_SHOOTABLE`: Actor can be shot
- `MF_MISSILE`: Actor is a projectile
- `MF_SPECIAL`: Actor can be picked up
- `MF_NOGRAVITY`: Actor is not affected by gravity
- And many more fundamental flags

#### ActorFlag2 through ActorFlag9 (flags2-flags9)
Additional specialized flags for more specific behaviors:
- Monster AI behaviors
- Special movement types
- Damage handling
- Visual effects
- Interaction rules
- And many other specialized behaviors

#### ActorRenderFlag (renderflags)
Flags that control how the actor is rendered:
- `RF_XFLIP`, `RF_YFLIP`: Sprite flipping
- `RF_FULLBRIGHT`: Render at full brightness
- `RF_INVISIBLE`: Don't render the actor
- Various clipping and positioning flags

#### ActorBounceFlag (BounceFlags)
Flags controlling how actors bounce off surfaces:
- `BOUNCE_Walls`: Bounces off walls
- `BOUNCE_Floors`: Bounces off floors
- `BOUNCE_Ceilings`: Bounces off ceilings
- Different bounce behavior presets (Heretic, Doom, Hexen)

### Key Methods

#### Lifecycle Methods
- `BeginPlay()`: Called when the actor is first created
- `PostBeginPlay()`: Called immediately before the actor's first tick
- `Tick()`: Called every game tick to update the actor
- `Die()`: Called when the actor is killed
- `OnDestroy()`: Called when the actor is being destroyed

#### Movement and Positioning
- `SetOrigin()`: Sets the actor's position
- `Move()`: Moves the actor by a vector
- `CheckPortalTransition()`: Handles movement through portals
- `FallAndSink()`: Applies gravity and water physics

#### Combat and Damage
- `TakeSpecialDamage()`: Handles special damage types
- `DoSpecialDamage()`: Applies special damage effects
- `ApplyDamageFactor()`: Modifies damage based on type
- `GetModifiedDamage()`: Calculates final damage after modifiers

#### State Management
- `SetState()`: Changes the actor's state
- `FindState()`: Looks up a state by name
- `SetIdle()`: Sets the actor to its idle state

#### Inventory Management
- `GiveInventoryType()`: Gives an item to the actor
- `FindInventory()`: Finds an item in the actor's inventory
- `UseInventory()`: Uses an inventory item
- `DropInventory()`: Drops an item from inventory

#### Actor Relationships
- `IsFriend()`: Checks if another actor is friendly
- `IsHostile()`: Checks if another actor is hostile
- `IsTeammate()`: Checks if another actor is on the same team
- `CopyFriendliness()`: Copies relationship settings from another actor

#### Utility Methods
- `Distance2D()`, `Distance3D()`: Calculate distance to another actor
- `AngleTo()`: Calculates angle to another actor
- `Vec2To()`, `Vec3To()`: Calculate vector to another actor
- `GetGravity()`: Gets the actor's gravity value

### Actor Iterators
The file also defines iterator classes for finding actors:

- `FActorIterator`: Iterates through actors with a specific TID (thing ID)
- `NActorIterator`: Iterates through actors of a specific class with a TID

### Helper Functions
Several global helper functions for actor manipulation:

- `Spawn()`: Creates a new actor
- `ClassForSpawn()`: Resolves a class name to a spawn type
- `P_LinePickActor()`: Finds an actor along a line trace
- `PrintMiscActorInfo()`: Prints debug information about an actor

## Implementation Details

### Actor Position and Movement
- Actors have a 3D position (`__Pos`) and velocity (`Vel`)
- Movement is handled through various methods that update position and handle collisions
- Special handling for portals, 3D floors, and other complex geometry

### Actor States
- Actors use a state machine system for controlling behavior and animation
- States are defined in DECORATE/ZScript and linked to sprite frames
- State transitions can trigger function calls

### Actor Flags
- Extensive use of bit flags to control behavior
- Flags are organized into multiple 32-bit fields (flags through flags9)
- Additional specialized flag sets for rendering, bouncing, etc.

### Serialization
- Actors can be serialized for save games
- The `Serialize()` method handles saving and loading actor state

### Networking
- Support for network synchronization
- The `EnableNetworking()` method controls network visibility

## Connections with Other Modules
- Connects to the rendering system through sprite and visual properties
- Interfaces with the physics system for movement and collision
- Links to the damage system for combat interactions
- Connects to the inventory system for item management
- Interfaces with the state system for behavior control
- Uses the thinker system for regular updates
- Connects to the portal system for seamless world transitions
- Interfaces with the player system for player-controlled actors
