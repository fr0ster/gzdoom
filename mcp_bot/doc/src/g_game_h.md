# g_game.h

## File Purpose
This header file defines the core game management functions and structures for GZDoom. It provides the interface for high-level game operations such as loading and saving games, demo recording and playback, handling player input, and managing game state transitions. The file serves as a central hub for coordinating the various subsystems that make up the game loop.

## Key Components

### Game State Management

- **`wipegamestate`**: External variable that controls screen wipe transitions between game states.
- **`G_Ticker`**: Main game tick function that advances the game state by one frame.
- **`G_Responder`**: Event handler that processes player input events.
- **`FSTATE_*` Constants**: Define different states of the game flow (ending game, changing level, etc.).

### Demo Recording and Playback

- **`G_RecordDemo`**: Starts recording a gameplay demo.
- **`G_BeginRecording`**: Initializes demo recording with a specified starting map.
- **`G_PlayDemo`**: Plays back a recorded demo.
- **`G_TimeDemo`**: Plays a demo while timing it (for benchmarking).
- **`G_CheckDemoStatus`**: Verifies the current state of demo playback.

### Save and Load Game Functions

- **`G_LoadGame`**: Loads a saved game from a file.
- **`G_DoLoadGame`**: Performs the actual loading operation.
- **`G_SaveGame`**: Saves the current game state to a file.
- **`G_DoQuickSave`**: Performs a quick save operation.
- **`G_CheckSaveGameWads`**: Verifies that the required WAD files are available for a saved game.

### Player Management

- **`G_PlayerFinishLevel`**: Handles player state when completing a level.
- **`G_DoPlayerPop`**: Removes a player from the game.
- **`G_AddViewPitch`**: Adjusts the player's view pitch (looking up/down).
- **`G_AddViewAngle`**: Adjusts the player's view angle (looking left/right).
- **`G_GetUserCVar`**: Retrieves a console variable for a specific player.

### Miscellaneous Functions

- **`G_ScreenShot`**: Captures a screenshot of the game.
- **`G_StartSlideshow`**: Initiates a slideshow sequence.
- **`RunIntermission`**: Runs the intermission sequence between levels.

### Global Variables

- **`SendItemUse`**, **`SendItemDrop`**: Pointers to actors for item use and drop operations.
- **`SendItemDropAmount`**: Amount of items to drop.

## Technical Details

- Uses enumerations for game states and level transition types.
- Includes function declarations for game loop management.
- Defines flags for player state transitions (`PPS_*` constants).
- Provides interface for demo recording and playback.
- Includes serialization support for save games.

## Connections with Other Modules

- Includes `dobjgc.h` for garbage collection of game objects.
- Includes `name.h` for name handling.
- Includes `gamestate.h` for game state definitions.
- References `event_t` structure for input event handling.
- References `AActor` class for game object interactions.
- References `FLevelLocals` structure for level-specific data.
- Uses `FSerializer` for save game serialization.
- Uses `FBaseCVar` for console variable access.
- References `DIntermissionController` and `level_info_t` for level transitions.
