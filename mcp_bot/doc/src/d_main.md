# d_main.cpp

## File Purpose
This file serves as the main entry point and core control system for GZDoom. It contains the main program initialization (`D_DoomMain`), the game loop (`D_DoomLoop`), and various supporting functions for game startup, shutdown, and state management. The file handles command-line parameter processing, WAD file loading, subsystem initialization, and the overall flow of the game.

## Key Components

### Main Functions

- `D_DoomMain_Internal()`: The primary initialization function that sets up the game environment
- `D_DoomLoop()`: The main game loop that handles timing, input, and rendering
- `D_InitGame()`: Initializes the game based on the selected IWAD
- `D_Display()`: Handles rendering the current frame, including wipe effects
- `D_DoAdvanceDemo()`: Advances to the next demo sequence
- `D_PageDrawer()`: Draws the intermission pages
- `D_ErrorCleanup()`: Cleans up after a recoverable error
- `D_Cleanup()`: Performs cleanup operations for game shutdown or restart

### Game State Management

- `gamestate`: Global variable tracking the current state of the game (title, level, etc.)
- `gameaction`: Global variable indicating pending game actions
- `wipegamestate`: State to transition to after a screen wipe
- `D_ProcessEvents()`: Processes input events
- `D_DoAnonStats()`: Handles anonymous statistics collection

### Initialization Sequence

1. `D_DoomInit()`: Basic initialization and command-line processing
2. `D_FindIWAD()`: Locates and selects the appropriate IWAD
3. `D_InitGame()`: Game-specific initialization based on the selected IWAD
4. `D_CheckNetGame()`: Sets up networking if needed
5. Various subsystem initializations (sound, graphics, etc.)

### Console Variables (CVARs)

The file defines and manages numerous CVARs, including:
- `dmflags`, `dmflags2`, `dmflags3`: Game behavior flags
- `compatflags`, `compatflags2`: Compatibility settings
- `fraglimit`, `timelimit`: Multiplayer game limits
- `i_timescale`: Game speed control
- `vid_rendermode`: Rendering backend selection

### Command-Line Processing

- `CheckCmdLine()`: Processes command-line arguments
- `ConsiderPatches()`: Handles Dehacked patch loading
- `D_MultiExec()`: Executes configuration files

## Special Features

### Screen Wipes

The file manages screen transition effects (wipes) between different game states:
- `wipestart`: Stores the starting screen for a wipe
- `wipegamestate`: Tracks the game state during a wipe
- `PerformWipe()`: Performs the actual wipe animation

### Demo Playback and Recording

- Functions for demo recording and playback
- Support for timedemo performance testing

### Restart Functionality

- `debug_restart`: Command to restart the game
- State preservation during restarts

### Startup Screen

- Management of the startup/loading screen
- Progress bar updates during initialization

## Connections with Other Modules

- Interfaces with all major subsystems (rendering, sound, input, etc.)
- Manages the game state machine
- Coordinates between the menu system, console, and gameplay
- Handles network initialization and synchronization
- Controls the loading and processing of game resources

## Technical Details

### Game Loop Structure

The main game loop in `D_DoomLoop()` follows this pattern:
1. Start a new frame with `I_StartFrame()`
2. Run game tics with `TryRunTics()`
3. Process events with `D_ProcessEvents()`
4. Render the current frame with `D_Display()`
5. Update music with `S_UpdateMusic()`
6. Repeat until exit or restart

### Error Handling

The file implements comprehensive error handling:
- Try/catch blocks for recoverable errors
- Special handling for VM aborts
- Cleanup procedures for graceful shutdown

### System Integration

- Window title management
- Discord/Steam presence updates
- Performance monitoring and statistics
- System-specific adaptations
