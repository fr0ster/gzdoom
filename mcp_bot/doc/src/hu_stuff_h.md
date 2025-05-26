# hu_stuff.h

## File Purpose
This header file defines the interfaces for the Head-Up Display (HUD) functionality in GZDoom. It provides declarations for functions related to chat routines and deathmatch score display, which are essential components of the game's user interface during gameplay.

## Key Components

### Chat System

- **`CT_Init`**: Initializes the chat system.
- **`CT_Responder`**: Handles input events for the chat system, returning true if the event was consumed.
- **`CT_Drawer`**: Renders the chat interface on the screen.

### Scoreboard Display

- **`HU_DrawScores`**: Draws the deathmatch scoreboard, showing player rankings and statistics.

### Global Variables

- **`SB_ForceActive`**: A boolean flag that can be used to force the scoreboard to be displayed regardless of other conditions.

## Technical Details

### Chat System Implementation

The chat system provides a way for players to communicate with each other during multiplayer games. The implementation includes:
- Initialization of chat-related resources
- Processing of keyboard input for chat messages
- Rendering of chat messages on the screen

### Scoreboard Display

The scoreboard display shows player rankings in deathmatch games, including:
- Player names
- Frag counts
- Other relevant statistics
- Visual indicators for the local player

## Connections with Other Modules

- Interfaces with the event system to process player input for chat
- Connected to the rendering system for displaying chat messages and the scoreboard
- Linked to the multiplayer networking system for player data in the scoreboard
- Used by the game's main loop to display HUD elements during gameplay

## Notable Features

- Support for chat communication in multiplayer games
- Deathmatch scoreboard display with player statistics
- Ability to force the scoreboard to be displayed via the `SB_ForceActive` flag
