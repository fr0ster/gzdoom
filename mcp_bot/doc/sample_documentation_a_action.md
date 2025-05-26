# a_action.cpp

## File Purpose
This file implements various action functions for actors in GZDoom. It primarily focuses on handling actor state changes related to blocking, corpse management, and item dropping. These functions are used by the game engine to control actor behavior when they die or need to change their collision properties.

## Key Components

### A_Unblock Function
A function that removes an actor's solid flag, making it non-blocking. It also handles:
- Restoring visibility for stealth monsters
- Dropping items based on conversation metadata
- Dropping items based on actor's DropItems metadata

### Corpse Queue Management Functions
Functions that manage the corpse queue system used by Hexen and other games:

#### A_QueueCorpse
- Adds the calling actor to the level's corpse queue
- Enforces the maximum corpse queue size by removing oldest corpses
- Uses the `sv_corpsequeuesize` CVAR to determine maximum queue size

#### A_DeQueueCorpse
- Removes an actor from the corpse queue
- Used when an actor is resurrected or otherwise needs to be removed from the queue

## Implementation Details

### Item Dropping Logic
The item dropping system supports two methods:
1. Conversation-based drops: Items specified in the actor's Conversation property
2. DropItems metadata: A linked list of items with probability and amount information

The function `P_DropItem` is called to actually spawn the dropped items in the game world.

### Corpse Queue Implementation
- Uses a dynamic array (`CorpseQueue`) stored in the `FLevelLocals` object
- Implements a FIFO (First In, First Out) queue for corpse management
- Provides garbage collection support through `GC::WriteBarrier`
- Exposed to ZScript through `DEFINE_ACTION_FUNCTION` macros

### Stealth Monster Handling
When unblocking a stealth monster (one with the MF_STEALTH flag), the function:
- Resets its Alpha value to 1.0 (fully visible)
- Resets its visibility direction (visdir) to 0

## Connections with Other Modules
- Interacts with the actor system through `actor.h`
- Uses player data structures from `d_player.h`
- Connects to the conversation system through `p_conversation.h`
- Uses line specials from `p_lnspec.h`
- Interacts with the play simulation through `p_local.h`
- Uses terrain effects from `p_terrain.h`
- Connects to enemy AI through `p_enemy.h`
- Interfaces with the serialization system through `serializer.h`
- Integrates with the virtual machine through `vm.h`
- Uses actor inline functions from `actorinlines.h`
