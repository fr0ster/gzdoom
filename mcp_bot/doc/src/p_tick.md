# p_tick.cpp

## File Purpose
This source file implements the core game tick functions for GZDoom, as declared in `p_tick.h`. It contains the main game simulation logic that advances the game state by one logical frame. This file is responsible for coordinating the thinking and movement of all actors in the game world, handling time-based events, and managing the game's pause functionality. It serves as the central hub for the game's update loop.

## Key Components

### Main Ticker Functions

- **`P_Ticker`**: The primary game tick function that advances the game state by one frame.
  - Handles actor thinking and movement
  - Updates level time and map time
  - Processes player inputs and AI
  - Updates special effects and level elements
  - Tracks player velocity statistics

- **`P_CheckTickerPaused`**: Determines if the game ticker should be paused.
  - Checks for menu activity, console state, and other pause conditions
  - Handles sound pausing when the game is paused
  - Returns a boolean indicating the pause state

### Clientside Logic

- **`P_RunClientsideLogic`**: Handles logic that should run every tick, including during prediction.
  - Runs console and menu tickers
  - Processes UI events
  - Updates inventory timers
  - Handles clientside thinkers
  - Updates the status bar
  - Manages automap ticking

### Interpolation Management

- **`P_ClearLevelInterpolation`**: Resets all interpolation data for smooth rendering.
  - Clears actor position and FOV interpolation
  - Resets weapon sprite interpolation
  - Updates the interpolation path for rendering

## Technical Details

### Game Simulation Process

The `P_Ticker` function follows a specific sequence for game simulation:
1. Updates interpolation data for smooth rendering
2. Checks for pause conditions
3. Resets sight counters for AI visibility checks
4. Clears actor interpolation for the current frame
5. Processes particles and special effects
6. Runs player thinking for all active players
7. Triggers the world tick event for script hooks
8. Runs the level tick for level-specific updates
9. Processes all thinkers (actors and other game objects)
10. Updates special sectors and level features
11. Advances the level time counters
12. Tracks player velocity statistics

### Pause Handling

The game can be paused in several situations:
- When the menu is active (except for "no pause" menus)
- When the console is open or animating
- During single-player games only (not in netgames)
- When not playing or recording a demo

When paused, the game:
- Stops sound effects
- Optionally pauses music (based on level settings)
- Skips most game logic but still processes certain visual updates

### Frozen State Management

The game supports a "frozen" state that's separate from pausing:
- Updated every 4 tics to work with certain actor behaviors (like A_Tracer)
- Can be toggled globally or per-level
- Affects actor movement and thinking
- Special handling for player "time freezer" powers

### Multi-Level Support

The ticker supports processing multiple levels simultaneously:
- Iterates through all active levels
- Updates each level's time counters independently
- Processes thinkers for each level
- Maintains separate frozen states for each level

## Connections with Other Modules

- Interfaces with the console system (`C_Ticker`)
- Connected to the menu system (`M_Ticker`)
- Linked to the sound system for pause handling
- Interacts with the renderer for interpolation management
- Processes player inputs and AI through the player thinking system
- Manages level-specific features through the level tick
- Triggers script events through the event manager

## Notable Features

- Support for multi-level processing
- Clientside logic separation for network play
- Interpolation management for smooth rendering
- Frozen state handling for time-stopping effects
- Player velocity statistics tracking
- Event system integration for script hooks
- Comprehensive pause handling
