# p_tick.h

## File Purpose
This header file defines the core game tick functions for GZDoom. It provides the interface for the main game tick processing, which is responsible for advancing the game state by one logical frame. The functions declared here are essential for the game's update loop, handling the thinking and movement of all actors (monsters and players) in the game world.

## Key Components

### P_Ticker Function

- **`P_Ticker`**: The main tick function for the game's play simulation.
  - Called by `C_Ticker` in the main game loop.
  - Processes one game tick (frame) of gameplay.
  - Handles all thinking and movement of monsters and players.
  - Can trigger game exit through `G_PlayerExited`.

### P_CheckTickerPaused Function

- **`P_CheckTickerPaused`**: Checks if the game ticker should be paused.
  - Returns a boolean indicating whether the ticker is currently paused.
  - Used to determine if game logic updates should be skipped for the current frame.

## Technical Details

### Ticker Operation

The `P_Ticker` function is the heart of the game's simulation, responsible for:
- Updating player states and processing player commands
- Running AI routines for monsters and other actors
- Processing actor movement and collision detection
- Handling actor interactions and damage
- Updating sector specials and other level elements
- Managing game state transitions

### Pause Handling

The `P_CheckTickerPaused` function provides a way to check if the game simulation should be paused. This can occur due to:
- The game being explicitly paused by the player
- Menu screens being active
- Certain game events that require pausing the simulation
- Multiplayer synchronization issues

## Connections with Other Modules

- Called by the main ticker system (`C_Ticker`) in the game loop
- Interfaces with the game state management system (`G_PlayerExited`)
- Connected to the actor thinking and movement systems
- Linked to the player input processing system
- Used by the main game loop to advance the game state

## Notable Features

- Simple interface for the complex task of advancing the game state
- Support for pausing the game simulation when needed
- Integration with the game's exit mechanism
- Central role in the game's update loop
