# m_cheat.cpp

## File Purpose
This source file implements GZDoom's cheat system as declared in `m_cheat.h`. It contains the functions that execute various cheat commands, allowing players to modify game state by gaining health, weapons, ammo, and special abilities. The implementation handles both classic Doom cheats and GZDoom-specific extensions, providing a comprehensive cheat system that works across different game modes and IWAD types.

## Key Components

### Global Variables

- **`globalfreeze`**: Controls whether the game world is frozen (monsters and other actors don't move).
- **`globalchangefreeze`**: Used to toggle the frozen state.

### Cheat Execution Functions

- **`cht_DoMDK`**: Implements the "MDK" (Murder Death Kill) cheat, which instantly kills monsters in the player's line of sight.
- **`cht_DoCheat`**: The main cheat handler function that processes various cheat codes based on a cheat identifier.
- **`cht_Give`**: Gives the player specified items or resources.
- **`cht_Take`**: Removes specified items or resources from the player.
- **`cht_SetInv`**: Sets the player's inventory of a specific item to a specified amount.
- **`cht_Suicide`**: Causes the player to commit suicide.
- **`cht_Morph`**: Transforms the player into another creature (like a chicken or pig).
- **`cht_Takeweaps`**: Removes all weapons from the player.

### Helper Classes

- **`DSuicider`**: A thinker class that handles delayed suicide operations, ensuring that death noises are properly played.

## Technical Details

### Cheat Implementation

The `cht_DoCheat` function is the core of the cheat system, handling a wide variety of cheats through a switch statement:

- **God Mode Cheats**: IDDQD, GOD, BUDDHA, etc.
- **Noclip Cheats**: IDCLIP, NOCLIP, etc.
- **Item Cheats**: IDKFA, IDFA, etc.
- **Power Cheats**: BEHOLDV, BEHOLDS, etc.
- **Special Cheats**: MASSACRE, FREEZE, etc.
- **Game-Specific Cheats**: Heretic/Hexen artifacts, Strife items, etc.

### Virtual Method Calls

Many cheat functions use the virtual method system to call appropriate game-specific implementations:

- Uses `IFVIRTUALPTRNAME` to find and call virtual methods on player pawns
- Supports different implementations for different game types
- Allows mods to override cheat behavior

### Suicide Implementation

The suicide cheat uses a special thinker class (`DSuicider`) to delay the suicide operation until the next game tick, ensuring that:

- Death noises are properly played
- The console has time to appear in single-player games
- The player's damage factor is properly restored

### ZScript Integration

The implementation includes integration with ZScript through:

- Virtual method calls to player pawn methods
- Support for ZScript-defined inventory items
- Handling of mod-specific cheats

## Connections with Other Modules

- Interfaces with the player system to modify player state
- Connected to the inventory system for giving and taking items
- Linked to the actor system for morphing and other transformations
- Uses the message system to display feedback to players
- Integrates with the network code for multiplayer synchronization
- Connects to the virtual method system for game-specific implementations

## Notable Features

- Support for both classic Doom cheats and GZDoom extensions
- Game-specific cheat handling for Heretic, Hexen, and Strife
- Comprehensive feedback messages for cheat activation
- Network-safe implementation for multiplayer games
- Support for freezing and unfreezing the game world
- Integration with the ZScript virtual method system
- Special handling for suicide to ensure proper death effects
