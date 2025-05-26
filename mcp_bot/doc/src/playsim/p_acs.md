# p_acs.cpp

## File Purpose
This implementation file provides the core functionality for the ACS (Action Code Script) system in GZDoom. It implements the classes and structures defined in `p_acs.h`, providing the actual execution engine for ACS scripts, variable management, string handling, and the overall ACS virtual machine. This file is essential for the interactive and dynamic elements of maps created with ACS scripting.

## Key Components

### ACS Virtual Machine
The core of the file is the ACS virtual machine implementation, which interprets and executes ACS bytecode. This includes:

- Opcode handlers for all ACS instructions
- Stack management for script execution
- Function call and return mechanisms
- Variable access and manipulation
- Array operations
- String handling
- Mathematical and logical operations

### FBehavior Implementation
The `FBehavior` class methods are implemented here, providing functionality for:

- Loading ACS modules from WAD lumps
- Parsing ACS bytecode and data structures
- Managing script execution
- Handling function calls
- Accessing and modifying variables and arrays
- String table management
- Serialization for save games

### FBehaviorContainer Implementation
The `FBehaviorContainer` structure methods are implemented, providing:

- Module loading and management
- Default module initialization
- Script lookup across multiple modules
- Module serialization
- String lookup across modules

### ACSStringPool Implementation
The `ACSStringPool` class methods are implemented, handling:

- String storage and retrieval
- String hashing for efficient lookup
- Reference counting and garbage collection
- Level-specific string locking
- Serialization of strings

### DACSThinker Implementation
The `DACSThinker` class methods are implemented, managing:

- Script execution scheduling
- Script termination
- Script suspension and resumption
- Script serialization
- Script debugging

### DLevelScript Class
While not declared in the header, this file likely implements the `DLevelScript` class, which represents an instance of a running ACS script. This includes:

- Script state management
- Local variable storage
- Script execution context
- Activation and deactivation
- Suspension and resumption
- Serialization

## Implementation Details

### Script Execution Flow
The ACS virtual machine follows a specific execution flow:

1. Scripts are loaded from ACS modules in WAD files
2. Scripts are triggered by map events, line specials, or other scripts
3. The `DACSThinker` schedules scripts for execution
4. Each tick, the virtual machine executes a certain number of instructions for each active script
5. Scripts can suspend execution to wait for events or delays
6. When a script completes, it is removed from the active script list

### Variable Management
The implementation handles various variable scopes:

- Global variables (persist across all maps)
- Map variables (persist within a single map)
- Local variables (exist only within a script instance)
- World variables (accessible by all scripts)
- Global arrays (dynamic arrays with global scope)

Each scope has specific serialization and access mechanisms.

### String Management
The string pool implementation provides efficient string handling:

- Strings are stored in a hash table for quick lookup
- Reference counting prevents premature deletion
- Garbage collection removes unused strings
- Strings can be locked to specific map levels
- String serialization preserves strings across save/load

### Script Types and Events
The implementation handles various script types, which determine when scripts are automatically executed:

- Open scripts (executed when the level starts)
- Respawn scripts (executed when a player respawns)
- Death scripts (executed when a player dies)
- Enter scripts (executed when a player enters a sector)
- And many more for different game events

### Multiplayer Considerations
The implementation includes special handling for multiplayer games:

- Network-safe scripts (marked with `SCRIPTF_Net`)
- Client-side scripts (marked with `SCRIPTF_ClientSide`)
- Synchronization of script execution across clients
- Player-specific script activators

### Error Handling
The implementation includes robust error handling:

- Bounds checking for array access
- Stack overflow prevention
- Invalid instruction detection
- Division by zero protection
- Infinite loop detection

## Connections with Other Modules
- Interfaces with the `DThinker` system for script execution scheduling
- Connects to the level system for map-specific scripts and variables
- Interfaces with the actor system for script activators and targets
- Connects to the serialization system for save/load functionality
- Used by line specials to trigger scripts
- Interfaces with the console variable system for script-accessible CVARs
- Connects to the HUD system for displaying script-generated messages
- Interfaces with the sound system for script-triggered sounds
- Connects to the sector system for script-controlled sector effects
