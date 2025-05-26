# i_net.cpp

## File Purpose
This source file implements the networking system for GZDoom, providing functionality for multiplayer gameplay through UDP sockets. It handles network initialization, client connections, packet transmission, and game session management for both peer-to-peer and packet server networking modes.

## Key Components

### Network Connection Types

- **`ENetConnectType`**: Enumeration for connection packet types
  - Pre-connection handshaking (`PRE_HEARTBEAT`, `PRE_CONNECT`, etc.)
  - Game setup messages (`PRE_USER_INFO`, `PRE_GAME_INFO`, etc.)
  - Game start signal (`PRE_GO`)
  - Error conditions (`PRE_FULL`, `PRE_WRONG_PASSWORD`, etc.)

### Connection Management

- **`FConnection`**: Structure for tracking client connections
  - Connection status tracking
  - Client address information
  - Game information acknowledgment
- **`EConnectionStatus`**: Enumeration for client connection states
  - `CSTAT_NONE`: Not connected
  - `CSTAT_CONNECTING`: Attempting to connect
  - `CSTAT_WAITING`: Waiting for game information
  - `CSTAT_READY`: Ready to start the game

### Socket Functions

- **`CreateUDPSocket`**: Creates a UDP socket for network communication
- **`BindToLocalPort`**: Binds a socket to a specific port
- **`BuildAddress`**: Constructs a socket address from a hostname or IP
- **`StartNetwork`**: Initializes the network system
- **`CloseNetwork`**: Shuts down the network system

### Packet Handling

- **`SendPacket`**: Sends a packet to a specific address
- **`GetPacket`**: Receives a packet and processes it
- **`GenerateGameID`**: Creates a unique game ID for session validation
- **`FindClient`**: Locates a client by their network address

### Game Session Management

- **`HostGame`**: Sets up a game as the host
- **`JoinGame`**: Connects to a hosted game
- **`Host_CheckForConnections`**: Processes incoming connections as host
- **`Guest_ContactHost`**: Maintains connection with the host as a guest
- **`I_InitNetwork`**: Main entry point for network initialization

### User Interface Integration

- **`I_NetLog`**: Logs network-related messages
- **`I_NetError`**: Displays network error messages
- **`I_NetMessage`**: Updates the network status message
- **`I_NetClientConnected`**: Notifies of a new client connection
- **`I_NetClientUpdated`**: Updates client status information
- **`I_NetClientDisconnected`**: Notifies of a client disconnection

## Technical Details

### Network Protocol

The implementation uses a custom protocol over UDP:
1. **Connection Establishment**:
   - Clients send `PRE_CONNECT` to the host
   - Host validates and responds with `PRE_CONNECT_ACK`
   - Clients and host exchange user information
   - Host sends game information to clients
   - Host sends `PRE_GO` when all clients are ready

2. **Packet Structure**:
   - 4-byte CRC32 checksum header
   - Command byte (with flags)
   - Payload data
   - Optional compression for larger packets

3. **Security Features**:
   - Password protection for game sessions
   - Game ID validation for all packets
   - Version checking between clients
   - Client banning capability

### Cross-Platform Support

The implementation includes compatibility code for different platforms:
- Windows-specific socket handling through Winsock
- POSIX socket API for non-Windows platforms
- Platform-specific error handling and socket options

### Network Modes

Two networking modes are implemented:
1. **Peer-to-Peer**: Used for smaller games (2 players)
   - All clients connect directly to each other
   - Suitable for LAN games or small internet games

2. **Packet Server**: Used for larger games or when clients are on different networks
   - One client acts as the server
   - Server relays packets between clients
   - Automatically selected based on network conditions

## Connections with Other Modules

- Integrates with the start window system for user interface feedback
- Connects to the game loop for sending and receiving network messages
- Links to the compression system for packet compression
- Interfaces with the command-line argument system for network configuration
- Uses the random number generator for game ID creation

## Notable Features

- Automatic selection of networking mode based on player count and network topology
- Support for compressed network packets to reduce bandwidth usage
- Password protection for private game sessions
- Version checking to ensure compatibility between clients
- Client kick and ban functionality
- Heartbeat system to maintain connections
- Graceful handling of client disconnections
- Cross-platform socket implementation
