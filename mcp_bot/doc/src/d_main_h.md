# d_main.h

## File Purpose
This header file defines the core interfaces and data structures for GZDoom's main control system. It contains declarations for the main program functions, game state management, IWAD handling, and various utility functions. The file serves as a bridge between the system-specific code and the game engine, providing essential structures and functions that control the overall flow of the game.

## Key Components

### Core Functions

- **`D_DoomMain()`**: The main entry point for the game (referenced but not declared in this file)
- **`D_Display()`**: Handles rendering the current frame
- **`D_PageTicker()`**: Updates the intermission page state
- **`D_PageDrawer()`**: Draws the intermission pages
- **`D_AdvanceDemo()`**: Advances to the next demo sequence
- **`D_StartTitle()`**: Starts the title screen sequence
- **`D_ToggleHud()`**: Toggles the heads-up display on/off

### Game State Management

- **`advancedemo`**: Boolean flag indicating if the demo should advance
- **`D_DrawIcon`**: Pointer to an icon to draw during the next screen refresh
- **`r_renderercaps`**: Stores renderer capabilities to avoid per-frame processing
- **`CRestartException`**: Exception class used for game restarts

### IWAD Management

#### FIWADInfo Structure

A comprehensive structure that stores information about an IWAD file:

- **Basic Information**: Name, autoload section name, configuration name
- **Visual Properties**: Foreground and background colors for the title banner
- **Game Type**: Which game the IWAD represents (Doom, Heretic, etc.)
- **Startup Configuration**: Startup type, required files, map info
- **Content Management**: Lumps to load or delete, additional WADs to load
- **Feature Flags**: Various flags controlling game behavior
- **Resource Control**: Settings for widescreen, brightmaps, and lights
- **Platform Integration**: Discord and Steam app IDs

#### FFoundWadInfo Structure

Stores information about a discovered WAD file:
- **`mFullPath`**: Full path to the WAD file
- **`mRequiredPath`**: Path to a required dependency WAD
- **`mInfoIndex`**: Index into the IWAD info array

#### FIWadManager Class

Manages the discovery, validation, and selection of IWAD files:

- **`ParseIWadInfo()`**: Parses IWADINFO lumps
- **`ScanIWAD()`**: Examines an IWAD to determine its type
- **`CheckIWADInfo()`**: Validates an IWAD by checking for the IWADINFO lump
- **`IdentifyVersion()`**: Identifies the version of an IWAD
- **`FindIWAD()`**: Locates an appropriate IWAD for the game
- **`GetAutoname()`**: Retrieves the autoload name for an IWAD
- **`GetIWadFlags()`**: Gets the flags for an IWAD

### Renderer Utilities

- **`V_IsHardwareRenderer()`**: Checks if the hardware renderer is active
- **`V_IsTrueColor()`**: Checks if the renderer is using true color

### Miscellaneous

- **`CheckCheatmode()`**: Verifies if cheats are allowed in the current game state

## Technical Details

- Uses conditional compilation (`#ifndef NO_SWRENDERER`) to handle different build configurations
- Defines the `vid_rendermode` CVAR for selecting the rendering backend
- Includes a restart exception mechanism for handling game restarts
- Provides structures for IWAD management that support various game types

## Connections with Other Modules

- Interfaces with the rendering system through `D_Display()` and renderer-related functions
- Connects to the game state system through demo and page management functions
- Provides IWAD management functionality used by the resource loading system
- Links to the HUD system through the toggle function
- Interacts with the cheat system through `CheckCheatmode()`
