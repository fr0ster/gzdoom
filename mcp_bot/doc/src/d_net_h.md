# d_net.h

## File Purpose
This header file defines the networking infrastructure for GZDoom's multiplayer functionality. It provides structures and functions for handling network communication between clients and servers, managing game state synchronization, and implementing reliable packet transmission with retransmission capabilities. The file serves as the core of GZDoom's networking system, enabling players to participate in multiplayer games.

## Key Components

### Enumerations

- **`EChatType`**: Defines chat visibility modes:
  - `CHAT_DISABLED`: Chat is disabled
  - `CHAT_TEAM_ONLY`: Only team chat is enabled
  - `CHAT_GLOBAL`: All chat messages are enabled

- **`EClientFlags`**: Bit flags for client state management:
  - `CF_QUIT`: Client has sent an exit command
  - `CF_MISSING_SEQ`: Client is missing sequence data
  - `CF_RETRANSMIT_SEQ`: Client needs sequence data retransmitted
  - `CF_MISSING_CON`: Client is missing consistency data
  - `CF_RETRANSMIT_CON`: Client needs consistency data retransmitted
  - `CF_UPDATED`: Client has received an updated packet

### Classes

#### FDynamicBuffer
A dynamic buffer class for managing network data:
- **`SetData(const uint8_t* data, int len)`**: Sets the buffer data
- **`GetData(int* len = nullptr)`**: Retrieves the buffer data

### Structures

#### FClientNetState
Comprehensive structure for tracking client network state:

- **`FNetTic`**: Inner structure for storing tic data:
  - `Data`: Dynamic buffer for tic data
  - `Command`: User command for this tic

- **Latency Management**:
  - `CurrentLatency`: Current latency ID
  - `bNewLatency`: Flag for new latency measurement
  - `AverageLatency`: Calculated average latency
  - `SentTime`: Timestamps for packet sending
  - `RecvTime`: Timestamps for packet acknowledgment

- **State Tracking**:
  - `Flags`: Client state flags
  - `ResendID`: ID for retransmission tracking
  - `ResendSequenceFrom`: Starting sequence for retransmission
  - `SequenceAck`: Last acknowledged sequence
  - `CurrentSequence`: Last received sequence

- **Consistency Management**:
  - `ResendConsistencyFrom`: Starting consistency for retransmission
  - `ConsistencyAck`: Last acknowledged consistency
  - `LastVerifiedConsistency`: Last verified consistency
  - `CurrentNetConsistency`: Last received consistency
  - `NetConsistency`: Array of received consistencies
  - `LocalConsistency`: Array of local consistencies for verification

### Functions

#### Network Update Functions
- **`NetUpdate(int tics)`**: Creates and broadcasts ticcmds to other players
- **`D_QuitNetGame(void)`**: Broadcasts exit notification to other players
- **`TryRunTics(void)`**: Processes network tics
- **`Net_Initialize()`**: Initializes the networking system

#### Tic Management
- **`Net_NewClientTic()`**: Creates a new client tic
- **`Net_SetWaiting()`**: Sets the network to waiting state
- **`Net_ClearBuffers()`**: Clears network buffers
- **`Net_ResetCommands(bool midTic)`**: Resets command buffers

#### Data Serialization
- **`Net_WriteInt8(uint8_t)`**: Writes an 8-bit integer to the network
- **`Net_WriteInt16(int16_t)`**: Writes a 16-bit integer to the network
- **`Net_WriteInt32(int32_t)`**: Writes a 32-bit integer to the network
- **`Net_WriteInt64(int64_t)`**: Writes a 64-bit integer to the network
- **`Net_WriteFloat(float)`**: Writes a float to the network
- **`Net_WriteDouble(double)`**: Writes a double to the network
- **`Net_WriteString(const char *)`**: Writes a string to the network
- **`Net_WriteBytes(const uint8_t *, int len)`**: Writes a byte array to the network

#### Command Processing
- **`Net_DoCommand(int cmd, uint8_t **stream, int player)`**: Processes a network command
- **`Net_SkipCommand(int cmd, uint8_t **stream)`**: Skips a network command

### Global Variables
- **`LocalCmds[LOCALCMDTICS]`**: Array of local user commands
- **`ClientTic`**: Current client tic
- **`ClientStates[MAXPLAYERS]`**: Array of client network states

## Technical Details

### Packet Structure
The file includes a detailed comment describing the network packet structure:
1. Command flags byte
2. Last sequence acknowledgment (4 bytes)
3. Last consistency acknowledgment (4 bytes)
4. Quitter information (if applicable)
5. Player count and tic count
6. Base sequence and consistency information
7. Per-player data including:
   - Player number
   - Latency information
   - Consistency deltas
   - Command and event data for each tic

### Reliability Mechanisms
- Sequence numbering for packet ordering
- Consistency checking for game state verification
- Retransmission flags for handling packet loss
- Latency measurement and tracking

## Connections with Other Modules
- Interfaces with `d_protocol.h` for network protocol definitions
- Uses `i_net.h` for low-level network operations
- Connects to the game loop through `TryRunTics()`
- Provides network command infrastructure used by various game systems
- Supports the multiplayer chat system through the `EChatType` enumeration
