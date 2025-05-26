# actorptrselect.h

## File Purpose
This header file defines a system for safely selecting and manipulating actor pointers in GZDoom. It provides a standardized way to access various actor references (like target, master, tracer) and player pointers, while implementing safeguards against circular references that could cause infinite loops. This system is particularly important for scripting languages like DECORATE and ZScript that need to manipulate actor relationships.

## Key Components

### AAPTR Enumeration
Defines constants for selecting different actor pointers:

```cpp
enum AAPTR
{
    AAPTR_DEFAULT = 0,
    AAPTR_NULL = 0x1,
    AAPTR_TARGET = 0x2,
    AAPTR_MASTER = 0x4,
    AAPTR_TRACER = 0x8,
    // ... more selectors
};
```

The enumeration includes several categories of selectors:

#### General Actor Selectors
- `AAPTR_TARGET`: References the actor's target
- `AAPTR_MASTER`: References the actor's master
- `AAPTR_TRACER`: References the actor's tracer
- `AAPTR_FRIENDPLAYER`: References the player that the actor is friendly to
- `AAPTR_GET_LINETARGET`: Gets the actor that would be hit by a bullet fired by this actor

#### Player-Specific Selectors
- `AAPTR_PLAYER_GETTARGET`: Gets the actor that the player is aiming at
- `AAPTR_PLAYER_GETCONVERSATION`: Gets the NPC the player is conversing with

#### Static Selectors
- `AAPTR_PLAYER1` through `AAPTR_PLAYER8`: Direct references to specific player actors
- `AAPTR_NULL`: Explicitly returns a null pointer

#### Selector Groups
- `AAPTR_PLAYER_SELECTORS`: Combines all player-specific selectors
- `AAPTR_GENERAL_SELECTORS`: Combines all general actor selectors
- `AAPTR_STATIC_SELECTORS`: Combines all static selectors

### PTROP Enumeration
Defines flags for controlling pointer operation behavior:

```cpp
enum PTROP
{
    PTROP_UNSAFETARGET = 1,
    PTROP_UNSAFEMASTER = 2,
    PTROP_NOSAFEGUARDS = PTROP_UNSAFETARGET|PTROP_UNSAFEMASTER
};
```

These flags allow bypassing the safety checks that prevent circular references.

### Function Declarations

#### COPY_AAPTR and COPY_AAPTREX
```cpp
AActor *COPY_AAPTR(AActor *origin, int selector);
AActor *COPY_AAPTREX(FLevelLocals *Level, AActor *origin, int selector);
```

These functions retrieve an actor pointer based on the specified selector, following a priority order:
1. Player-specific selectors (if the origin is a player)
2. General actor selectors (if the origin is non-null)
3. Static selectors
4. The origin actor itself (if no selector matches)

#### Verification Functions
```cpp
void VerifyTargetChain(AActor *self, bool preciseMissileCheck=true);
void VerifyMasterChain(AActor *self);
```

These functions check for and break circular references in target and master chains, which could otherwise cause infinite loops.

#### ASSIGN_AAPTR
```cpp
void ASSIGN_AAPTR(AActor *toActor, int toSlot, AActor *ptr, int flags);
```

Assigns an actor pointer to a specific slot (target, master, or tracer) of another actor, with optional safety checks.

## Implementation Details

### Pointer Selection Logic
The `COPY_AAPTR` function implements a priority-based selection system that determines which actor reference to return based on the provided selector flags and the context of the origin actor.

### Safety Mechanisms
The verification functions (`VerifyTargetChain` and `VerifyMasterChain`) implement algorithms to detect and break circular references in actor chains. These are particularly important for:

1. **Target Chains**: Primarily for missiles, to prevent infinite recursion when processing missile movement and collisions
2. **Master Chains**: For all actors, to prevent infinite loops when traversing ownership hierarchies

### Missile Detection
The code includes special handling for missiles, with an optional `preciseMissileCheck` parameter to accommodate legacy behavior that some mods depend on.

## Connections with Other Modules
- Interfaces with the `AActor` class for accessing actor properties
- Used by DECORATE and ZScript for actor pointer manipulation
- Connects to the player system for player-specific pointer operations
- Used by the targeting system for line-of-sight checks
- Supports the conversation system through the conversation NPC pointer
