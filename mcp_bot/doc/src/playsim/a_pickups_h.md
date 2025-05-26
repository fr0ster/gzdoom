# a_pickups.h

## File Purpose
This header file defines the interface for the pickup and inventory system in GZDoom. It provides declarations for functions related to item pickups and establishes structures needed for weapon rendering. The file serves as a bridge between the C++ engine code and the script-side inventory implementation.

## Key Components

### Constants

#### Weapon Slots
- `NUM_WEAPON_SLOTS`: Defines the number of available weapon slots (10)

### Structures

#### visstyle_t
A structure that encapsulates the fields of `vissprite_t` that can be altered by the `AlterWeaponSprite` function:

```cpp
struct visstyle_t
{
    bool        Invert;         // Whether to invert the sprite
    float       Alpha;          // Transparency level
    ERenderStyle RenderStyle;   // How to render the sprite
};
```

This structure is used for modifying weapon appearance during rendering, allowing for effects like transparency, inversion, and different render styles.

### Function Declarations

#### CallTryPickup
```cpp
bool CallTryPickup(AActor *item, AActor *toucher, AActor **toucher_return = nullptr);
```

Attempts to have an actor pick up an item:
- `item`: The item to be picked up
- `toucher`: The actor attempting to pick up the item
- `toucher_return`: Optional pointer to receive the actor that actually received the item
- Returns: Whether the pickup was successful

This function is implemented in a_pickups.cpp and serves as the main entry point for the pickup system.

#### DepleteOrDestroy
```cpp
void DepleteOrDestroy(AActor *item);
```

Handles the depletion or destruction of inventory items:
- `item`: The inventory item to deplete or destroy

This function is implemented in a_pickups.cpp but is virtual on the script side, allowing for custom behavior in ZScript.

### Forward Declarations
- `class player_t`: The player class
- `class FConfigFile`: Configuration file class

## Implementation Details

The header is intentionally minimal, providing only the necessary interface for the pickup system. Most of the actual inventory functionality is implemented in ZScript, with these C++ functions serving as bridge points between the engine and the script system.

The comment "A pickup is anything the player can pickup (i.e. weapons, ammo, powerups, etc)" provides a clear definition of what constitutes a pickup in the game's context.

## Connections with Other Modules
- Includes "actor.h" for the AActor class
- Includes "info.h" for class information
- Includes "s_sound.h" for sound functionality
- Connects to the player system through the player_t forward declaration
- Interfaces with the configuration system through the FConfigFile forward declaration
- Links to the rendering system through the visstyle_t structure
