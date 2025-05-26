# c_cmds.cpp

## File Purpose
This source file implements a wide range of console commands for GZDoom. It provides the core functionality for many of the game's cheat commands, debugging tools, and utility functions that can be accessed through the console interface. These commands allow players and developers to manipulate the game state, access debugging information, and perform various utility functions.

## Key Components

### Cheat Commands

- **God Mode Commands**: `god`, `god2`, `iddqd`, `buddha`, `buddha2` - Various implementations of invulnerability
- **Movement Cheats**: `fly`, `noclip`, `noclip2` - Commands that alter player movement physics
- **Combat Cheats**: `notarget`, `powerup`, `anubis` - Commands that affect enemy behavior or player abilities
- **Item Manipulation**: `give`, `take`, `setinv` - Commands to add, remove, or set inventory items

### Debugging Commands

- **Actor Information**: `linetarget`, `info`, `myinfo` - Display information about actors in the game
- **Actor Listing**: `actorlist`, `actornum`, `monster`, `monsternum`, `items`, `itemsnum`, `countitems`, `countitemsnum` - List or count various types of actors
- **Position Information**: `currentpos` - Display the player's current position and orientation

### Map Navigation

- **Map Changing**: `idclev`, `hxvisit`, `changemap`, `nextmap`, `nextsecret` - Commands to change the current map
- **Position Changing**: `warp` - Teleport the player to specific coordinates

### Game State Manipulation

- **Player State**: `resurrect`, `chase`, `thaw` - Commands that affect the player's state
- **Game Parameters**: `changeskill` - Change the game's difficulty level
- **Script Execution**: `puke`, `pukename`, `special` - Execute ACS scripts or map specials

### Utility Commands

- **Save/Load**: `save`, `load` - Save or load game state
- **Visual Effects**: `changesky`, `skymisttoggle` - Modify visual elements of the game
- **Information Display**: `mapinfo`, `secret` - Display information about maps or secrets

### Helper Functions

- **`CheckCheatmode`**: Checks if cheats are allowed in the current game state
- **`PrintFilteredActorList`**: Helper function for listing actors with various filters
- **Actor Type Checkers**: Functions like `IsActorAMonster`, `IsActorAnItem`, etc. that check actor types

## Technical Details

### Cheat Implementation

Most cheat commands follow a similar pattern:
1. Check if cheats are allowed using `CheckCheatmode()`
2. Send a network message using `Net_WriteInt8(DEM_GENERICCHEAT)` followed by a cheat-specific code
3. This ensures cheats work in both single-player and network games

### Console Command Registration

Commands are registered using the `CCMD` macro, which:
- Defines a function with the command name
- Registers the function with the console command system
- Allows the command to be called from the console

### Network Communication

Many commands use network messages to ensure changes are synchronized in multiplayer:
- `DEM_GENERICCHEAT` for basic cheats
- `DEM_GIVECHEAT`, `DEM_TAKECHEAT`, etc. for more complex operations
- Commands that modify the game state use specific message types

### Actor Filtering System

The actor listing commands use a flexible filtering system:
- Type-checking functions determine which actors to include
- Optional class name or TID filters can be applied
- Both listing and counting modes are supported

## Connections with Other Modules

- Interfaces with the network system for multiplayer synchronization
- Uses the console system for command registration and output
- Connects to the actor system for object manipulation and information
- Interacts with the game state system for map changes and skill settings
- Utilizes the save/load system for game state persistence

## Notable Features

- Comprehensive set of debugging tools for developers
- Support for all classic Doom cheats plus many extensions
- Network-aware implementation for multiplayer compatibility
- Detailed actor information display and filtering
- Map navigation and manipulation capabilities
- Script execution interface for advanced game control
