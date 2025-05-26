# serializer.cpp

## File Purpose
This source file implements the serialization system for GZDoom, providing the functionality for saving and loading game states using a JSON-based format. It serves as the backbone of the savegame system, handling the conversion of complex game data structures to and from a serialized format that can be stored and retrieved.

## Key Components

### String Encoding Functions

- **`StringToUnicode`**: Converts a string to a UTF-8 encoded format
- **`UnicodeToString`**: Converts a UTF-8 encoded string back to the original format

### FSerializer Implementation

- **Reader/Writer Management**:
  - **`OpenWriter`**: Initializes the serializer for writing data
  - **`OpenReader`**: Initializes the serializer for reading data (from buffer or compressed data)
  - **`Close`**: Finalizes the serialization process and checks for errors
- **Structured Data Handling**:
  - **`BeginObject`/`EndObject`**: Methods for handling object structures
  - **`BeginArray`/`EndArray`**: Methods for handling array structures
  - **`WriteKey`**: Writes a key for an object property
- **Data Access Methods**:
  - **`GetOutput`**: Retrieves the serialized data as a string
  - **`GetCompressedOutput`**: Retrieves the serialized data in compressed form
  - **`GetString`**: Retrieves a string value from the serialized data
  - **`ArraySize`**: Gets the size of an array in the serialized data

### Object Serialization

- **`WriteObjects`**: Writes all collected objects to the serialized output
- **`ReadObjects`**: Reads and reconstructs objects from the serialized input

### Type-Specific Serialization

- **Primitive Types**: Implementation of serialization for basic types (bool, int, float, etc.)
- **Game-Specific Types**: Implementation of serialization for game types (FTextureID, FSoundID, etc.)
- **Special Types**: Implementation of serialization for special cases (PClass, FFont, Dictionary, etc.)

## Technical Details

### RapidJSON Integration

The implementation uses RapidJSON as its underlying JSON library:
- Configuration options are set for compatibility and precision
- The library is used for both reading and writing JSON data
- Special handling is provided for various JSON data types

### String Handling

The implementation includes special handling for strings:
- UTF-8 encoding is used for all strings in the JSON output
- Double-encoding is used to preserve the original data exactly
- Special functions handle the conversion between formats

### Object Reference System

The object serialization system:
1. Assigns unique indices to objects during serialization
2. Stores these indices in the JSON output
3. Creates objects of the appropriate types during deserialization
4. Maps indices back to the recreated objects
5. Handles error cases like unknown object types

### Compression Support

The implementation includes support for compressed output:
- Uses the zlib/miniz library for compression
- Supports both DEFLATE compression and uncompressed storage
- Includes CRC32 checksums for data integrity

### Error Handling

The implementation includes robust error handling:
- Tracks the number of errors encountered during serialization
- Provides detailed error messages for various failure cases
- Throws errors when critical problems are encountered
- Handles recovery from non-critical errors

## Connections with Other Modules

- Integrates with RapidJSON for JSON parsing and generation
- Connects to the object system for serializing game objects
- Links to the texture system for serializing texture references
- Interfaces with the sound system for serializing sound references
- Uses the compression system for efficient storage
- Connects to the error reporting system for handling errors

## Notable Features

- JSON-based serialization for human-readable and extensible format
- Support for compressed output for efficient storage
- Comprehensive type support for game-specific data structures
- Object reference tracking for complex object graphs
- Error detection and reporting for robust serialization
- Unicode string handling with preservation of original data
- Support for dictionary serialization
- Special handling for function pointers
