# p_conversation.cpp

## File Purpose
This source file implements the Strife-style conversation system in GZDoom, providing interactive dialogues between players and non-player characters (NPCs). It handles the logic for displaying conversation nodes, processing player replies, checking inventory requirements, giving or taking items, and executing special actions based on dialogue choices.

## Key Components

### Conversation Management Functions

- **`P_StartConversation`**: Initiates a conversation between an NPC and a player.
  - Sets up the conversation state, including facing directions.
  - Processes item checks to determine the appropriate starting node.
  - Creates and displays the conversation menu for the player.
  - Plays voice audio if available.

- **`P_ResumeConversation`**: Resumes conversations that were interrupted by slideshows.

- **`P_FreeStrifeConversations`**: Cleans up conversation resources.

- **`P_ConversationCommand`**: Handles network commands related to conversations.
  - Processes reply selections from players.
  - Ensures conversation state is synchronized in multiplayer games.

### Helper Functions

- **`HandleReply`**: Processes a player's reply selection.
  - Checks if the player has required items.
  - Gives items or executes special actions if conditions are met.
  - Takes items from the player if specified.
  - Updates the quest log if needed.
  - Handles transitions to new conversation nodes.

- **`CheckStrifeItem`**: Checks if a player has a specific item in their inventory.

- **`TakeStrifeItem`**: Takes items from a player, with special handling for quest items, keys, and the sigil.

- **`ShouldSkipReply`**: Determines if a reply should be skipped based on item requirements.

- **`ClearConversationStuff`**: Clears conversation-related fields on a player.

- **`TerminalResponse`**: Displays a response message on the screen.

### Level Integration

- **`FLevelLocals::SetConversation`**: Associates a conversation node with a conversation ID or actor class.

- **`FLevelLocals::GetConversation`**: Retrieves a conversation node index by ID or class name.

- **`FLevelLocals::FindNode`**: Finds the index of a conversation node in the StrifeDialogues array.

## Technical Details

### Conversation Flow

1. A conversation begins when a player interacts with an NPC that has a conversation defined.
2. The system checks the player's inventory to determine which node to display.
3. The NPC's dialogue and possible player responses are shown in a menu.
4. When the player selects a response:
   - The system checks if the player has required items.
   - If requirements are met, any specified actions are executed.
   - Required items may be taken from the player.
   - The conversation may continue with a new node or end.

### Item Handling

- The system carefully handles special items like quest items, keys, and the sigil, which are never taken from the player.
- Items can be given to the player as rewards for certain dialogue choices.
- The system supports checking for multiple items with specific quantities.

### Network Support

- Conversations are synchronized across the network using the `DEM_CONVREPLY`, `DEM_CONVNULL`, and `DEM_CONVCLOSE` network commands.
- This ensures all players see consistent conversation state in multiplayer games.

### UI Integration

- Conversations use a menu system for display, with support for custom menu classes.
- The system supports displaying terminal responses as HUD messages.
- Music volume is adjusted during conversations with voice acting.

## Connections with Other Modules

- Interacts with the inventory system for item checks and manipulation.
- Uses the sound system for voice playback and volume control.
- Connects to the menu system for displaying conversation UI.
- Interfaces with the network code for multiplayer synchronization.
- Works with the actor system for NPC animations and interactions.
- Integrates with the quest log system for tracking player progress.

## Notable Features

- Support for branching dialogues based on player inventory and choices.
- Integration with the quest log system.
- Support for voice acting with automatic music volume adjustment.
- Special handling for quest items and other important inventory.
- Support for executing special actions through dialogue choices.
- NPC animations that respond to player choices.
- Support for slideshows triggered by conversations.
