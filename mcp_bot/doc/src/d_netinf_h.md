# d_netinf.h

## File Purpose
This header file defines the interface for handling player information in GZDoom's networking system. It provides functions and data structures for managing user information that needs to be synchronized across the network, such as player gender, player class, colors, and other customizable attributes. The file serves as a bridge between the networking code and the player configuration system.

## Key Components

### Gender System

- **`GENDER_MALE`, `GENDER_FEMALE`, `GENDER_NEUTER`, `GENDER_OBJECT`**: Enumeration constants defining the possible gender values for players
- **`D_GenderToInt(const char *gender)`**: Converts a gender string to its corresponding integer value
- **`GenderNames[GENDER_MAX]`**: Array of string names for each gender type

### Player Class Management

- **`D_PlayerClassToInt(const char *classname)`**: Converts a player class name to its corresponding integer value

### User Information Management

- **`D_SetupUserInfo(void)`**: Initializes the user information system
- **`D_UserInfoChanged(FBaseCVar *info)`**: Callback function triggered when user information changes
- **`D_GetUserInfoStrings(int pnum, bool compact)`**: Retrieves user information as a formatted string
- **`D_ReadUserInfoStrings(int player, uint8_t **stream, bool update)`**: Reads user information from a network stream

### Server Information Management

- **`D_SendServerInfoChange(FBaseCVar *cvar, UCVarValue value, ECVarType type)`**: Sends server information changes to clients
- **`D_SendServerFlagChange(FBaseCVar *cvar, int bitnum, bool set, bool silent)`**: Sends server flag changes to clients
- **`D_DoServerInfoChange(uint8_t **stream, bool singlebit)`**: Processes server information changes from a network stream

### Player Appearance

- **`D_GetPlayerColor(int player, float *h, float *s, float *v, FPlayerColorSet **colorset)`**: Retrieves a player's color settings
- **`D_PickRandomTeam(int player)`**: Assigns a random team to a player
- **`D_PickRandomTeam()`**: Overloaded version that returns a random team index
- **`D_GetFragCount(player_t *player)`**: Retrieves a player's frag count

## Technical Details

- Uses the console variable system (`FBaseCVar`) to manage user and server settings
- Provides conversion functions between string representations and internal numeric values
- Implements network serialization for user information
- Supports both compact and verbose formats for user information strings

## Connections with Other Modules

- Interfaces with the console variable system for configuration management
- Provides data to the networking system for synchronization
- Connects to the player system for appearance and team management
- Used by the HUD and status bar for displaying player information
- Supports the chat system with player gender information for proper pronoun substitution
