# serializer_doom.h

## File Purpose
This header file defines the Doom-specific serialization system in GZDoom, which is responsible for saving and loading game state to and from files. It extends the base serialization system with specialized functionality for handling Doom-specific data structures and pointers. This system is crucial for implementing save games, network synchronization, and demo recording/playback features in the engine.

## Key Components

### FDoomSerializer Class

- **`FDoomSerializer`**: A specialized serializer class that extends `FSerializer` with Doom-specific functionality.
  - Contains a pointer to the current level being serialized.
  - Overrides methods from the base serializer to handle Doom-specific data types.
  - Provides special handling for sprites, state pointers, and other game-specific elements.

### Specialized Serialization Functions

- **`SerializeArgs`**: Function for serializing special arguments.
  - Handles ACS script numbers in the first argument of ACS specials.
  - Provides special formatting for line special arguments.

- **`SerializeTerrain`**: Function for serializing terrain types.
  - Converts between terrain indices and names.
  - Ensures terrain types are properly saved and restored.

- **`Sprite`**: Method for serializing sprite references.
  - Converts between sprite indices and names.
  - Ensures sprites are properly saved and restored.

- **`StatePointer`**: Method for serializing state pointers.
  - Handles the serialization of actor state pointers.
  - Ensures state references are properly saved and restored.

### Template Specializations

The file includes numerous template specializations for the `Serialize` function, handling various Doom-specific pointer types:

- **Game Structure Pointers**: Specialized serialization for pointers to sectors, lines, sides, vertices, and polyobjects.
- **Actor Class Pointers**: Specialized serialization for pointers to actor classes.
- **Player Pointers**: Specialized serialization for pointers to player structures.
- **String Pointers**: Specialized serialization for pointers to strings.
- **State Pointers**: Specialized serialization for pointers to actor states.
- **Level Pointers**: Specialized serialization for pointers to level structures.
- **Dialogue Node Pointers**: Specialized serialization for pointers to Strife dialogue nodes.
- **Door Animation Pointers**: Specialized serialization for pointers to door animations.

## Technical Details

### Pointer Serialization

- Pointers are serialized by storing their indices or offsets within their respective arrays.
- When reading, the pointers are reconstructed by looking up the indices in the current level's arrays.
- This approach ensures that pointers remain valid even if the memory layout changes between saves.

### Level-Specific Serialization

- The serializer maintains a reference to the current level being serialized.
- This reference is used to resolve pointers to level-specific structures.
- The system enforces that level references are self-contained (no cross-level references).

### Error Handling

- The serializer includes error checking to ensure that pointers are valid.
- Invalid pointers generate error messages and may cause the serialization to fail.
- The system attempts to handle missing or invalid data gracefully when possible.

### Special Case Handling

- ACS script numbers are handled specially, converting between numeric indices and named references.
- Sprite references are serialized using their four-character names rather than indices.
- State pointers are serialized by storing their owning class and offset within that class's state table.

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
- Template specializations for various pointer types to simplify serialization code.
