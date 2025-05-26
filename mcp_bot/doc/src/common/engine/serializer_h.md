# serializer.h

## File Purpose
This header file defines the serialization system for GZDoom, providing a comprehensive framework for saving and loading game states, object properties, and other data structures. It uses a JSON-based approach to create a flexible, extensible serialization system that can handle complex data types and object relationships.

## Key Components

### FSerializer Class

- **Core Serialization Class**: Provides the main interface for serializing and deserializing data
- **Reader/Writer Management**:
  - **`OpenWriter`**: Initializes the serializer for writing data
  - **`OpenReader`**: Initializes the serializer for reading data
  - **`Close`**: Finalizes and cleans up the serialization process
- **Structured Data Handling**:
  - **`BeginObject`/`EndObject`**: Methods for handling object structures
  - **`BeginArray`/`EndArray`**: Methods for handling array structures
  - **`WriteKey`**: Writes a key for an object property
- **Data Access Methods**:
  - **`GetOutput`**: Retrieves the serialized data as a string
  - **`GetCompressedOutput`**: Retrieves the serialized data in compressed form
  - **`GetString`**: Retrieves a string value from the serialized data
  - **`ArraySize`**: Gets the size of an array in the serialized data

### Helper Structures

- **`NumericValue`**: Structure for handling different numeric types (signed, unsigned, float)
- **`FunctionPointerValue`**: Structure for serializing function pointers

### Serialization Functions

- **Template-based Serialization**: Overloaded `Serialize` functions for different data types
- **Array Serialization**: Methods for serializing arrays of data
- **Object Serialization**: Methods for serializing complex objects

### Utility Functions

- **`nullcmp`**: Helper function to check if a buffer contains only zeros
- **`StringToUnicode`/`UnicodeToString`**: Functions for handling string encoding

## Technical Details

### Serialization Format

The serializer uses JSON as its underlying format:
- Objects are represented as JSON objects with key-value pairs
- Arrays are represented as JSON arrays
- Primitive types are mapped to their JSON equivalents
- Complex types are serialized into structured JSON

### Default Value Handling

The serialization system supports default values:
- When writing, values equal to their defaults can be omitted to save space
- When reading, missing values are left unchanged (keeping their default values)
- The `save_full` flag can force saving all values regardless of defaults

### Object Reference Handling

The serializer handles object references through a special system:
- Objects are assigned unique indices during serialization
- References are stored as these indices
- During deserialization, indices are mapped back to the recreated objects
- Special handling for null references and the `WP_NOCHANGE` sentinel value

### Template Specializations

The system provides specialized serialization for various types:
- Primitive types (bool, int, float, etc.)
- Game-specific types (FTextureID, FSoundID, etc.)
- Container types (TArray, Dictionary, etc.)
- Mathematical types (vectors, angles, etc.)
- Engine types (PClass, FFont, etc.)

## Connections with Other Modules

- Integrates with the object system for serializing game objects
- Connects to the texture system for serializing texture references
- Links to the sound system for serializing sound references
- Interfaces with the compression system for compressed output
- Used by the savegame system for storing game state

## Notable Features

- JSON-based serialization for human-readable and extensible format
- Support for default values to minimize storage requirements
- Comprehensive type support for game-specific data structures
- Object reference tracking for complex object graphs
- Error detection and reporting for robust serialization
- Compression support for efficient storage
- Unicode string handling
- Automatic registration of save handlers through SaveRecord system
