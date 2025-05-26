# d_protocol.h

## File Purpose
This header file defines the network protocol used by GZDoom for multiplayer games and demo recording/playback. It specifies the format of network messages, demo file structures, and player commands. The file serves as the foundation for GZDoom's networking system, ensuring consistent communication between clients and proper recording/playback of demos.

## Key Components

### Demo File Format

- **IFF-Style Chunk Identifiers**:
  - `FORM_ID`: Standard IFF container format identifier
  - `ZDEM_ID`: ZDoom demo file identifier
  - `ZDHD_ID`: Demo header chunk identifier
  - `VARS_ID`: Game variables chunk identifier
  - `UINF_ID`: User information chunk identifier
  - `COMP_ID`: Compatibility information chunk identifier
  - `BODY_ID`: Demo body (commands) chunk identifier
  - `NETD_ID`: Network data chunk identifier
  - `WEAP_ID`: Weapon information chunk identifier

- **Demo Header Structure**:
  - `zdemoheader_s`: Contains version information, map name, RNG seed, and console player number

### Player Command Structure

- **`usercmd_t` Structure**: Represents a player's input for a single game tic
  - `buttons`: Button state flags
  - `pitch`: Up/down view angle
  - `yaw`: Left/right view angle
  - `roll`: Tilt angle
  - `forwardmove`: Forward/backward movement
  - `sidemove`: Left/right movement
  - `upmove`: Up/down movement (jumping/crouching)

- **Command Transmission Flags**:
  - `UCMDF_*` constants: Indicate which fields are present in a transmitted command

### Network Commands

- **`EDemoCommand` Enumeration**: Defines all possible network commands
  - Movement commands (`DEM_USERCMD`, `DEM_EMPTYUSERCMD`)
  - Game state commands (`DEM_MUSICCHANGE`, `DEM_CHANGEMAP`)
  - UI commands (`DEM_PRINT`, `DEM_CENTERPRINT`)
  - Cheat commands (`DEM_GENERICCHEAT`, `DEM_GIVECHEAT`)
  - Inventory commands (`DEM_INVUSE`, `DEM_INVDROP`)
  - Player interaction commands (`DEM_SAY`, `DEM_DROPPLAYER`)
  - Special commands (`DEM_RUNSCRIPT`, `DEM_RUNSPECIAL`)
  - Demo control commands (`DEM_STOP`)

- **`ECheatCommand` Enumeration**: Defines all possible cheat commands
  - God mode cheats (`CHT_GOD`, `CHT_BUDDHA`)
  - Movement cheats (`CHT_NOCLIP`, `CHT_FLY`)
  - Item cheats (`CHT_IDKFA`, `CHT_IDFA`, `CHT_KEYS`)
  - Power-up cheats (`CHT_POWER`, `CHT_BEHOLDV`, etc.)
  - Special effect cheats (`CHT_MORPH`, `CHT_FREEZE`)

### Data Serialization

- **Chunk Management**:
  - `StartChunk()`: Begins a new chunk in the data stream
  - `FinishChunk()`: Finalizes a chunk in the data stream
  - `SkipChunk()`: Skips over a chunk in the data stream

- **User Command Serialization**:
  - `PackUserCmd()`: Compresses a user command for network transmission
  - `UnpackUserCmd()`: Decompresses a user command from network data
  - `WriteUserCmdMessage()`: Writes a user command to a network message
  - `ReadUserCmdMessage()`: Reads a user command from a network message
  - `SkipUserCmdMessage()`: Skips over a user command in a network message

- **Primitive Type Serialization**:
  - Functions for reading/writing various data types:
    - `ReadInt8()`, `WriteInt8()`
    - `ReadInt16()`, `WriteInt16()`
    - `ReadInt32()`, `WriteInt32()`
    - `ReadInt64()`, `WriteInt64()`
    - `ReadFloat()`, `WriteFloat()`
    - `ReadDouble()`, `WriteDouble()`
    - `ReadString()`, `WriteString()`
    - `ReadStringConst()`

## Technical Details

- Uses big-endian IDs for IFF chunk identification regardless of host system endianness
- Implements delta compression for user commands to reduce network traffic
- Provides a comprehensive set of network commands for all game actions
- Supports both network play and demo recording/playback with the same protocol

## Connections with Other Modules

- Used by `d_net.cpp` for network message processing
- Provides the foundation for demo recording and playback
- Interfaces with the input system for player command handling
- Connects to the game state system for executing commands
- Supports the cheat system through command definitions
