# a_morph.h

## File Purpose
This header file defines the interface and constants for the actor morphing system in GZDoom. Morphing allows one actor (typically a player) to transform into another actor type with different abilities, appearance, and properties. This system is primarily used for player transformations like the pig spell in Heretic or the chicken spell in Hexen.

## Key Components

### Constants

#### Time and Health Constants
- `MORPHTICS`: Default duration for morphing effects (40 seconds in tics)
- `MAXMORPHHEALTH`: Maximum health value for morphed forms (30)

#### Morph Style Flags
An enumeration of bit flags that control various aspects of morphing behavior:

- `MORPH_OLDEFFECTS`: Default Heretic/Hexen behavior (value 0)
- `MORPH_ADDSTAMINA`: Treats morphing as a power rather than a curse
- `MORPH_FULLHEALTH`: Uses new health semantics for morphed forms
- `MORPH_UNDOBYTOMEOFPOWER`: Unmorphs when using a Tome of Power
- `MORPH_UNDOBYCHAOSDEVICE`: Unmorphs when using a Chaos Device
- `MORPH_FAILNOTELEFRAG`: Prevents telefragging when unmorph fails
- `MORPH_FAILNOLAUGH`: Disables laugh sound when unmorph fails
- `MORPH_WHENINVULNERABLE`: Allows self-morphing while invulnerable
- `MORPH_LOSEACTUALWEAPON`: Only loses specified morph weapon
- `MORPH_NEWTIDBEHAVIOUR`: Transfers actor TID to morphed form
- `MORPH_UNDOBYDEATH`: Unmorphs when killed
- `MORPH_UNDOBYDEATHFORCED`: Forces unmorph when killed
- `MORPH_UNDOBYDEATHSAVES`: Restores health when unmorphed by death
- `MORPH_UNDOBYTIMEOUT`: Unmorphs when duration expires
- `MORPH_UNDOALWAYS`: Always unmorphs when using power items
- `MORPH_TRANSFERTRANSLATION`: Transfers color translation to morphed form
- `MORPH_KEEPARMOR`: Preserves armor value when morphing
- `MORPH_IGNOREINVULN`: Ignores player invulnerability status

- `MORPH_STANDARDUNDOING`: Combined flag for standard unmorph triggers

### Function Declarations

#### P_MorphActor
```cpp
bool P_MorphActor(AActor *activator, AActor *victim, PClassActor *ptype, PClassActor *mtype, int duration, int style, PClassActor *enter_flash, PClassActor *exit_flash);
```

Transforms an actor into another type with specified parameters:
- `activator`: Actor causing the morphing (can be NULL)
- `victim`: Actor to be morphed
- `ptype`: Player class to check for (if morphing a player)
- `mtype`: Actor class to morph into
- `duration`: How long the morph lasts (in tics)
- `style`: Combination of MORPH_* flags
- `enter_flash`: Actor class to spawn as visual effect when morphing
- `exit_flash`: Actor class to spawn as visual effect when unmorphing
- Returns: Whether morphing was successful

#### P_UnmorphActor
```cpp
bool P_UnmorphActor(AActor *activator, AActor *morphed, int flags = 0, bool force = false);
```

Reverts a morphed actor to its original form:
- `activator`: Actor causing the unmorphing (can be NULL)
- `morphed`: Actor to be unmorphed
- `flags`: Additional control flags
- `force`: Whether to force unmorphing regardless of conditions
- Returns: Whether unmorphing was successful

## Implementation Details

The header only declares the interface for the morphing system. The actual implementation is in a_morph.cpp, which uses the virtual function system to delegate the morphing behavior to the actor classes themselves.

The morphing system is designed to be flexible, allowing for different behaviors based on the style flags. This enables game-specific morphing mechanics while maintaining a consistent interface.

## Connections with Other Modules
- Interacts with the actor system for transformations
- Connects to the player system for player-specific morphing behavior
- Interfaces with the weapon system for handling weapons during morphing
- Uses the virtual machine system for delegating morphing behavior to actor classes
