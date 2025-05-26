# i_net.h

## File Purpose
This header file defines the networking interface for GZDoom, providing constants, enumerations, and function declarations for the game's multiplayer networking system. It establishes the foundation for both peer-to-peer and packet server networking modes.

## Key Components

### Network Constants

- **`MAXPLAYERS`**: Maximum number of players allowed in a multiplayer game (64)
- **`BACKUPTICS`**: Number of game tics to remember for network synchronization (175)
- **`MAXTICDUP`**: Maximum number of duplicate tics allowed (3)
- **`MAXSENDTICS`**: Maximum number of tics to send at once (35)
- **`MAX_MSGLEN`**: Maximum size of a network message (14000 bytes)

### Network Command Enumerations

- **`ENetCommand`**: Commands for network operations
  - `CMD_NONE`: No command
  - `CMD_SEND`: Send a packet
  - `CMD_GET`: Receive a packet

- **`ENetFlags`**: Flags for network packets
  - `NCMD_EXIT`: Client has left the game
  - `NCMD_RETRANSMIT`: Packet retransmission
  - `NCMD_SETUP`: Initial connection setup
  - `NCMD_LEVELREADY`: Level loading synchronization
  - `NCMD_QUITTERS`: Information about players quitting
  - `NCMD_COMPRESSED`: Packet is compressed
  - `NCMD_LATENCY`: Latency measurement packets

- **`ENetMode`**: Network operation modes
  - `NET_PeerToPeer`: Direct connections between all players
  - `NET_PacketServer`: Server-client model with a host

### Client Management

- **`FClientStack`**: Class for managing connected clients
  - `InGame`: Check if a client is in the game
  - `operator+=`: Add a client to the stack
  - `operator-=`: Remove a client from the stack

### Global Variables

- **`netgame`**: Flag indicating if a network game is active
- **`multiplayer`**: Flag indicating if multiple players are in the game
- **`consoleplayer`**: Index of the local player
- **`Net_Arbitrator`**: Index of the host/arbitrator player
- **`NetworkClients`**: Stack of connected clients
- **`NetMode`**: Current network mode
- **`NetBuffer`**: Buffer for network messages
- **`NetBufferLength`**: Length of data in the network buffer
- **`TicDup`**: Number of duplicate tics
- **`RemoteClient`**: Index of the remote client being communicated with
- **`MaxClients`**: Maximum number of clients allowed in the current game

### Network Functions

- **`I_InitNetwork`**: Initialize the networking system
- **`I_ClearClient`**: Clear a client's connection data
- **`I_NetCmd`**: Execute a network command (send/receive)
- **`I_NetDone`**: Finalize network operations
- **`HandleIncomingConnection`**: Process an incoming connection
- **`CloseNetwork`**: Shut down the networking system

## Technical Details

### Client Management

The `FClientStack` class provides a sorted collection of client indices, with methods to:
- Check if a client is in the game
- Add a client to the game
- Remove a client from the game

### Network Buffer

The system uses a fixed-size buffer (`NetBuffer`) for network communications:
- Maximum message length is defined by `MAX_MSGLEN`
- Current message length is tracked in `NetBufferLength`
- Messages are sent and received through this buffer

### Network Modes

The system supports two network modes:
- **Peer-to-Peer**: All clients connect directly to each other
- **Packet Server**: One client acts as a server, relaying packets between clients

## Connections with Other Modules

- Integrates with the game loop for sending and receiving network messages
- Connects to the player system for managing player connections
- Links to the game state system for synchronizing game state across the network
- Interfaces with the socket system for low-level network communication

## Notable Features

- Support for both peer-to-peer and packet server networking modes
- Efficient client management through the `FClientStack` class
- Comprehensive packet flags for different network operations
- Support for packet compression
- Latency measurement capabilities
- Level loading synchronization
- Configurable network parameters (tic duplication, port, etc.)
