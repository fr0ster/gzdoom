# p_pspr.h

## File Purpose
This header file defines the structures and functions for sprite animation and weapon display in GZDoom. It provides the foundation for player weapon sprites (psprites), which are overlay graphics drawn directly on the view screen. These sprites are used for weapons, weapon flashes, and other first-person visual elements that are attached to the player's view.

## Key Components

### Constants

```cpp
#define WEAPONBOTTOM            128.
#define WEAPONTOP               32.
#define WEAPON_FUDGE_Y          0.375
```

Constants that define the vertical positioning limits for weapon sprites on the screen. These values are used for weapon bobbing and positioning calculations.

### PSPLayers Enumeration

```cpp
enum PSPLayers
{
    PSP_STRIFEHANDS = -1,
    PSP_CALLERID = 0,
    PSP_WEAPON = 1,
    PSP_FLASH = 1000,
    PSP_TARGETCENTER = INT_MAX - 2,
    PSP_TARGETLEFT,
    PSP_TARGETRIGHT,
};
```

Defines the different layers for player sprites. Each layer represents a different element that can be drawn on the screen:
- `PSP_STRIFEHANDS`: Special layer for Strife's hand graphics
- `PSP_CALLERID`: Layer for the caller ID (used by some custom weapons)
- `PSP_WEAPON`: Main weapon sprite layer
- `PSP_FLASH`: Muzzle flash layer
- `PSP_TARGETCENTER`, `PSP_TARGETLEFT`, `PSP_TARGETRIGHT`: Targeting reticle layers

### PSPFlags Enumeration

```cpp
enum PSPFlags
{
    PSPF_ADDWEAPON      = 1 << 0,
    PSPF_ADDBOB         = 1 << 1,
    PSPF_POWDOUBLE      = 1 << 2,
    PSPF_CVARFAST       = 1 << 3,
    PSPF_ALPHA          = 1 << 4,
    PSPF_RENDERSTYLE    = 1 << 5,
    PSPF_FLIP           = 1 << 6,
    PSPF_FORCEALPHA     = 1 << 7,
    PSPF_FORCESTYLE     = 1 << 8,
    PSPF_MIRROR         = 1 << 9,
    PSPF_PLAYERTRANSLATED = 1 << 10,
    PSPF_PIVOTPERCENT   = 1 << 11,
    PSPF_INTERPOLATE    = 1 << 12,
};
```

Flags that control various aspects of player sprite rendering and behavior:
- `PSPF_ADDWEAPON`: Add weapon offset to the sprite position
- `PSPF_ADDBOB`: Add bobbing motion to the sprite
- `PSPF_POWDOUBLE`: Apply power doubler effect (faster animation)
- `PSPF_CVARFAST`: Use weapon speed cvar for animation speed
- `PSPF_ALPHA`: Apply alpha transparency
- `PSPF_RENDERSTYLE`: Apply custom render style
- `PSPF_FLIP`: Flip the sprite horizontally
- `PSPF_FORCEALPHA`: Force alpha value regardless of game settings
- `PSPF_FORCESTYLE`: Force render style regardless of game settings
- `PSPF_MIRROR`: Mirror the sprite
- `PSPF_PLAYERTRANSLATED`: Apply player color translation
- `PSPF_PIVOTPERCENT`: Use percentage-based pivot point
- `PSPF_INTERPOLATE`: Interpolate sprite position between frames

### PSPAlign Enumeration

```cpp
enum PSPAlign
{
    PSPA_TOP = 0,
    PSPA_CENTER,
    PSPA_BOTTOM,
    PSPA_LEFT = PSPA_TOP,
    PSPA_RIGHT = 2
};
```

Defines alignment options for player sprites, controlling how they are positioned relative to their anchor points:
- `PSPA_TOP`/`PSPA_LEFT`: Align to the top/left
- `PSPA_CENTER`: Align to the center
- `PSPA_BOTTOM`/`PSPA_RIGHT`: Align to the bottom/right

### WeaponInterp Structure

```cpp
struct WeaponInterp
{
    FVector2 v[4];
};
```

A structure used for interpolating weapon positions between frames, storing four 2D vectors that represent the corners of the weapon sprite.

### DPSprite Class

```cpp
class DPSprite : public DObject
{
    // ... methods and members
};
```

The core class that represents a player sprite. It inherits from `DObject` and includes methods and properties for managing sprite state, animation, positioning, and rendering.

#### Key Methods

```cpp
DPSprite(player_t *owner, AActor *caller, int id);
static void NewTick();
void SetState(FState *newstate, bool pending = false);
std::pair<FRenderStyle, float> GetRenderStyle(FRenderStyle ownerstyle, double owneralpha);
float GetYAdjust(bool fullscreen);
```

- Constructor: Creates a new player sprite with the specified owner, caller, and ID
- `NewTick`: Static method called at the start of a new tick to update all player sprites
- `SetState`: Sets the sprite to a new state, optionally marking it as pending
- `GetRenderStyle`: Calculates the render style and alpha for the sprite
- `GetYAdjust`: Calculates vertical position adjustment based on screen size

#### Key Properties

```cpp
int HAlign, VAlign;         // Horizontal and vertical alignment
DVector2 baseScale;         // Base scale (set by weapon); defaults to (1.0, 1.2) since that's Doom's native aspect ratio
DAngle rotation;            // How much rotation to apply.
DVector2 pivot;             // pivot points
DVector2 scale;             // Dynamic scale (set by A_Overlay functions)
double x, y, alpha;         // Position and transparency
double oldx, oldy;          // Previous position for interpolation
bool InterpolateTic;        // One tic interpolation (WOF_INTERPOLATE)
DVector2 Coord[4];          // Offsets
WeaponInterp Prev;          // Interpolation
WeaponInterp Vert;          // Current Position
bool firstTic;              // First tick flag
int Tics;                   // Tics remaining in current state
FTranslationID Translation; // Color translation
int Flags;                  // Rendering flags
FRenderStyle Renderstyle;   // Render style
```

Properties that control the appearance, position, and behavior of the player sprite.

### Global Functions

```cpp
void P_NewPspriteTick();
void P_CalcSwing(player_t *player);
void P_SetPsprite(player_t *player, PSPLayers id, FState *state, bool pending = false);
void P_BringUpWeapon(player_t *player);
void P_FireWeapon(player_t *player);
void P_BobWeapon(player_t *player, float *x, float *y, double ticfrac);
void P_BobWeapon3D(player_t *player, FVector3 *translation, FVector3 *rotation, double ticfrac);
DAngle P_BulletSlope(AActor *mo, FTranslatedLineTarget *pLineTarget = NULL, int aimflags = 0);
AActor *P_AimTarget(AActor *mo);
```

Functions that handle various aspects of player sprite and weapon management:
- `P_NewPspriteTick`: Updates all player sprites for a new game tick
- `P_CalcSwing`: Calculates weapon swinging motion
- `P_SetPsprite`: Sets a player sprite to a new state
- `P_BringUpWeapon`: Initiates the weapon raising animation
- `P_FireWeapon`: Fires the player's current weapon
- `P_BobWeapon`: Calculates weapon bobbing motion in 2D
- `P_BobWeapon3D`: Calculates weapon bobbing motion in 3D
- `P_BulletSlope`: Calculates the slope for bullet projectiles
- `P_AimTarget`: Finds a target for auto-aim

### Weapon Ready State Functions

```cpp
void DoReadyWeaponToBob(AActor *self);
void DoReadyWeaponToFire(AActor *self, bool primary = true, bool secondary = true);
void DoReadyWeaponToSwitch(AActor *self, bool switchable = true);
```

Functions that prepare a weapon for different actions:
- `DoReadyWeaponToBob`: Prepares the weapon to bob with player movement
- `DoReadyWeaponToFire`: Prepares the weapon to be fired
- `DoReadyWeaponToSwitch`: Prepares the weapon to be switched

### Weapon Action Function

```cpp
void A_ReFire(AActor *self, FState *state = NULL);
```

A weapon action function that handles automatic refiring of weapons.

## Implementation Details

### Player Sprite Management
The player sprite system in GZDoom is designed to handle multiple sprite layers that can be independently animated and positioned. Each layer is represented by a `DPSprite` object, which is linked to a player and manages its own state, position, and rendering properties.

### Sprite Animation
Sprite animation is handled through the state system, with each sprite having a current state that defines its appearance and behavior. The `SetState` method is used to change a sprite's state, and the `Tics` property controls how long the sprite remains in its current state before advancing to the next one.

### Sprite Positioning
Sprites are positioned on the screen using a combination of base position, weapon offset, bobbing motion, and alignment. The `x` and `y` properties define the base position, which can be modified by various factors:
- Weapon offset: Added if the `PSPF_ADDWEAPON` flag is set
- Bobbing motion: Added if the `PSPF_ADDBOB` flag is set
- Alignment: Controlled by the `HAlign` and `VAlign` properties

### Sprite Rendering
Sprites are rendered with various visual effects controlled by the `Flags`, `Renderstyle`, and `alpha` properties. These allow for transparency, custom render styles, flipping, mirroring, and other visual effects.

### Weapon Bobbing
Weapon bobbing is a visual effect that makes the weapon move slightly as the player moves. It's implemented through the `P_BobWeapon` and `P_BobWeapon3D` functions, which calculate the bobbing motion based on the player's movement speed and direction.

### Weapon Firing
Weapon firing is handled by the `P_FireWeapon` function, which initiates the firing sequence for the player's current weapon. This typically involves changing the weapon sprite's state to a firing animation and creating projectiles or hitscan attacks.

## Connections with Other Modules
- Interfaces with the player system for weapon management
- Connects to the state system for sprite animation
- Interfaces with the rendering system for displaying sprites
- Used by the weapon code for implementing weapon behavior
- Connects to the input system for weapon control
- Interfaces with the sound system for weapon sounds
