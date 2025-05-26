# p_saveg.h

## File Purpose
This header file defines the interface for the game state serialization system in GZDoom. It provides the declarations for functions that handle saving and loading game state, particularly focusing on persistent storage and archiving of game data. This system is crucial for save game functionality and for preserving game state during level transitions in hub-based games.

## Key Components

### Function Declarations

- **`P_DestroyThinkers`**: Destroys all thinkers in the game world.
  - Takes a boolean parameter `hubLoad` to indicate whether the destruction is happening during a hub level transition.
  - When `hubLoad` is true, certain thinkers may be preserved for continuity between hub levels.

- **`P_ReadACSDefereds`**: Reads deferred ACS scripts from a serializer.
  - These are scripts that were scheduled to run but have not yet been executed.
  - Used during game loading to restore the state of pending ACS scripts.

- **`P_WriteACSDefereds`**: Writes deferred ACS scripts to a serializer.
  - Used during game saving to store the state of pending ACS scripts.

## Technical Details

### Serialization System

- The file introduces the `FSerializer` class (defined elsewhere) which is the core of GZDoom's serialization system.
- This class provides methods for reading and writing structured data to and from archives.
- The serialization system supports both binary and text-based formats, with the latter being useful for debugging.

### Thinker Management

- Thinkers are objects that perform actions each game tick, such as moving actors, operating platforms, or managing game logic.
- The `P_DestroyThinkers` function is used to clean up these objects when transitioning between levels or loading a saved game.
- Special handling is needed during hub transitions to preserve certain thinkers that should persist across levels.

### ACS Script Handling

- ACS (Action Code Script) is GZDoom's scripting system for level interactivity.
- Deferred scripts are those that have been triggered but are scheduled to run at a later time.
- The `P_ReadACSDefereds` and `P_WriteACSDefereds` functions ensure these pending scripts are properly saved and restored.

## Connections with Other Modules

- Works closely with the `p_saveg.cpp` implementation file which contains the actual serialization code.
- Interfaces with the thinker system for managing active game objects.
- Connects to the ACS scripting system for handling deferred scripts.
- Used by the game's save/load system and level transition code.
- Relies on the `FSerializer` class from the serialization framework.

## Notable Features

- Support for hub-based level transitions, where certain game state must persist between levels.
- Integration with the ACS scripting system for preserving script state.
- Part of a comprehensive serialization system that can handle complex game state.
