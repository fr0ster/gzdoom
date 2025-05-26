# g_game.cpp

## File Purpose
This source file implements the core game management functions for GZDoom. It handles game state management, player input processing, demo recording and playback, save/load functionality, and the main game loop. This file serves as the central hub for coordinating the various subsystems that make up the game engine.

## Key Components

### Game State Management

- **Game Action Handlers**: Functions like `G_DoNewGame`, `G_DoLoadGame`, `G_DoPlayDemo`, etc., that handle transitions between different game states.
- **Game Ticker**: The `G_Ticker` function that advances the game state by one frame, processing player commands and calling the appropriate subsystem tickers.
- **Game Responder**: The `G_Responder` function that processes player input events and routes them to the appropriate handlers.

### Player Management

- **Player Spawning**: Functions for spawning players in deathmatch, cooperative, and single-player modes.
- **Player Rebirth**: Handling player respawning after death.
- **Player Input**: Processing of player movement, button presses, and other inputs.
- **Player State**: Management of player state transitions (alive, dead, reborn, etc.).

### Demo Recording and Playback

- **Demo Recording**: Functions for recording gameplay demos, including `G_RecordDemo` and `G_WriteDemoTiccmd`.
- **Demo Playback**: Functions for playing back recorded demos, including `G_PlayDemo` and `G_ReadDemoTiccmd`.
- **Demo File Format**: Implementation of the IFF-based demo file format with various chunks for game data.

### Save/Load System

- **Game Saving**: Functions for saving the current game state to a file, including `G_DoSaveGame` and `G_SaveGame`.
- **Game Loading**: Functions for loading a saved game, including `G_DoLoadGame` and `G_LoadGame`.
- **Autosave**: Implementation of automatic game saving at key points.
- **Quicksave**: Implementation of quick save/load functionality.

### Console Commands

- **Movement Commands**: Commands for player movement, weapon selection, inventory management, etc.
- **Demo Commands**: Commands for recording and playing demos.
- **Save/Load Commands**: Commands for saving and loading games.
- **Spy Mode**: Commands for switching between player views in multiplayer.

### Input Processing

- **Button Mapping**: Processing of button inputs from keyboard, mouse, and joystick.
- **Movement Processing**: Conversion of input events to player movement commands.
- **View Angle Adjustment**: Functions for adjusting player view angles based on input.

## Technical Details

### Game Loop

- The game loop is driven by the `G_Ticker` function, which processes player commands, advances the game state, and calls the appropriate subsystem tickers.
- The `G_Responder` function handles input events and routes them to the appropriate handlers.

### Player Command Processing

- Player commands are built from input events in `G_BuildTiccmd`.
- Commands are then processed and applied to the player's state.
- Special commands like pause, save, item use, etc., are handled separately.

### Demo System

- Demos are recorded as IFF FORM files with various chunks for game data.
- The `ZDEM` format includes headers, player info, console variables, and the actual gameplay data.
- Demo playback simulates player input based on the recorded commands.

### Save System

- Saves are stored as ZIP files containing JSON data and screenshots.
- The save system captures the entire game state, including player positions, monster states, and level data.
- Autosaves are created automatically at key points in the game.

## Connections with Other Modules

- Includes numerous headers from various subsystems, indicating its central role in the engine.
- Interacts with the player, level, rendering, input, and network subsystems.
- Calls into the scripting system for certain events.
- Manages the game state transitions that affect all other subsystems.

## Notable Features

- Support for demo recording and playback.
- Comprehensive save/load system with autosave and quicksave.
- Multiplayer support with player spawning and state management.
- Spy mode for viewing the game through other players' eyes.
- Console commands for various game actions.
- Support for different input devices (keyboard, mouse, joystick).
