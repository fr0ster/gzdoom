# m_random.cpp

## File Purpose
This source file implements the random number generator (RNG) system for GZDoom. It provides the functionality for creating, managing, and using multiple independent random number generators based on the Mersenne Twister algorithm. The implementation follows the principles introduced by Lee Killough in BOOM for ensuring demo compatibility and deterministic behavior.

## Key Components

### Global RNG Instances and Variables

- **`M_Random`**: Global RNG instance for non-gameplay-affecting randomness
- **`pr_exrandom`**: Named RNG for general use
- **`rngseed`**: Global seed used to initialize all RNGs
- **`staticrngseed`** and **`use_staticrng`**: Variables for static seed control

### RNG Management Implementation

- **`FRandom` Constructor/Destructor**: Implementation of RNG creation and cleanup
- **`StaticClearRandom`**: Function to initialize all RNGs with the global seed
- **`Init`**: Method to initialize a single RNG with a given seed
- **`StaticWriteRNGState`/`StaticReadRNGState`**: Functions for serializing RNG states
- **`StaticFindRNG`**: Function to find or create an RNG with a given name
- **`SaveRNGState`/`RestoreRNGState`**: Functions to backup and restore RNG states

### Console Commands

- **`rngseed`**: Console command for getting/setting/clearing the static RNG seed
- **`showrngs`**: Debug command to display the current state of all RNGs

### RNG Lists

- **`RNGList` and `CRNGList`**: Linked lists of all regular and client-side RNGs
- **`NewRNGs` and `NewCRNGs`**: Arrays for tracking dynamically created RNGs

## Technical Details

### RNG Creation and Management

The implementation supports two types of RNGs:
1. **Named RNGs**: Created with a name, stored in savegames, and used for gameplay
2. **Nameless RNGs**: Temporary RNGs not stored in savegames

RNGs are organized in linked lists:
- Each RNG has a `Next` pointer to form a linked list
- RNGs are sorted by their name's CRC32 value for efficient lookup
- Client-side RNGs are kept in a separate list from regular RNGs

### RNG Initialization Process

When initializing an RNG:
1. The RNG's name is hashed using CRC32
2. This hash is combined with the global seed to create a unique starting state
3. The SFMT algorithm is initialized with this combined seed
4. This ensures each RNG has a different but deterministic starting state

### Savegame Serialization

The serialization process:
1. Stores the global seed
2. For each named RNG, stores:
   - The CRC32 of its name (for identification)
   - Its current index into the SFMT state array
   - The entire SFMT state array
3. When loading, RNGs are matched by their name CRC

### Dynamic RNG Creation

The `StaticFindRNG` function:
1. Calculates the CRC32 of the requested RNG name
2. Searches the appropriate RNG list for a matching CRC
3. If found, returns the existing RNG
4. If not found, creates a new RNG with that name
5. Stores the new RNG in a cleanup array for proper memory management

## Connections with Other Modules

- Integrates with the serialization system for savegames
- Connects to the console command system for debugging and control
- Used by DECORATE scripts through the StaticFindRNG interface
- Provides random number generation for all gameplay systems

## Notable Features

- Implementation of Killough's approach for demo compatibility
- High-quality random number generation using SFMT
- Support for multiple independent RNG streams
- Efficient RNG lookup by name CRC
- Complete serialization for savegames
- Console commands for debugging and testing
- Support for both regular and client-side RNGs
- Dynamic RNG creation for DECORATE scripts
