# doomstat.h

## File Purpose
This header file defines the global variables that store the internal state of the GZDoom engine. It serves as a central repository for variables that track game state, user settings, and engine parameters. Theoretically, the complete internal state of the engine should be accessible through the variables collected in this file, though in practice, the state is distributed across multiple modules.

## Key Components

### Game Speed Control

- **`EGameSpeed` Enumeration**: Defines game speed modes
  - `SPEED_Normal`: Standard game speed
  - `SPEED_Fast`: Accelerated game speed
- **`GameSpeed`**: Current game speed setting

### Command Line Parameters

- **`devparm`**: Debug mode flag, set when launched with `-devparm`

### Game Mode and Map Selection

- **`startmap`**: Name of the map to start the game with
- **`autostart`**: Flag to automatically start the game
- **`gameskill`**: Selected skill level (as a CVar)
- **`NextSkill`**: Skill level to use at the next level load

### Multiplayer State

- **`netgame`**: True if more than one player is in the game
- **`multiplayer`**: True for bot games or network games
- **`multiplayernext`**: Flag for fake multiplayer without bots
- **`deathmatch`**: Deathmatch mode flag (as a CVar)
- **`teamplay`**: Team play mode flag (as a CVar)
- **`teamdamage`**: Friendly fire amount (as a CVar)
- **`SinglePlayerClass`**: Player class for single-player games

### Sound Parameters

- **`snd_mastervolume`**: Maximum master volume (as a CVar)
- **`snd_sfxvolume`**: Maximum sound effects volume (as a CVar)
- **`snd_musicvolume`**: Maximum music volume (as a CVar)

### Display State

- **`automapactive`**: Flag indicating if the automap is active
- **`viewactive`**: Flag indicating if the view is active
- **`nodrawers`**, **`noblit`**: Flags to disable rendering
- **`viewwindowx`**, **`viewwindowy`**: View window position
- **`viewheight`**, **`viewwidth`**: View window dimensions
- **`consoleplayer`**: Index of the player taking events (local player)

### Demo Playback/Recording

- **`usergame`**: True if a human player is in control (not a demo)
- **`newdemoname`**, **`newdemomap`**: Name and map for a new demo
- **`demoplayback`**: Flag indicating demo playback
- **`demorecording`**: Flag indicating demo recording
- **`demover`**: Demo version
- **`singledemo`**: Flag to quit after playing a demo from command line
- **`SaveVersion`**: Version number for saved games

### Game State

- **`gametic`**: Game time in tics
- **`playeringame`**: Array of flags indicating which players are active

### Debug and File Handling

- **`debugfile`**: File handle for debug output
- **`precache`**: Flag to load all graphics at level load
- **`singletics`**: Debug flag to cancel adaptiveness
- **`developer`**: Developer mode level (as a CVar)

### Compatibility and Flags

- **`var_friction`**: Variable friction flag (as a CVar)
- **`dmflags`**, **`dmflags2`**, **`dmflags3`**: Deathmatch flags (as CVars)
- **`compatflags`**, **`compatflags2`**: Compatibility flags (as CVars)
- **`infighting`**: Monster infighting behavior (as a CVar)

### DeHackEd Support

- **`DehInfo` Structure**: Contains various parameters for DeHackEd support
  - Health and armor values
  - Weapon and item properties
  - Visual effect settings
  - Gameplay behavior flags

### Miscellaneous

- **`ToggleFullscreen`**: Flag to toggle fullscreen mode
- **`LumpFilterIWAD`**: Filter for IWAD lumps
- **`generic_ui`**: Flag to use generic text output instead of game-specific output

## Technical Details

- Uses `EXTERN_CVAR` macro to declare console variables
- Includes `menustate.h` for menu-related state variables
- Contains a mix of global variables and console variables
- Some arrays have commented-out size specifications (`/*MAXPLAYERS*/`)

## Connections with Other Modules

- Central repository referenced by most game modules
- Provides access to game state for rendering, sound, and gameplay systems
- Connects to the console variable system through `EXTERN_CVAR` declarations
- Supports DeHackEd modifications through the `DehInfo` structure
- Interfaces with the menu system through included menu state variables
