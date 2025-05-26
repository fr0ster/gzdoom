# a_morph.cpp

## File Purpose
This source file implements the actor morphing system in GZDoom. It provides the functionality for transforming one actor (typically a player) into another actor type with different abilities, appearance, and properties. The implementation uses the virtual function system to delegate the actual morphing behavior to the actor classes themselves.

## Key Components

### P_MorphActor Function
```cpp
bool P_MorphActor(AActor *activator, AActor *victim, PClassActor *ptype, PClassActor *mtype, int duration, int style, PClassActor *enter_flash, PClassActor *exit_flash)
```

This function transforms an actor into another type with specified parameters:
- `activator`: Actor causing the morphing (can be NULL)
- `victim`: Actor to be morphed
- `ptype`: Player class to check for (if morphing a player)
- `mtype`: Actor class to morph into
- `duration`: How long the morph lasts (in tics)
- `style`: Combination of MORPH_* flags (defined in a_morph.h)
- `enter_flash`: Actor class to spawn as visual effect when morphing
- `exit_flash`: Actor class to spawn as visual effect when unmorphing
- Returns: Whether morphing was successful

The implementation uses the virtual machine system to call the `Morph` virtual function on the victim actor. This allows different actor types to implement their own morphing behavior while maintaining a consistent interface.

### P_UnmorphActor Function
```cpp
bool P_UnmorphActor(AActor *activator, AActor *morphed, int flags, bool force)
```

This function reverts a morphed actor to its original form:
- `activator`: Actor causing the unmorphing (can be NULL)
- `morphed`: Actor to be unmorphed
- `flags`: Additional control flags
- `force`: Whether to force unmorphing regardless of conditions
- Returns: Whether unmorphing was successful

Similar to P_MorphActor, this function uses the virtual machine system to call the `Unmorph` virtual function on the morphed actor.

## Implementation Details

### Virtual Function Delegation
Both functions use the `IFVIRTUALPTR` macro to check if the actor has the appropriate virtual function and call it if available. This design allows:

1. Different actor types to implement custom morphing behavior
2. ZScript extensions to override the default behavior
3. Consistent interface for all morphing operations

### Parameter Passing
The implementation uses the VMCall system to pass parameters to the virtual functions:
- Parameters are packed into a VMValue array
- The return value is captured in a VMReturn object
- The boolean result is converted from an integer

### Minimal C++ Implementation
The C++ implementation is intentionally minimal, serving primarily as a bridge to the virtual function system. The actual morphing logic is implemented in ZScript or the actor classes themselves, allowing for greater flexibility and extensibility.

## Connections with Other Modules
- Integrates with the actor system through "actor.h"
- Uses the virtual machine system through "vm.h"
- Connects to the class information system through "info.h"
- Indirectly connects to the player system for player-specific morphing behavior
- Interfaces with the weapon system for handling weapons during morphing
