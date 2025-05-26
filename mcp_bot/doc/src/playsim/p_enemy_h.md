# p_enemy.h

## File Purpose
This header file defines the structures and functions for enemy AI and behavior in GZDoom. It provides the foundation for monster movement, targeting, attacking, and other AI-related functionality. The file is essential for the game's combat mechanics, as it controls how enemies interact with players and other actors in the game world.

## Key Components

### Direction Types
```cpp
enum dirtype_t
{
    DI_EAST,
    DI_NORTHEAST,
    DI_NORTH,
    DI_NORTHWEST,
    DI_WEST,
    DI_SOUTHWEST,
    DI_SOUTH,
    DI_SOUTHEAST,
    DI_NODIR,
    NUMDIRS
};
```

An enumeration defining the eight cardinal and ordinal directions, plus a special `DI_NODIR` value indicating no direction. This is used for monster movement and pathfinding.

### Direction Speed Tables
```cpp
extern double xspeed[8], yspeed[8];
```

Arrays containing the X and Y components of movement for each of the eight directions, used to calculate monster movement vectors.

### Look Operation Flags
```cpp
enum LO_Flags
{
    LOF_NOSIGHTCHECK = 1,
    LOF_NOSOUNDCHECK = 2,
    LOF_DONTCHASEGOAL = 4,
    LOF_NOSEESOUND = 8,
    LOF_FULLVOLSEESOUND = 16,
    LOF_NOJUMP = 32,
};
```

Flags that control various aspects of monster sight and sound detection, as well as behavior when a target is spotted.

### Look Parameters Structure
```cpp
struct FLookExParams
{
    DAngle Fov;
    double minDist;
    double maxDist;
    double maxHeardist;
    int flags;
    FState *seestate;
};
```

A structure that encapsulates parameters for monster sight and sound detection, including field of view, minimum and maximum distances, and flags.

### Monster Interaction Functions
```cpp
int P_HitFriend(AActor *self);
void P_NoiseAlert(AActor *emitter, AActor *target, bool splash=false, double maxdist=0);
int P_CheckMeleeRange(AActor* actor, double range = -1);
bool P_CheckMeleeRange2(AActor *actor);
```

Functions that handle various aspects of monster interaction:
- `P_HitFriend` checks if an actor has hit a friendly actor
- `P_NoiseAlert` alerts monsters to a noise source
- `P_CheckMeleeRange` and `P_CheckMeleeRange2` check if a target is within melee range

### Monster Movement Functions
```cpp
int P_SmartMove(AActor *actor);
bool P_TryWalk(AActor *actor);
void P_NewChaseDir(AActor *actor);
void P_RandomChaseDir(AActor *actor);
```

Functions that handle monster movement and pathfinding:
- `P_SmartMove` implements intelligent movement for monsters
- `P_TryWalk` attempts to move a monster in its current direction
- `P_NewChaseDir` calculates a new direction for a monster to chase its target
- `P_RandomChaseDir` selects a random direction for a monster to move

### Target Acquisition Functions
```cpp
int P_IsVisible(AActor *lookee, AActor *other, INTBOOL allaround, FLookExParams *params);
int P_LookForMonsters(AActor *actor);
int P_LookForTID(AActor *actor, INTBOOL allaround, FLookExParams *params);
int P_LookForEnemies(AActor *actor, INTBOOL allaround, FLookExParams *params);
int P_LookForPlayers(AActor *actor, INTBOOL allaround, FLookExParams *params);
```

Functions that handle monster target acquisition:
- `P_IsVisible` checks if one actor is visible to another
- `P_LookForMonsters` searches for monster targets
- `P_LookForTID` searches for targets with a specific TID (Thing ID)
- `P_LookForEnemies` searches for enemy targets
- `P_LookForPlayers` searches for player targets

### Item Drop Functions
```cpp
AActor *P_DropItem(AActor *source, PClassActor *type, int special, int chance);
void P_TossItem(AActor *item);
```

Functions that handle item dropping:
- `P_DropItem` creates a new item dropped by a monster
- `P_TossItem` applies a random velocity to a dropped item

### Monster Action Functions
```cpp
void A_Weave(AActor *self, int xyspeed, int zspeed, double xydist, double zdist);
void A_Unblock(AActor *self, bool drop);
void A_BossDeath(AActor *self);
void A_Wander(AActor *self, int flags = 0);
void A_DoChase(AActor *actor, bool fastchase, FState *meleestate, FState *missilestate, bool playactive, bool nightmarefast, bool dontmove, int flags);
void A_Chase(AActor *self);
void A_FaceTarget(AActor *actor);
void A_Face(AActor *self, AActor *other, DAngle max_turn = nullAngle, DAngle max_pitch = DAngle::fromDeg(270.), DAngle ang_offset = nullAngle, DAngle pitch_offset = nullAngle, int flags = 0, double z_add = 0);
void A_SkullAttack(AActor *self, double speed);
```

Functions that implement various monster actions:
- `A_Weave` makes a monster move in a weaving pattern
- `A_Unblock` makes a monster unblock its current position
- `A_BossDeath` handles special effects when a boss monster dies
- `A_Wander` makes a monster wander randomly
- `A_DoChase` and `A_Chase` implement monster chase behavior
- `A_FaceTarget` and `A_Face` make a monster turn to face its target
- `A_SkullAttack` implements the flying skull attack behavior

### Miscellaneous Functions
```cpp
int CheckBossDeath(AActor *);
int P_Massacre(bool baddies = false, PClassActor *cls = nullptr);
```

Miscellaneous functions:
- `CheckBossDeath` checks if a boss monster has died and triggers any special effects
- `P_Massacre` kills all monsters of a specific class or all monsters in the level

## Implementation Details

### Monster Movement
Monster movement in GZDoom is based on a grid-based pathfinding system:
- Monsters move in one of eight directions (cardinal and ordinal)
- Movement is calculated using the `xspeed` and `yspeed` tables
- Monsters can change direction to avoid obstacles or to chase a target
- The `P_SmartMove` function handles intelligent movement, including obstacle avoidance

### Target Acquisition
Monsters acquire targets through several mechanisms:
- Line of sight checks using `P_IsVisible`
- Sound detection using `P_NoiseAlert`
- Active searching using the various `P_LookFor*` functions
- Targets can be players, other monsters, or specific actors with a TID

### Monster Actions
Monsters can perform various actions:
- Chasing a target using `A_Chase`
- Attacking a target when in range
- Wandering randomly using `A_Wander`
- Special attacks like the flying skull attack using `A_SkullAttack`

### Boss Monsters
Boss monsters have special handling:
- `A_BossDeath` triggers special effects when a boss monster dies
- `CheckBossDeath` checks if a boss monster has died and triggers level progression

## Connections with Other Modules
- Interfaces with the actor system for monster behavior
- Connects to the player system for targeting players
- Interfaces with the map system for pathfinding
- Connects to the sound system for noise alerts
- Used by the game logic for level progression
- Interfaces with the state system for monster state changes
