# d_net.cpp

## File Purpose
This file implements the core networking functionality for GZDoom's multiplayer system. It handles packet transmission, network command processing, game state synchronization, and player communication. The file provides both peer-to-peer and packet server networking modes, with comprehensive support for reliable packet delivery, latency management, and game state consistency checking.

## Key Components

### Network State Management

- **Client State Tracking**: Maintains the network state for each client, including sequence numbers, consistency values, and latency information
- **Packet Buffering**: Handles local and remote packet buffers for efficient network communication
- **Lobby Management**: Controls game lobby creation and synchronization between players
- **Level Start Coordination**: Ensures all players start levels simultaneously with proper synchronization

### Network Communication

- **Packet Handling**:
  - `HSendPacket()`: Sends a packet to a specific client
  - `HGetPacket()`: Receives a packet from the network
  - `GetPackets()`: Processes all incoming packets
  - `SendHeartbeat()`: Sends regular heartbeat packets for latency measurement

- **Command Processing**:
  - `Net_DoCommand()`: Processes network commands received from clients
  - `Net_SkipCommand()`: Skips over network commands without executing them
  - `NetUpdate()`: Main function for updating network state and sending packets

### Game Synchronization

- **Tic Management**:
  - `TryRunTics()`: Processes game tics based on available network data
  - `Net_UpdateStatus()`: Checks if the game can advance based on network state
  - `MakeConsistencies()`: Creates consistency values for game state verification
  - `CheckConsistencies()`: Verifies game state consistency between clients

- **Latency Handling**:
  - Adaptive timing system to handle varying network conditions
  - Latency measurement and tracking for each client
  - Command buffering to smooth gameplay despite network jitter

### Network Event System

- **`NetEventData` Class**: Manages network events that occur between game tics
- **Event Serialization**: Functions for writing various data types to the network stream
- **Event Processing**: System for handling events in the correct order across the network

### Client Management

- **`ClientConnecting()`**: Handles new client connections
- **`DisconnectClient()`**: Manages client disconnections
- **`ClientQuit()`**: Processes client quit requests
- **`SetArbitrator()`**: Sets the host/arbitrator for the game

## Technical Details

### Networking Modes

1. **Peer-to-Peer Mode**:
   - All clients communicate directly with each other
   - Each client sends its commands to all other clients
   - No central authority for game state

2. **Packet Server Mode**:
   - One client acts as the arbitrator/host
   - All clients send commands to the host
   - Host redistributes commands to all clients
   - Provides better synchronization for high-latency connections

### Reliability Mechanisms

- **Sequence Numbering**: Tracks the order of packets and commands
- **Consistency Checking**: Verifies game state synchronization between clients
- **Retransmission**: Automatically requests missing or corrupted packets
- **Adaptive Timing**: Adjusts game speed based on network conditions

### Optimization Techniques

- **Command Batching**: Groups commands to reduce packet overhead
- **Tic Duplication**: Allows multiple game tics per network update
- **Latency Balancing**: Adjusts timing to accommodate clients with varying latencies
- **Prediction**: Predicts game state to smooth gameplay despite network delays

### Console Commands

- **Network Information**:
  - `pings`: Displays latency information for all clients
  - `listplayers`: Lists all players in the game
  - `net_stat`: Shows detailed network statistics

- **Player Management**:
  - `kick`: Removes a player from the game
  - `mute`/`unmute`: Controls message reception from specific players
  - `net_addcontroller`/`net_removecontroller`: Manages players with settings control privileges

## Special Features

### Tic Stability System

- `r_ticstability`: Controls consistent timing for interpolation between frames
- `TicStabilityBegin()`, `TicStabilityEnd()`, `TicStabilityWait()`: Functions that manage stable frame timing

### Network Commands

The file implements a comprehensive set of network commands (DEM_*) for various game actions:
- Chat messages and player communication
- Cheat commands and administrative functions
- Game state modifications and level changes
- Player actions and inventory management
- Script execution and special effects

### Muting System

- Allows players to mute messages from specific other players
- Provides commands for managing muted players

### Controller System

- Allows the host to designate certain players as "settings controllers"
- These players have permission to change game settings

## Connections with Other Modules

- Interfaces with `d_main.cpp` for game loop integration
- Uses `i_net.h` for low-level network operations
- Connects to the player system for command processing
- Interacts with the console system for command execution
- Provides network event data to various game subsystems
