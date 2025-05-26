# ct_chat.cpp

## File Purpose
This implementation file provides the functionality for the in-game chat system in GZDoom. It handles the input, display, and network transmission of chat messages between players in multiplayer games. The chat system supports both global chat (visible to all players) and team chat (visible only to players on the same team), as well as chat macros for quick communication.

## Key Components

### Constants and Limits

```cpp
enum { QUEUESIZE = 128 };
constexpr int MessageLimit = 2;
constexpr uint64_t MessageThrottleTime = 1000u;
constexpr uint64_t SpamCoolDown = 3000u;
```

Constants that define the behavior of the chat system:
- `QUEUESIZE`: Maximum size of the chat message buffer
- `MessageLimit`: Maximum number of messages that can be sent in a brief period
- `MessageThrottleTime`: Time in milliseconds that spam messages are tracked
- `SpamCoolDown`: Time in milliseconds for the spam cooldown period

### Global Variables

```cpp
static TArray<uint8_t> ChatQueue;
static uint64_t ChatThrottle = 0u;
static int ChatSpamCount = 0;
static uint64_t ChatCoolDown = 0u;
```

Variables that store the state of the chat system:
- `ChatQueue`: Buffer that stores the current chat message being typed
- `ChatThrottle`: Timestamp for tracking message throttling
- `ChatSpamCount`: Counter for tracking spam messages
- `ChatCoolDown`: Timestamp for the spam cooldown period

### Chat Macros

```cpp
CVAR (String, chatmacro1, "I'm ready to kick butt!", CVAR_ARCHIVE)
CVAR (String, chatmacro2, "I'm OK.", CVAR_ARCHIVE)
// ... more chat macros ...
```

Console variables that store predefined chat messages that can be quickly sent using number keys. These macros are customizable and are saved in the user's configuration.

### Public Functions

```cpp
void CT_Init();
void CT_Drawer();
bool CT_Responder(event_t *ev);
void CT_PasteChat(const char *clip);
```

Public functions that provide the interface to the chat system:
- `CT_Init`: Initializes the chat system
- `CT_Drawer`: Renders the chat input interface
- `CT_Responder`: Handles input events for the chat system
- `CT_PasteChat`: Pastes text from the clipboard into the chat input

### Private Functions

```cpp
static void CT_ClearChatMessage();
static void CT_AddChar(int c);
static void CT_BackSpace();
static void ShoveChatStr(const char *str, uint8_t who);
static bool DoSubstitution(FString &out, const char *in);
```

Private helper functions for the chat system:
- `CT_ClearChatMessage`: Clears the current chat message
- `CT_AddChar`: Adds a character to the current chat message
- `CT_BackSpace`: Removes the last character from the current chat message
- `ShoveChatStr`: Sends a chat message across the network
- `DoSubstitution`: Performs variable substitution in chat messages

### Console Commands

```cpp
CCMD (messagemode)
CCMD (say)
CCMD (messagemode2)
CCMD (say_team)
```

Console commands that provide different ways to initiate chat:
- `messagemode`: Activates global chat input mode
- `say`: Sends a global chat message directly from the console
- `messagemode2`: Activates team chat input mode
- `say_team`: Sends a team chat message directly from the console

## Implementation Details

### Chat Input Handling
The chat system captures keyboard input when in chat mode (`chatmodeon` is non-zero). It handles special keys like Enter (to send the message), Escape (to cancel), Backspace (to delete characters), and Ctrl+C/Ctrl+V for copy/paste operations. Regular character input is added to the chat message buffer.

### Chat Message Display
The `CT_Drawer` function renders the chat input interface on the screen. It displays a prompt ("Say:" for global chat or "Say to team:" for team chat) followed by the current chat message being typed. The text is positioned at the bottom of the screen, either above the status bar or at the bottom of the viewport.

### Chat Message Transmission
When a chat message is completed (by pressing Enter), the `ShoveChatStr` function sends it across the network using the `DEM_SAY` network command. The message includes a flag indicating whether it's a global or team message, and whether it's a "/me" action message.

### Spam Protection
The chat system includes spam protection to prevent players from flooding the chat with messages. It limits the number of messages that can be sent in a brief period and enforces a cooldown period for players who exceed this limit. The server can also enable a "slow mode" that enforces a minimum delay between messages.

### Chat Substitution
The chat system supports variable substitution in messages using the `$` symbol followed by a variable name. For example, `$health` is replaced with the player's current health, and `$weapon` is replaced with the name of the player's current weapon. This allows players to quickly share information about their status.

### Chat Macros
The chat system supports ten customizable chat macros (0-9) that can be quickly sent by pressing the corresponding number key while in chat mode. These macros are stored as console variables and can be customized by the player.

## Connections with Other Modules
- Interfaces with the input system for handling keyboard events
- Connects to the network system for sending chat messages
- Interfaces with the rendering system for displaying the chat input
- Used by the console system for processing chat commands
- Connects to the player system for accessing player information for substitution
- Interfaces with the clipboard system for copy/paste operations
