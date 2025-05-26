# a_pickups.cpp

## File Purpose
This source file implements core functionality for the inventory system in GZDoom. It provides essential functions for handling item pickups, displaying pickup messages, and managing inventory items. Despite its name suggesting a focus on pickups specifically, it contains fundamental inventory-related functions that are used throughout the game's item interaction system.

## Key Components

### PrintPickupMessage Function
```cpp
void PrintPickupMessage(bool localview, const FString &str)
```

Displays a message when an item is picked up:
- `localview`: Whether the message is for the local player
- `str`: The message to display

Features:
- Merges identical messages that occur on the same game tick (unless disabled in gameinfo)
- Translates messages that begin with '$' using the string table
- Flashes the crosshair when a message is displayed
- Uses static storage to track the last message and when it was displayed

### DepleteOrDestroy Function
```cpp
void DepleteOrDestroy(AActor *item)
```

Handles the depletion or destruction of inventory items:
- `item`: The inventory item to deplete or destroy

This function delegates to the virtual `DepleteOrDestroy` method of the inventory item, allowing different item types to implement their own behavior. Generally:
- If the item is depleted (used up), its amount is set to 0
- Otherwise, the item is destroyed completely

### CallTryPickup Function
```cpp
bool CallTryPickup(AActor *item, AActor *toucher, AActor **toucher_return)
```

Attempts to have an actor pick up an item:
- `item`: The item to be picked up
- `toucher`: The actor attempting to pick up the item
- `toucher_return`: Optional pointer to receive the actor that actually received the item
- Returns: Whether the pickup was successful

This function delegates to the virtual `CallTryPickup` method of the inventory item, which handles the actual pickup logic. It uses the virtual machine system to call the appropriate method and handle the return values.

## Implementation Details

### Message Merging
The pickup message system uses static variables to track:
- `StaticLastMessageTic`: The game tick when the last message was displayed
- `StaticLastMessage`: The content of the last message

This allows the system to avoid displaying duplicate messages in rapid succession, reducing screen clutter.

### Virtual Function Delegation
Both `DepleteOrDestroy` and `CallTryPickup` use the virtual machine system to delegate to the appropriate methods on the inventory items. This design allows:

1. Different item types to implement custom behavior
2. ZScript extensions to override the default behavior
3. Consistent interface for all inventory operations

### Function Caching
`CallTryPickup` caches the VMFunction pointer for better performance:
```cpp
static VMFunction *func = nullptr;
if (func == nullptr) PClass::FindFunction(&func, NAME_Inventory, NAME_CallTryPickup);
```

This avoids repeated lookups of the same function.

## Connections with Other Modules
- Integrates with the string system through "gstrings.h"
- Connects to the status bar system through "sbar.h"
- Uses game state information from "doomstat.h"
- Interfaces with the player system through "d_player.h"
- Uses the virtual machine system through "vm.h"
- Connects to level data through "g_levellocals.h"
- Uses game information through "gi.h"
- Interacts with the CVAR system through the `sv_unlimited_pickup` external CVAR
