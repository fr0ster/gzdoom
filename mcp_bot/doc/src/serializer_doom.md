# serializer_doom.cpp

## File Purpose
This source file implements the Doom-specific serialization system in GZDoom, which extends the base serialization system to handle game-specific data structures and pointers. It provides the functionality needed for saving and loading game state, including complex structures like actors, sectors, lines, and game states. This implementation is crucial for features such as save games, network synchronization, and demo recording/playback in the engine.

## Key Components

### FDoomSerializer Implementation

- **`CloseReaderCustom`**: Overrides the base class method to clean up thinkers that weren't properly linked.
  - Prevents memory leaks by destroying orphaned thinker objects.
  - Ensures that objects don't survive level transitions inappropriately.

- **`Sprite`**: Implements sprite serialization.
  - Converts between sprite indices and four-character names.
  - Handles lookup of sprites by name when deserializing.

- **`StatePointer`**: Implements state pointer serialization.
  - Delegates to the appropriate serialization function.
  - Handles return code management.

### Specialized Serialization Functions

- **`SerializeArgs`**: Implements serialization for line special arguments.
  - Handles ACS script numbers specially, converting between numeric indices and named references.
  - Formats arguments as an array for JSON storage.
  - Provides error checking during deserialization.

- **`SerializeTerrain`**: Implements serialization for terrain types.
  - Converts between terrain indices and names using the terrain system.
  - Ensures terrain types are properly saved and restored.

### Template Specializations

The file implements numerous template specializations for the `Serialize` function, handling various Doom-specific pointer types:

- **Game Structure Pointers**: Implementation for serializing pointers to sectors, lines, sides, vertices, and polyobjects.
  - Uses array indices to represent pointers.
  - Validates level context during serialization.

- **Actor Class Pointers**: Implementation for serializing pointers to actor classes.
  - Uses class names for serialization.
  - Handles null pointers appropriately.

- **Player Pointers**: Implementation for serializing pointers to player structures.
  - Uses player indices for serialization.

- **State Pointers**: Implementation for serializing pointers to actor states.
  - Stores the owning class and state index.
  - Handles special cases like Dehacked states.
  - Provides error reporting for invalid states.

- **Dialogue Node Pointers**: Implementation for serializing pointers to Strife dialogue nodes.
  - Uses node indices for serialization.
  - Validates indices during deserialization.

- **String Pointers**: Implementation for serializing pointers to strings.
  - Handles allocation of string memory during deserialization.
  - Manages null pointers appropriately.

- **Level Pointers**: Implementation for serializing pointers to level structures.
  - Enforces that level references are self-contained.
  - Prevents cross-level references.

## Technical Details

### Pointer Serialization Approach

- Pointers are serialized by storing their indices or offsets within their respective arrays.
- When reading, the pointers are reconstructed by looking up the indices in the current level's arrays.
- This approach ensures that pointers remain valid even if the memory layout changes between saves.

### Error Handling

- The implementation includes extensive error checking to ensure valid serialization.
- Invalid pointers or data generate error messages with appropriate context.
- The system attempts to handle missing or invalid data gracefully when possible.

### Memory Management

- String serialization allocates memory from appropriate pools to ensure proper lifetime.
- Thinker cleanup prevents memory leaks from orphaned objects.
- The system ensures that all pointers are properly resolved or nullified.

### Special Case Handling

- ACS script numbers are handled specially, converting between numeric indices and named references.
- Sprite references are serialized using their four-character names rather than indices.
- State pointers include information about their owning class to ensure proper resolution.
- Level pointers are validated to prevent cross-level references.

## Connections with Other Modules

- Extends the base serialization system defined in `serializer.h`.
- Interfaces with the level system to access level-specific data structures.
- Connects to the actor system for state and class serialization.
- Interacts with the terrain system for terrain type serialization.
- Used by the save game system to store and restore game state.
- Used by the demo recording system to capture and replay game events.

## Notable Features

- Support for serializing complex game structures and pointers.
- Handling of special cases like ACS script numbers and sprite references.
- Error checking to ensure valid serialization and deserialization.
- Level-specific context to ensure proper pointer resolution.
- Memory management to prevent leaks and ensure proper object lifetime.
- Template specializations for various pointer types to simplify serialization code.
