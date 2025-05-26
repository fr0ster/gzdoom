# m_random.h

## File Purpose
This header file defines the random number generator (RNG) system for GZDoom. It provides a high-quality, deterministic random number generation framework based on the Mersenne Twister algorithm (specifically SFMT - SIMD-oriented Fast Mersenne Twister). The system is designed to ensure reproducibility for demos and network play while allowing multiple independent RNG streams for different game subsystems.

## Key Components

### FRandom Class

- **Core RNG Class**: Inherits from SFMTObj to provide high-quality random number generation
- **Constructor Variants**:
  - Nameless constructor for temporary RNGs not stored in savegames
  - Named constructor for persistent RNGs that are saved/restored
- **Random Number Methods**:
  - **`operator()`**: Returns a random number in the range [0,255] or [0,mod)
  - **`Random2`**: Returns the difference between two random numbers
  - **`HitDice`**: Special method for Heretic/Hexen-style random damage calculation
  - **`Random`**: Synonym for operator()

### Real Number Generation

- **Methods for generating floating-point random numbers**:
  - **`GenRand_Real1`**: Generates a random number on [0,1]-real-interval
  - **`GenRand_Real2`**: Generates a random number on [0,1)-real-interval
  - **`GenRand_Real3`**: Generates a random number on (0,1)-real-interval
  - **`GenRand_Res53`**: Generates a random number on [0,1) with 53-bit resolution

### Static RNG Management

- **`StaticClearRandom`**: Initializes all RNGs with the global seed
- **`StaticReadRNGState`/`StaticWriteRNGState`**: Serialization functions for savegames
- **`StaticFindRNG`**: Finds or creates an RNG with a given name
- **`SaveRNGState`/`RestoreRNGState`**: Backup and restore RNG states
- **`StaticPrintSeeds`**: Debug function to print current RNG states

### FCRandom Class

- Derived from FRandom, specifically for client-side random number generation

### Global Variables

- **`rngseed`**: The global seed used to initialize all RNGs
- **`staticrngseed`**: Optional static seed that can be set by the user
- **`use_staticrng`**: Flag to enable the static seed
- **`M_Random`**: Global RNG instance for non-gameplay-affecting randomness

## Technical Details

### RNG Implementation

The random number generator is based on the SFMT (SIMD-oriented Fast Mersenne Twister) algorithm:
- High-quality pseudorandom number generation
- Long period (2^19937-1)
- Good statistical properties
- Fast generation using SIMD instructions

### RNG Initialization

Each RNG is initialized with a unique seed derived from:
- The global `rngseed` value
- The CRC32 hash of the RNG's name
- This ensures each RNG has a different but deterministic starting state

### Savegame Integration

The RNG system supports saving and restoring the state of all RNGs:
- Each named RNG's state is stored in savegames
- When loading, RNGs are restored to their saved state
- New RNGs added since the savegame was created are initialized to their default state

### Demo Compatibility

The system follows Killough's approach from BOOM for demo compatibility:
- Each game subsystem has its own independent RNG
- This prevents changes in one subsystem from affecting random numbers in another
- Ensures that demos remain synchronized even when code changes

## Connections with Other Modules

- Used by virtually all gameplay systems that require randomness
- Integrated with the serialization system for savegames
- Connected to the console command system for debugging
- Used by DECORATE scripts through the StaticFindRNG interface

## Notable Features

- High-quality random number generation using Mersenne Twister
- Multiple independent RNG streams for different game subsystems
- Deterministic behavior for demo recording and network play
- Support for both integer and floating-point random numbers
- Serialization for savegames
- Debug capabilities for tracking RNG states
- Support for static seeds for testing purposes
