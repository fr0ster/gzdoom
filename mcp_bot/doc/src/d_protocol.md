# d_protocol.cpp

## File Purpose
This file implements the network protocol functions defined in `d_protocol.h`. It provides the core functionality for serializing and deserializing network messages, handling user commands, and managing IFF-style chunk data for GZDoom's networking and demo recording/playback system. The file contains low-level binary data manipulation routines that form the foundation of GZDoom's network communication.

## Key Components

### Data Serialization Functions

- **Basic Type Reading**:
  - `ReadInt8()`: Reads an 8-bit integer from a stream
  - `ReadInt16()`: Reads a 16-bit integer from a stream
  - `ReadInt32()`: Reads a 32-bit integer from a stream
  - `ReadInt64()`: Reads a 64-bit integer from a stream
  - `ReadFloat()`: Reads a 32-bit floating-point value from a stream
  - `ReadDouble()`: Reads a 64-bit floating-point value from a stream
  - `ReadString()`: Reads a null-terminated string from a stream and returns a copy
  - `ReadStringConst()`: Reads a null-terminated string from a stream without copying

- **Basic Type Writing**:
  - `WriteInt8()`: Writes an 8-bit integer to a stream
  - `WriteInt16()`: Writes a 16-bit integer to a stream
  - `WriteInt32()`: Writes a 32-bit integer to a stream
  - `WriteInt64()`: Writes a 64-bit integer to a stream
  - `WriteFloat()`: Writes a 32-bit floating-point value to a stream
  - `WriteDouble()`: Writes a 64-bit floating-point value to a stream
  - `WriteString()`: Writes a null-terminated string to a stream

### User Command Processing

- **Command Serialization**:
  - `PackUserCmd()`: Compresses a user command for efficient network transmission
  - `UnpackUserCmd()`: Decompresses a user command from network data
  - `WriteUserCmdMessage()`: Creates a complete network message for a user command
  - `SkipUserCmdMessage()`: Skips over a user command message in a stream
  - `ReadUserCmdMessage()`: Reads a user command message from a stream
  - `RunPlayerCommands()`: Executes all commands for a player for a specific tic

- **Command Optimization**:
  - Delta compression to only transmit changed fields
  - Bit-packing for button states to reduce bandwidth usage
  - Special handling for empty commands

### IFF Chunk Management

- **Chunk Handling**:
  - `StartChunk()`: Begins a new IFF-style chunk in a data stream
  - `FinishChunk()`: Finalizes an IFF-style chunk and handles padding
  - `SkipChunk()`: Skips over an unknown chunk in a data stream

### Serialization Support

- **Modern Serialization**:
  - `Serialize()`: Handles serialization of user commands for the modern serialization system
  - Provides human-readable text format for saved games and demos

## Technical Details

### Binary Data Handling

- Uses big-endian format for network transmission regardless of host endianness
- Implements efficient bit-packing for button states
- Handles floating-point values through union-based type punning
- Ensures proper alignment and padding for IFF chunks

### Command Compression

- Implements delta compression by only transmitting fields that have changed
- Uses a flags byte to indicate which fields are present in the message
- Special handling for button states with variable-length encoding
- Optimizes empty commands with a special message type

### Demo Recording Support

- Provides functions for creating and managing IFF chunks in demo files
- Handles padding for odd-sized chunks to maintain alignment
- Supports skipping unknown chunks for forward compatibility

## Connections with Other Modules

- Implements the protocol defined in `d_protocol.h`
- Used by `d_net.cpp` for network message processing
- Provides the foundation for demo recording and playback
- Interfaces with the input system for player command handling
- Supports the modern serialization system for saved games
