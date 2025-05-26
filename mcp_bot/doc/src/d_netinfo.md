# d_netinfo.cpp

## File Purpose
This file implements the management and transport of user and server configuration variables (CVars) across a network in GZDoom. It handles player information synchronization, team management, and server settings distribution. The file provides mechanisms for encoding, transmitting, and decoding user preferences and game settings between clients and servers in a multiplayer environment.

## Key Components

### User Information Management

- **`userinfo_t` Class Implementation**: Provides methods for managing player-specific settings
  - `Reset()`: Initializes a player's userinfo with default values
  - `TeamChanged()`: Handles team assignment changes
  - `SkinChanged()`: Processes skin selection changes
  - `GenderChanged()`: Manages gender setting changes
  - `PlayerClassChanged()`: Handles player class selection changes
  - `ColorChanged()`: Processes player color modifications

- **User Information Serialization**:
  - `D_EscapeUserInfo()`: Escapes special characters in user info strings
  - `D_UnescapeUserInfo()`: Unescapes special characters in user info strings
  - `D_GetUserInfoStrings()`: Creates a formatted string of all user settings
  - `D_ReadUserInfoStrings()`: Parses user info strings from network data
  - `WriteUserInfo()`: Serializes user info for saving to files
  - `ReadUserInfo()`: Deserializes user info from saved files

### Team Management

- **Team Assignment**:
  - `D_PickRandomTeam()`: Selects an appropriate team for a player
  - `UpdateTeam()`: Updates a player's team assignment and notifies other players
  - `D_GetFragCount()`: Calculates frag counts for individual players or teams

### Server Information Management

- **Server Variable Handling**:
  - `SetServerVar()`: Updates server variables from network data
  - `D_SendServerInfoChange()`: Sends server variable changes to clients
  - `D_SendServerFlagChange()`: Sends server flag changes to clients
  - `D_DoServerInfoChange()`: Processes server variable changes from network data

### Player Appearance

- **Visual Customization**:
  - `D_GetPlayerColor()`: Calculates a player's color based on settings and team
  - Color conversion utilities for HSV and RGB color spaces
  - Team color enforcement in team-based game modes

### User Variables

- **Player Configuration CVars**:
  - `name`: Player's display name
  - `team`: Player's team assignment
  - `skin`: Player's skin selection
  - `gender`: Player's gender selection
  - `color`: Player's color preference
  - `colorset`: Player's color set selection
  - `playerclass`: Player's class selection
  - `autoaim`: Player's auto-aim setting
  - Movement and view bob settings
  - Various gameplay preference settings

## Technical Details

### User Information Structure

- Uses a map-based structure to store player settings as console variables
- Provides type-safe access to settings through specialized getter methods
- Implements custom serialization for network transmission
- Supports both compact and verbose formats for network efficiency

### Network Communication

- Implements escape sequences for special characters in network strings
- Provides bidirectional conversion between internal values and network representations
- Handles synchronization of settings changes across all connected clients

### Team Balancing

- Implements team selection logic to maintain balanced teams
- Tracks team presence and membership for proper distribution
- Provides random team assignment with tie-breaking for equal-sized teams

### Console Commands

- **`playerinfo`**: Displays detailed information about players in the game

## Connections with Other Modules

- Interfaces with the console variable system for configuration management
- Provides data to the networking system for player information synchronization
- Connects to the rendering system for player appearance customization
- Supports the team system for team-based game modes
- Interacts with the player class system for class selection and validation
