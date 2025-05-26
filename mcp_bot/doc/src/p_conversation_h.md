# p_conversation.h

## File Purpose
This header file defines the structures and functions for implementing Strife-style conversation dialogues in GZDoom. It provides the foundation for interactive conversations between players and non-player characters (NPCs), allowing for branching dialogue trees, item checks, and various actions to be triggered through conversation choices.

## Key Components

### Data Structures

- **`FStrifeDialogueItemCheck`**: Structure for checking if a player has specific items in their inventory.
  - `PClassActor *Item`: The item class to check for.
  - `int Amount`: The required amount of the item.

- **`FStrifeDialogueNode`**: Structure representing a conversation node (what an NPC says to the player).
  - Contains information about the speaker, dialogue text, backdrop image, and voice sound.
  - Stores item checks that determine which node to display based on player inventory.
  - Links to possible player responses (children).
  - Includes fields for customizing the conversation menu.

- **`FStrifeDialogueReply`**: Structure representing a player's response in a conversation.
  - Contains the reply text and various actions to take when selected.
  - Can give items to the player, take items from them, or execute special actions.
  - Can lead to another conversation node.
  - Includes item checks to determine if the reply should be available.

### Functions

- **`P_FreeStrifeConversations`**: Frees all conversation-related resources.
- **`P_StartConversation`**: Initiates a conversation between an NPC and a player.
- **`P_ResumeConversation`**: Resumes a conversation that was interrupted.
- **`P_ConversationCommand`**: Handles network commands related to conversations.
- **`GetStrifeType`**: Retrieves a PClassActor pointer from a Strife type number.

## Technical Details

### Conversation System

- The conversation system is based on nodes and replies, forming a dialogue tree.
- Each node represents what an NPC says, and each reply represents a player's response.
- Replies can lead to different nodes, creating branching conversations.
- Item checks can be used to show different dialogue based on the player's inventory.

### Item Checks

- Item checks are used in three ways:
  1. To determine which node to display (in `FStrifeDialogueNode::ItemCheck`).
  2. To determine if a reply is available (in `FStrifeDialogueReply::ItemCheck`).
  3. To take items from the player when a reply is selected.

### Network Support

- The conversation system supports networked multiplayer through the `P_ConversationCommand` function.
- This allows conversations to be synchronized across all players in a multiplayer game.

## Connections with Other Modules

- Interacts with the inventory system to check for and manipulate items.
- Uses the sound system for voice playback.
- Connects to the menu system for displaying conversation UI.
- Interfaces with the network code for multiplayer support.
- Works with the actor system for NPC interactions.

## Notable Features

- Support for voice acting through the `SpeakerVoice` field.
- Ability to give items to players or take items from them during conversations.
- Support for executing special actions when certain replies are selected.
- Branching dialogue trees based on player inventory and choices.
- Quest log integration through the `LogString` and `LogNumber` fields.
