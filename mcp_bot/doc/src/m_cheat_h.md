# m_cheat.h

## File Purpose
This header file defines the interface for GZDoom's cheat system. It provides function declarations for implementing and executing various cheat commands that allow players to modify game state, such as gaining health, weapons, ammo, and special abilities. These functions are called when the game detects a valid cheat sequence entered by the player.

## Key Components

### Cheat Execution Functions

- **`cht_DoMDK`**: Implements the "MDK" (Murder Death Kill) cheat, which instantly kills monsters in the player's line of sight.
- **`cht_DoCheat`**: The main cheat handler function that processes various cheat codes based on a cheat identifier.
- **`cht_Give`**: Gives the player specified items or resources.
- **`cht_Take`**: Removes specified items or resources from the player.
- **`cht_SetInv`**: Sets the player's inventory of a specific item to a specified amount.
- **`cht_Suicide`**: Causes the player to commit suicide.
- **`cht_Morph`**: Transforms the player into another creature (like a chicken or pig).
- **`cht_Takeweaps`**: Removes all weapons from the player.

## Technical Details

### Function Parameters

- Most functions take a `player_t` pointer as their first parameter, which identifies the player who activated the cheat.
- Additional parameters vary by function:
  - Item names as strings for `cht_Give` and `cht_Take`
  - Amount values for quantity-based cheats
  - Class references for morphing cheats

### Return Values

- Most cheat functions return void, as they directly modify game state.
- `cht_Morph` returns an `FString` containing a message about the result of the morph operation.

### Implementation Notes

- These functions are designed to be called from the network code, not directly from input handling.
- The header only declares the interface; the actual implementation is in `m_cheat.cpp`.
- The functions are designed to work with GZDoom's object and inventory systems.

## Connections with Other Modules

- Used by the input system to execute cheats when valid cheat sequences are detected.
- Interfaces with the player system to modify player state.
- Connected to the inventory system for giving and taking items.
- Linked to the actor system for morphing and other transformations.
- Used by the network code to synchronize cheat effects in multiplayer games.

## Notable Features

- Support for both classic Doom cheats (IDKFA, IDDQD, etc.) and GZDoom-specific cheats.
- Functions for both giving and taking items from players.
- Support for morphing the player into different creatures.
- Ability to set inventory amounts to specific values.
- Support for suicide functionality.
