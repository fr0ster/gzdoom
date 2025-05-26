# actorptrselect.cpp

## File Purpose
This implementation file provides the functionality for safely selecting and manipulating actor pointers in GZDoom, as declared in `actorptrselect.h`. It contains the core logic for retrieving actor references based on selectors, as well as safety mechanisms to prevent circular references in actor chains that could cause infinite loops or crashes.

## Key Components

### COPY_AAPTR and COPY_AAPTREX Functions
```cpp
AActor *COPY_AAPTR(AActor *origin, int selector);
AActor *COPY_AAPTREX(FLevelLocals *Level, AActor *origin, int selector);
```

These functions implement the actor pointer selection system, following a priority-based approach:

1. If the origin is a player and a player-specific selector is specified, it returns:
   - The actor the player is aiming at (`AAPTR_PLAYER_GETTARGET`)
   - The NPC the player is conversing with (`AAPTR_PLAYER_GETCONVERSATION`)

2. If the origin is non-null and a general actor selector is specified, it returns:
   - The actor's target (`AAPTR_TARGET`)
   - The actor's master (`AAPTR_MASTER`)
   - The actor's tracer (`AAPTR_TRACER`)
   - The player the actor is friendly to (`AAPTR_FRIENDPLAYER`)
   - The actor that would be hit by a bullet fired by this actor (`AAPTR_GET_LINETARGET`)

3. If a static selector is specified, it returns:
   - A specific player actor (`AAPTR_PLAYER1` through `AAPTR_PLAYER8`)
   - NULL (`AAPTR_NULL`)

4. If no selector matches, it returns the origin actor itself.

The `COPY_AAPTREX` variant takes an additional `FLevelLocals` parameter to support operations across different levels, while `COPY_AAPTR` is a convenience wrapper that uses the origin actor's level.

### Verification Functions

#### VerifyTargetChain
```cpp
void VerifyTargetChain(AActor *self, bool preciseMissileCheck);
```

This function checks for and breaks circular references in the target chain of missile actors. It uses an algorithm that:

1. Starts with the actor itself and follows its target chain
2. For each new actor in the chain, verifies it hasn't appeared earlier in the chain
3. If a circular reference is detected, breaks the chain by setting the actor's target to NULL

The `preciseMissileCheck` parameter controls how strictly an actor is considered a missile. This accommodates legacy behavior that some mods depend on.

#### VerifyMasterChain
```cpp
void VerifyMasterChain(AActor *self);
```

Similar to `VerifyTargetChain`, but checks for circular references in the master chain of any actor. This prevents infinite loops when traversing ownership hierarchies.

### ASSIGN_AAPTR Function
```cpp
void ASSIGN_AAPTR(AActor *toActor, int toSlot, AActor *ptr, int flags);
```

This function assigns an actor pointer to a specific slot of another actor:

1. `AAPTR_TARGET`: Sets the actor's target
2. `AAPTR_MASTER`: Sets the actor's master
3. `AAPTR_TRACER`: Sets the actor's tracer

After assignment, it automatically calls the appropriate verification function unless safety checks are disabled via the flags parameter.

## Implementation Details

### Helper Functions
The implementation includes a lambda function `AAPTR_RESOLVE_PLAYERNUM` that resolves a player number to the corresponding player actor, handling cases where the player might not be in the game.

### Bullet Slope Calculation
For targeting-related selectors (`AAPTR_PLAYER_GETTARGET` and `AAPTR_GET_LINETARGET`), the function calls `P_BulletSlope` to determine what actor the origin would hit if it fired a projectile.

### Portal Awareness
The targeting functions use the `ALF_PORTALRESTRICT` flag when calculating bullet slopes, ensuring proper handling of portals in the game world.

### Circular Reference Detection
The verification functions use a careful algorithm to detect circular references without getting caught in the very loops they're trying to prevent:

1. They maintain an "origin" pointer that marks the last verified actor in the chain
2. For each new actor, they check if it matches any actor from the start of the chain up to the origin
3. If a match is found, the chain is broken by setting the appropriate pointer to NULL

### Safety Flags
The `ASSIGN_AAPTR` function respects the safety flags (`PTROP_UNSAFETARGET`, `PTROP_UNSAFEMASTER`) that allow bypassing the verification checks when needed.

## Connections with Other Modules
- Interfaces with the `AActor` class for accessing and modifying actor properties
- Uses `P_BulletSlope` from the targeting system for line-of-sight checks
- Connects to the player system through player actor references
- Supports the conversation system through the conversation NPC pointer
- Used by DECORATE and ZScript for actor pointer manipulation
