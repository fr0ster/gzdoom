# p_pspr.cpp

## File Purpose
This implementation file provides the core functionality for sprite animation and weapon display in GZDoom. It implements the structures and functions declared in `p_pspr.h`, handling player weapon sprites (psprites), which are overlay graphics drawn directly on the view screen. These sprites are used for weapons, weapon flashes, and other first-person visual elements that are attached to the player's view.

## Key Components

### DPSprite Class Implementation

#### Constructor and Destructor
```cpp
DPSprite::DPSprite(player_t *owner, AActor *caller, int id)
void DPSprite::OnDestroy()
```

The constructor initializes a new player sprite with the specified owner, caller, and ID. It sets up default values for the sprite's properties, such as position, scale, and flags. The `OnDestroy` method handles cleanup when the sprite is destroyed, removing it from the player's sprite list.

#### State Management
```cpp
void DPSprite::SetState(FState *newstate, bool pending)
```

Sets the sprite to a new state, updating its appearance and behavior. If `pending` is true, the state change is deferred until the next tick. This method handles state transitions, including updating the sprite's frame, tics, and other properties based on the new state.

#### Rendering Style Calculation
```cpp
std::pair<FRenderStyle, float> DPSprite::GetRenderStyle(FRenderStyle ownerstyle, double owneralpha)
```

Calculates the render style and alpha for the sprite, taking into account the owner's render style and alpha, as well as the sprite's own flags and properties. This is used by the rendering system to determine how the sprite should be drawn.

#### Vertical Position Adjustment
```cpp
float DPSprite::GetYAdjust(bool fullscreen)
```

Calculates vertical position adjustment based on screen size and aspect ratio. This ensures that the weapon sprite is positioned correctly regardless of the player's screen resolution and aspect ratio.

#### Serialization
```cpp
void DPSprite::Serialize(FSerializer &arc)
```

Handles serialization and deserialization of the sprite's state, allowing it to be saved and loaded as part of the game's save system.

### Global Functions

#### Sprite Tick Management
```cpp
void P_NewPspriteTick()
```

Updates all player sprites for a new game tick. This function is called once per game tick and handles updating the state of all player sprites, including advancing animations, processing pending state changes, and updating positions.

#### Weapon Swing Calculation
```cpp
void P_CalcSwing(player_t *player)
```

Calculates weapon swinging motion based on player movement and turning. This creates a more immersive visual effect by making the weapon sway slightly as the player moves and turns.

#### Sprite State Management
```cpp
void P_SetPsprite(player_t *player, PSPLayers id, FState *state, bool pending)
```

Sets a player sprite to a new state. This is the main function used by weapon code to change the state of weapon sprites, such as when firing, reloading, or switching weapons.

#### Weapon Management
```cpp
void P_BringUpWeapon(player_t *player)
```

Initiates the weapon raising animation when a player switches to a new weapon. This function handles the transition from the lowered state to the ready state.

```cpp
void P_FireWeapon(player_t *player)
```

Fires the player's current weapon. This function handles the weapon firing sequence, including changing the weapon sprite's state, playing sound effects, and creating projectiles or hitscan attacks.

#### Weapon Bobbing
```cpp
void P_BobWeapon(player_t *player, float *x, float *y, double ticfrac)
```

Calculates weapon bobbing motion in 2D based on player movement. This creates a more immersive visual effect by making the weapon bob up and down slightly as the player moves.

```cpp
void P_BobWeapon3D(player_t *player, FVector3 *translation, FVector3 *rotation, double ticfrac)
```

Calculates weapon bobbing motion in 3D, including both translation and rotation. This provides a more sophisticated bobbing effect for modern rendering modes.

#### Aiming Functions
```cpp
DAngle P_BulletSlope(AActor *mo, FTranslatedLineTarget *pLineTarget, int aimflags)
```

Calculates the slope for bullet projectiles, taking into account auto-aim and other factors. This is used by hitscan weapons to determine the trajectory of bullets.

```cpp
AActor *P_AimTarget(AActor *mo)
```

Finds a target for auto-aim, searching for actors in the player's field of view that can be targeted. This is used by the auto-aim system to assist players in targeting enemies.

#### Weapon Ready State Functions
```cpp
void DoReadyWeaponToBob(AActor *self)
void DoReadyWeaponToFire(AActor *self, bool primary, bool secondary)
void DoReadyWeaponToSwitch(AActor *self, bool switchable)
```

These functions prepare a weapon for different actions:
- `DoReadyWeaponToBob`: Prepares the weapon to bob with player movement
- `DoReadyWeaponToFire`: Prepares the weapon to be fired
- `DoReadyWeaponToSwitch`: Prepares the weapon to be switched

#### Weapon Action Function
```cpp
void A_ReFire(AActor *self, FState *state)
```

A weapon action function that handles automatic refiring of weapons. This is used by weapons that can be fired continuously while the fire button is held down.

## Implementation Details

### Player Sprite Management
The implementation manages player sprites through a linked list attached to each player. The `DPSprite` objects in this list represent different layers of the player's view, such as the main weapon sprite, muzzle flash, and targeting reticle. The `P_NewPspriteTick` function updates all sprites in these lists each game tick.

### Sprite Animation
Sprite animation is implemented through the state system, with each sprite having a current state that defines its appearance and behavior. The `SetState` method changes a sprite's state, and the state system handles advancing to the next state in a sequence when the current state's duration (tics) expires.

### Sprite Positioning
Sprites are positioned on the screen using a combination of base position, weapon offset, bobbing motion, and alignment. The implementation includes sophisticated calculations for these factors, taking into account:
- Screen size and aspect ratio
- Player movement and turning
- Weapon properties
- Custom positioning set by weapon code

### Weapon Bobbing
Weapon bobbing is implemented through the `P_BobWeapon` and `P_BobWeapon3D` functions, which calculate bobbing motion based on player movement. The implementation includes:
- Vertical bobbing based on player speed
- Horizontal swaying based on player turning
- Adjustments based on player state (running, crouching, etc.)
- Customization through cvars and weapon properties

### Weapon Firing
Weapon firing is implemented through the `P_FireWeapon` function, which handles the firing sequence for the player's current weapon. The implementation includes:
- Changing the weapon sprite's state to a firing animation
- Playing sound effects
- Creating projectiles or hitscan attacks
- Handling ammo consumption
- Applying recoil and screen shake effects

### Aiming System
The aiming system is implemented through the `P_BulletSlope` and `P_AimTarget` functions, which handle auto-aim and target acquisition. The implementation includes:
- Searching for targets in the player's field of view
- Prioritizing targets based on distance and angle
- Adjusting aim based on player skill and game settings
- Handling special cases like locked-on targets

### Weapon Ready State
The weapon ready state is a special state that represents the weapon being ready to fire. The implementation includes several functions that prepare the weapon for different actions from this state:
- `DoReadyWeaponToBob`: Enables bobbing motion
- `DoReadyWeaponToFire`: Enables firing
- `DoReadyWeaponToSwitch`: Enables weapon switching

### Weapon Refiring
Automatic refiring of weapons is implemented through the `A_ReFire` function, which checks if the fire button is still held down and, if so, transitions the weapon back to its firing state. This creates a continuous firing effect for automatic weapons.

## Connections with Other Modules
- Interfaces with the player system for weapon management and input handling
- Connects to the state system for sprite animation and weapon behavior
- Interfaces with the rendering system for displaying sprites
- Used by the weapon code for implementing weapon behavior
- Connects to the input system for weapon control
- Interfaces with the sound system for weapon sounds
- Connects to the projectile system for creating projectiles
- Interfaces with the hitscan system for instant-hit weapons
