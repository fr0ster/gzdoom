# c_functions.h

## File Purpose
This header file defines miscellaneous console command helper functions for GZDoom. These functions provide support for console commands that need to interact with game objects, particularly for debugging and information display purposes.

## Key Components

### Actor Information Functions

- **`C_PrintInv(AActor *target)`**: Prints the inventory contents of a specified actor to the console, listing each item with its ID and amount.
- **`C_AimLine(FTranslatedLineTarget *t, bool nonshootable)`**: Performs an aim trace from the console player's viewpoint and returns the target information.
- **`C_PrintInfo(AActor *target, bool verbose)`**: Prints detailed information about a specified actor to the console, including class name, health, and other properties.

### Supporting Structures

- **`FTranslatedLineTarget`**: Forward declaration of a structure used to store information about what an aim trace hits.

## Technical Details

### Implementation Approach

These functions serve as utility functions for console commands, providing a way to extract and display information about game objects. They are designed to be called from console command handlers to provide debugging information to the user.

### C_PrintInv Implementation

This function iterates through the inventory chain of the specified actor and prints information about each item, including:
- The class name of the item
- The item's inventory ID
- The current amount and maximum amount of the item

### C_AimLine Implementation

This function uses the game's line attack system to perform a trace from the console player's viewpoint, with options to:
- Include or exclude non-shootable objects
- Ignore auto-aim settings
- Return detailed information about what was hit

### C_PrintInfo Implementation

This function displays basic information about an actor, with options for:
- Showing player name if the actor is a player
- Displaying the actor's class name
- Showing current health and spawn health
- Optionally showing additional miscellaneous actor information

## Connections with Other Modules

- Used by console commands in `c_cmds.cpp` for debugging and information display
- Interfaces with the actor system to access object properties
- Connects to the player system to get player information
- Utilizes the targeting system for aim tracing functionality

## Notable Features

- Support for detailed actor information display
- Inventory listing capabilities
- Integration with the game's aiming and targeting system
- Verbose output options for debugging
