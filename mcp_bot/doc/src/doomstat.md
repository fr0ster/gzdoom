# doomstat.cpp

## File Purpose
This source file implements the global state variables declared in `doomstat.h`. It serves as the central location for initializing and defining the global variables that track the internal state of the GZDoom engine. While `doomstat.h` declares these variables, this file provides their actual definitions and initial values.

## Key Components

### Version Control

- **`SaveVersion`**: Defines the version number used for saved games, allowing the engine to handle compatibility between different versions of saved game files.

### Game Speed

- **`GameSpeed`**: Initializes the game speed setting to `SPEED_Normal`, which is the default speed for gameplay.

### Skill Management

- **`NextSkill`**: Initialized to -1, this variable stores the skill level to use at the next level load. The -1 value indicates that no specific skill level has been requested for the next level.

### Player Class Management

- **`SinglePlayerClass`**: An array that stores the selected player class for each player in single-player games. This is particularly important for games like Hexen that have multiple character classes.

### IWAD Filtering

- **`LumpFilterIWAD`**: A string variable used to filter lumps from the IWAD (Internal WAD) file. This helps control which resources from the base game are loaded or excluded.

## Technical Details

- The file includes necessary headers for string handling, system interfaces, and level management.
- It defines global variables with their initial values, establishing the default state of the engine.
- The implementation is minimal, focusing only on variable definitions without additional logic.

## Connections with Other Modules

- Implements the variables declared in `doomstat.h`, which is included by most other modules.
- Includes `stringtable.h` for string handling capabilities.
- Includes `i_system.h` for system-level interfaces.
- Includes `g_level.h` and `g_levellocals.h` for level-related functionality.
- Provides the foundation for the global state that is accessed and modified by various game systems.

## Notable Aspects

- The file is intentionally simple, containing only variable definitions without complex logic.
- Many variables declared in `doomstat.h` are not defined here, as they are defined elsewhere in the codebase or are console variables (CVars) that are registered through the console variable system.
- The `MAXPLAYERS` constant is used to dimension the `SinglePlayerClass` array, ensuring it can accommodate the maximum number of players supported by the engine.
