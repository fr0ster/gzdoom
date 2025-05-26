# p_enemy.cpp

## File Purpose
This implementation file provides the core functionality for enemy AI and behavior in GZDoom. It implements the functions declared in `p_enemy.h`, handling monster movement, targeting, attacking, and other AI-related functionality. The file is essential for the game's combat mechanics, as it controls how enemies interact with players and other actors in the game world.

## Key Components

### Direction Speed Tables
```cpp
double xspeed[8] = {1, 0.7171630859, 0, -0.7171630859, -1, -0.7171630859, 0, 0.7171630859};
double yspeed[8] = {0, 0.7171630859, 1, 0.7171630859, 0, -0.7171630859, -1, -0.7171630859};
```

Arrays containing the X and Y components of movement for each of the eight cardinal and ordinal directions. These values are normalized to provide consistent movement speed regardless of direction.

### Monster Interaction Functions

#### P_HitFriend
```cpp
int P_HitFriend(AActor *self)
```

Checks if an actor has hit a friendly actor during an attack. This is used to prevent friendly fire between monsters of the same type or faction.

#### P_NoiseAlert
```cpp
void P_NoiseAlert(AActor *emitter, AActor *target, bool splash, double maxdist)
```

Alerts monsters to a noise source, causing them to potentially wake up and target the noise emitter. The `splash` parameter determines if the alert affects a wide area, and `maxdist` limits the maximum distance of the alert.

#### P_CheckMeleeRange and P_CheckMeleeRange2
```cpp
int P_CheckMeleeRange(AActor* actor, double range)
bool P_CheckMeleeRange2(AActor *actor)
```

Check if a target is within melee range of an actor. `P_CheckMeleeRange` uses a specified range or the actor's default melee range, while `P_CheckMeleeRange2` uses a more complex calculation based on the actor's size and target's size.

### Monster Movement Functions

#### P_SmartMove
```cpp
int P_SmartMove(AActor *actor)
```

Implements intelligent movement for monsters, handling obstacle avoidance, ledge detection, and door interaction. Returns a result code indicating the success or failure of the movement attempt.

#### P_TryWalk
```cpp
bool P_TryWalk(AActor *actor)
```

Attempts to move a monster in its current direction. If the movement is blocked, it returns false, indicating that a new direction should be chosen.

#### P_NewChaseDir
```cpp
void P_NewChaseDir(AActor *actor)
```

Calculates a new direction for a monster to chase its target. This function uses a simple pathfinding algorithm to determine the best direction to move towards the target while avoiding obstacles.

#### P_RandomChaseDir
```cpp
void P_RandomChaseDir(AActor *actor)
```

Selects a random direction for a monster to move. This is used when a monster has no target or when it cannot find a path to its target.

### Target Acquisition Functions

#### P_IsVisible
```cpp
int P_IsVisible(AActor *lookee, AActor *other, INTBOOL allaround, FLookExParams *params)
```

Checks if one actor is visible to another, taking into account line of sight, distance, field of view, and other factors. The `allaround` parameter determines if the lookee can see in all directions, and `params` provides additional parameters for the visibility check.

#### P_LookForMonsters, P_LookForTID, P_LookForEnemies, P_LookForPlayers
```cpp
int P_LookForMonsters(AActor *actor)
int P_LookForTID(AActor *actor, INTBOOL allaround, FLookExParams *params)
int P_LookForEnemies(AActor *actor, INTBOOL allaround, FLookExParams *params)
int P_LookForPlayers(AActor *actor, INTBOOL allaround, FLookExParams *params)
```

Functions that search for potential targets for a monster. Each function focuses on a different type of target:
- `P_LookForMonsters` searches for monster targets
- `P_LookForTID` searches for targets with a specific TID (Thing ID)
- `P_LookForEnemies` searches for enemy targets
- `P_LookForPlayers` searches for player targets

### Item Drop Functions

#### P_DropItem
```cpp
AActor *P_DropItem(AActor *source, PClassActor *type, int special, int chance)
```

Creates a new item dropped by a monster. The `type` parameter specifies the class of the item, `special` sets any special properties, and `chance` determines the probability of the item being dropped.

#### P_TossItem
```cpp
void P_TossItem(AActor *item)
```

Applies a random velocity to a dropped item, causing it to be "tossed" away from its drop position.

### Monster Action Functions

#### A_Weave
```cpp
void A_Weave(AActor *self, int xyspeed, int zspeed, double xydist, double zdist)
```

Makes a monster move in a weaving pattern, useful for flying monsters or projectiles. The parameters control the speed and amplitude of the weaving motion.

#### A_Unblock
```cpp
void A_Unblock(AActor *self, bool drop)
```

Makes a monster unblock its current position, allowing other actors to pass through. The `drop` parameter determines if the monster should also drop to the floor.

#### A_BossDeath
```cpp
void A_BossDeath(AActor *self)
```

Handles special effects when a boss monster dies, such as triggering level progression or special effects.

#### A_Wander
```cpp
void A_Wander(AActor *self, int flags)
```

Makes a monster wander randomly, changing direction periodically. The `flags` parameter controls various aspects of the wandering behavior.

#### A_DoChase and A_Chase
```cpp
void A_DoChase(AActor *actor, bool fastchase, FState *meleestate, FState *missilestate, bool playactive, bool nightmarefast, bool dontmove, int flags)
void A_Chase(AActor *self)
```

Implement monster chase behavior. `A_DoChase` is the core implementation, while `A_Chase` is a wrapper that calls `A_DoChase` with default parameters. These functions handle chasing a target, attacking when in range, and changing direction when necessary.

#### A_FaceTarget and A_Face
```cpp
void A_FaceTarget(AActor *actor)
void A_Face(AActor *self, AActor *other, DAngle max_turn, DAngle max_pitch, DAngle ang_offset, DAngle pitch_offset, int flags, double z_add)
```

Make a monster turn to face its target. `A_FaceTarget` is a simple wrapper that calls `A_Face` with the actor's current target.

#### A_SkullAttack
```cpp
void A_SkullAttack(AActor *self, double speed)
```

Implements the flying skull attack behavior, where a monster flies directly at its target at a specified speed.

### Miscellaneous Functions

#### CheckBossDeath
```cpp
int CheckBossDeath(AActor *actor)
```

Checks if a boss monster has died and triggers any special effects or level progression. Returns a value indicating if the boss death was handled specially.

#### P_Massacre
```cpp
int P_Massacre(bool baddies, PClassActor *cls)
```

Kills all monsters of a specific class or all monsters in the level. The `baddies` parameter determines if only hostile monsters should be killed, and `cls` specifies a specific class of monsters to kill.

## Implementation Details

### Monster Movement
The implementation of monster movement in GZDoom is based on a grid-based pathfinding system:
- Monsters move in one of eight directions (cardinal and ordinal)
- Movement is calculated using the `xspeed` and `yspeed` tables
- The `P_SmartMove` function handles intelligent movement, including:
  - Obstacle avoidance
  - Ledge detection (monsters won't walk off ledges unless they can fly or have the `DROPOFF` flag)
  - Door interaction (monsters can open doors if they have the `CANUSEWALLS` flag)
  - Special line activation (monsters can activate certain special lines)
- The `P_NewChaseDir` function implements a simple pathfinding algorithm to determine the best direction to move towards a target

### Target Acquisition
The implementation of target acquisition in GZDoom involves several mechanisms:
- Line of sight checks using `P_IsVisible`, which:
  - Traces a line from the monster to the potential target
  - Checks if the line is blocked by walls or other obstacles
  - Considers the monster's field of view (if `allaround` is false)
  - Takes into account distance and other factors
- Sound detection using `P_NoiseAlert`, which:
  - Wakes up sleeping monsters in the vicinity of a noise
  - Causes monsters to target the noise source
  - Can affect a wide area if `splash` is true
- Active searching using the various `P_LookFor*` functions, which:
  - Scan for potential targets in the monster's vicinity
  - Check if the potential targets are visible
  - Consider factors like distance, field of view, and target type

### Monster Actions
The implementation of monster actions in GZDoom includes:
- Chasing a target using `A_Chase`, which:
  - Moves the monster towards its target
  - Attacks the target when in range
  - Changes direction when necessary
- Attacking a target when in range, which:
  - Uses `P_CheckMeleeRange` to check if the target is within melee range
  - Transitions to the appropriate attack state
- Wandering randomly using `A_Wander`, which:
  - Changes direction periodically
  - Avoids obstacles and ledges
- Special attacks like the flying skull attack using `A_SkullAttack`, which:
  - Makes the monster fly directly at its target
  - Handles collision detection and damage

### Boss Monsters
The implementation includes special handling for boss monsters:
- `A_BossDeath` triggers special effects when a boss monster dies, such as:
  - Ending the level
  - Triggering special effects
  - Unlocking doors or revealing secrets
- `CheckBossDeath` checks if a boss monster has died and triggers level progression, considering:
  - The specific type of boss
  - The level's special requirements for progression
  - Any special effects that should be triggered

## Connections with Other Modules
- Interfaces with the actor system for monster behavior and state changes
- Connects to the player system for targeting players and handling player-monster interactions
- Interfaces with the map system for pathfinding, line of sight checks, and special line activation
- Connects to the sound system for noise alerts and monster sounds
- Used by the game logic for level progression and special events
- Interfaces with the state system for monster state changes and animation
