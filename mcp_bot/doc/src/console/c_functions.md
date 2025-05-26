# c_functions.cpp

## File Purpose
This source file implements the miscellaneous console command helper functions declared in c_functions.h. These functions provide support for console commands that need to interact with game objects, particularly for debugging and information display purposes.

## Key Components

### Actor Information Functions

- **`C_PrintInfo(AActor *target, bool verbose)`**: Implements the function to print detailed information about a specified actor to the console, including class name, health, and other properties.
- **`C_AimLine(FTranslatedLineTarget *t, bool nonshootable)`**: Implements the function to perform an aim trace from the console player's viewpoint and return the target information.
- **`C_PrintInv(AActor *target)`**: Implements the function to print the inventory contents of a specified actor to the console, listing each item with its ID and amount.

## Technical Details

### C_PrintInfo Implementation

This function displays basic information about an actor:
- If the actor is a player, it prints the player's name
- It prints the actor's class name using `GetClass()->TypeName.GetChars()`
- It shows the current health and spawn health values
- If the verbose parameter is true, it calls `PrintMiscActorInfo()` to display additional details

### C_AimLine Implementation

This function uses the game's line attack system to perform a trace:
- It calls `P_AimLineAttack` with the console player's actor as the source
- It uses the player's yaw angle as the direction
- It sets the range to `MISSILERANGE`
- It passes flags to control whether non-shootable objects are included and to ignore auto-aim settings
- The results are stored in the provided `FTranslatedLineTarget` structure

### C_PrintInv Implementation

This function iterates through the inventory chain of the specified actor:
- It first checks if the target is valid
- It prints a header indicating whose inventory is being displayed
- It loops through each inventory item using the linked list structure
- For each item, it prints the class name, inventory ID, current amount, and maximum amount
- It keeps a count of items and displays the total at the end

## Connections with Other Modules

- Interfaces with the player system through `players[consoleplayer].mo`
- Connects to the actor system to access object properties and inventory
- Uses the targeting system through `P_AimLineAttack`
- Called by console commands in `c_cmds.cpp` for debugging and information display

## Notable Features

- Detailed formatting of actor information for console output
- Support for both player and non-player actors
- Comprehensive inventory listing with item counts and amounts
- Integration with the game's aiming and targeting system
- Optional verbose output for more detailed debugging information
