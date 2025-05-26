# d_player.h

## File Purpose
This header file defines the core player structures and systems in GZDoom. It contains the `player_t` class, which represents a player in the game, along with supporting structures for player classes, user information, and player states. This file is central to player-related functionality, including movement, weapons, inventory, cheats, and visual effects.

## Key Components

### Player State Enumerations

#### playerstate_t
```cpp
typedef enum
{
    PST_LIVE,   // Playing or camping.
    PST_DEAD,   // Dead on the ground, view follows killer.
    PST_REBORN, // Ready to restart/respawn???
    PST_ENTER,  // [BC] Entered the game
    PST_GONE    // Player has left the game
} playerstate_t;
```

Defines the possible states a player can be in during gameplay.

#### Cheat Flags (cheat_t)
```cpp
typedef enum
{
    CF_NOCLIP           = 1 << 0,  // No clipping, walk through barriers.
    CF_GODMODE          = 1 << 1,  // No damage, no health loss.
    // ... many more cheat flags
} cheat_t;
```

Defines various cheat and debug flags that can be applied to players.

#### Weapon Flags
```cpp
enum
{
    WF_WEAPONREADY      = 1 << 0,  // Weapon is in the ready state and can fire its primary attack
    WF_WEAPONBOBBING    = 1 << 1,  // Bob weapon while the player is moving
    // ... more weapon flags
};
```

Defines flags that control weapon behavior and state.

### Player Class System

#### FPlayerClass
```cpp
class FPlayerClass
{
public:
    FPlayerClass ();
    FPlayerClass (const FPlayerClass &other) = default;
    ~FPlayerClass ();

    bool CheckSkin (int skin);

    PClassActor *Type;
    uint32_t Flags;
    TArray<int> Skins;
};
```

Represents a player class definition, which determines the player's actor type, available skins, and other properties.

#### Player Class Flags
```cpp
enum
{
    PCF_NOMENU          = 1,    // Hide in new game menu
};
```

Flags that control player class behavior.

### User Information System

#### userinfo_t
```cpp
struct userinfo_t : TMap<FName,FBaseCVar *>
{
    ~userinfo_t();

    // Various getter methods for user preferences
    double GetAimDist() const;
    double GetAutoaim() const;
    const char *GetName(unsigned int charLimit = 0u) const;
    int GetTeam() const;
    // ... many more getters

    void Reset(int pnum);
    int TeamChanged(int team);
    int SkinChanged(const char *skinname, int playerclass);
    // ... more change notification methods
};
```

Stores player-specific settings and preferences, implemented as a map of console variables. Includes methods for accessing and modifying these settings.

### Player Customization

#### FPlayerColorSet
```cpp
struct FPlayerColorSet
{
    struct ExtraRange
    {
        uint8_t RangeStart, RangeEnd;   // colors to remap
        uint8_t FirstColor, LastColor;  // colors to map to
    };

    FName Name;         // Name of this color
    int Lump;           // Lump to read the translation from, otherwise use next 2 fields
    uint8_t FirstColor, LastColor;      // Describes the range of colors to use for the translation
    // ... more fields
};
```

Defines a color translation set for player sprites, allowing for customized player colors.

### Player Class (player_t)

```cpp
class player_t
{
public:
    player_t();
    ~player_t();
    player_t &operator= (const player_t &p) = delete;
    void CopyFrom(player_t &src, bool copyPSP);

    void Serialize(FSerializer &arc);
    size_t PropagateMark();

    // Various player methods
    void SetLogNumber (int num);
    void SetLogText (const char *text);
    void SendPitchLimits() const;
    // ... more methods

    // Core player properties
    AActor *mo = nullptr;               // The actor controlled by this player
    uint8_t playerstate = 0;            // Current state (alive, dead, etc.)
    usercmd_t cmd = {};                 // Current input command
    usercmd_t original_cmd = {};        // Original input command before modifications
    uint32_t original_oldbuttons = 0;   // Previous button state

    userinfo_t userinfo;                // Player settings and preferences
    PClassActor *cls = nullptr;         // Class of associated PlayerPawn

    // View properties
    float DesiredFOV = 0;               // Desired field of vision
    float FOV = 0;                      // Current field of vision
    double viewz = 0;                   // Focal origin above r.z
    double viewheight = 0;              // Base height above floor for viewz
    double deltaviewheight = 0;         // Squat speed
    double bob = 0;                     // Bounded/scaled total velocity

    // Movement properties
    DVector2 Vel = { 0.0, 0.0 };        // Player's applied thrust (not total velocity)
    bool centering = false;             // True if view centering
    uint8_t turnticks = 0;              // Counter for turn sequence

    // Input state
    bool attackdown = false;            // True if attack button down last tic
    bool usedown = false;               // True if use button down last tic
    uint32_t oldbuttons = false;        // Buttons last frame

    // Player stats
    int health = 0;                     // Only used between levels
    int inventorytics = 0;              // Inventory display timer
    uint8_t CurrentPlayerClass = 0;     // Class # for this player instance
    int frags[MAXPLAYERS] = {};         // Kills of other players
    int fragcount = 0;                  // Cumulative frags for this player
    int lastkilltime = 0;               // For multikills
    uint8_t multicount = 0;             // Multikill counter
    uint8_t spreecount = 0;             // Killing spree counter

    // Weapon state
    uint16_t WeaponState = 0;           // Flags for weapon state
    AActor *ReadyWeapon = nullptr;      // Current ready weapon
    AActor *PendingWeapon = nullptr;    // Weapon to switch to (WP_NOCHANGE if not changing)
    TObjPtr<DPSprite*> psprites = MakeObjPtr<DPSprite*>(nullptr); // View sprites (gun, etc.)
    short refire = 0;                   // Refired shots are less accurate

    // Cheat and special effect state
    int cheats = 0;                     // Bit flags for cheats
    int timefreezer = 0;                // Player has an active time freezer
    uint32_t damagecount = 0;           // For screen flashing on damage
    uint32_t bonuscount = 0;            // For screen flashing on bonus
    int extralight = 0;                 // So gun flashes light up areas
    short fixedcolormap = 0;            // Can be set to REDCOLORMAP, etc.
    short fixedlightlevel = 0;          // Fixed light level

    // Morphing state
    int morphTics = 0;                  // Player is morphed if > 0
    PClassActor *MorphedPlayerClass = nullptr; // Class when morphed
    int MorphStyle = 0;                 // Which effects to apply when morphed
    PClassActor *MorphExitFlash = nullptr; // Flash to apply when demorphing
    TObjPtr<AActor*> PremorphWeapon = MakeObjPtr<AActor*>(nullptr); // Ready weapon before morphing

    // Miscellaneous state
    int respawn_time = 0;               // Delay respawning until this tic
    TObjPtr<AActor*> camera = MakeObjPtr<AActor*>(nullptr); // Whose eyes this player sees through
    int air_finished = 0;               // Time when you start drowning
    FName LastDamageType = NAME_None;   // For damage-specific pain and death sounds
    bool settings_controller = false;   // Player can control game settings
    int8_t crouching = 0;               // Crouching state
    int8_t crouchdir = 0;               // Direction of crouching (down/up)

    // Bot support
    TObjPtr<DBot*> Bot = MakeObjPtr<DBot*>(nullptr); // Bot AI controller

    // Visual effects
    float BlendR = 0;                   // Final blending values
    float BlendG = 0;
    float BlendB = 0;
    float BlendA = 0;

    // Conversation system
    TObjPtr<AActor*> ConversationNPC = MakeObjPtr<AActor*>(nullptr); // NPC the player is talking to
    TObjPtr<AActor*> ConversationPC = MakeObjPtr<AActor*>(nullptr);  // Player actor in conversation
    DAngle ConversationNPCAngle = nullAngle; // Original angle of NPC
    bool ConversationFaceTalker = false;     // Whether NPC should face player

    // Utility methods
    double GetDeltaViewHeight() const;
    double DefaultViewHeight() const;
    void Uncrouch();
    int GetSpawnClass();
    void TickPSprites();
    void DestroyPSprites();
    DPSprite *FindPSprite(int layer);
    DPSprite *GetPSprite(PSPLayers layer);
    void SetFOV(float fov);
    bool HasWeaponsInSlot(int slot) const;
    bool Resurrect();

    // View angle adjustment
    DRotator angleOffsetTargets;
};
```

The main player class that represents a player in the game. Contains extensive properties and methods for handling all aspects of player behavior.

### Global Variables and Functions

#### players Array
```cpp
extern player_t players[MAXPLAYERS];
```

The global array of player objects, one for each potential player in the game.

#### Helper Functions
```cpp
void P_CheckPlayerSprite(AActor *mo, int &spritenum, DVector2 &scale);
void EnumColorSets(PClassActor *pc, TArray<int> *out);
FPlayerColorSet *GetColorSet(PClassActor *pc, int setnum);
bool P_IsPlayerTotallyFrozen(const player_t *player);
bool P_NoInterpolation(player_t const *player, AActor const *actor);
```

Various utility functions for working with players and player sprites.

#### AActor Extensions
```cpp
inline void AActor::SetFriendPlayer(player_t *player);
inline bool AActor::IsNoClip2() const;
```

Extensions to the `AActor` class for player-related functionality.

## Implementation Details

### Player Input Handling
The player's input is stored in the `cmd` field, which contains the current input command. This includes movement, turning, and button presses. The `original_cmd` field stores the unmodified input command.

### Player View System
The player's view is controlled by several properties:
- `FOV` and `DesiredFOV` for field of vision
- `viewz` and `viewheight` for vertical positioning
- `bob` for view bobbing during movement

### Weapon System
The player's weapons are managed through:
- `ReadyWeapon` for the currently active weapon
- `PendingWeapon` for a weapon being switched to
- `psprites` for the weapon sprites displayed on screen
- `WeaponState` for flags controlling weapon behavior

### Player State Management
The player's state is tracked through:
- `playerstate` for the basic state (alive, dead, etc.)
- `health` for the player's health
- `cheats` for active cheat flags
- Various counters for damage, bonuses, etc.

### Morphing System
The player can be morphed into different forms, controlled by:
- `morphTics` for the duration of the morph
- `MorphedPlayerClass` for the class when morphed
- `MorphStyle` for the effects applied during morphing
- `MorphExitFlash` for the effect when demorphing

### Crouching System
The player's crouching state is managed through:
- `crouching` for the current state
- `crouchdir` for the direction of crouching
- `crouchfactor` for the current crouch amount
- `crouchoffset` and `crouchviewdelta` for view adjustments

## Connections with Other Modules
- Interfaces with the `AActor` class for the player's physical representation
- Connects to the weapon system through `ReadyWeapon` and `psprites`
- Links to the input system through the `cmd` structure
- Interfaces with the rendering system for view positioning and effects
- Connects to the conversation system for NPC interactions
- Links to the bot system for AI-controlled players
- Interfaces with the cheat system through the `cheats` flags
