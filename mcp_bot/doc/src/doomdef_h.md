# doomdef.h

## File Purpose
This header file defines fundamental constants, enumerations, and macros that are used throughout the GZDoom engine. It serves as a central repository for global parameters that control game behavior, compatibility options, and gameplay features. The file establishes the core definitions that shape how GZDoom operates and interacts with game content.

## Key Components

### Game Mode Definitions

- **`GameMode_t` Enumeration**: Identifies the IWAD version to handle game-specific animations and behaviors
  - `shareware`: DOOM 1 shareware (E1, M9)
  - `registered`: DOOM 1 registered (E3, M27)
  - `commercial`: DOOM 2 retail (E1, M34)
  - `retail`: DOOM 1 retail (E4, M36)
  - `undetermined`: No IWAD found

### Core Game Constants

- **`TICRATE`**: Defines the number of game tics per second (35)
- **`TELEFRAG_DAMAGE`**: Amount of damage done by a telefrag (1,000,000)
- **`TELEFOGHEIGHT`**: Height of teleportation fog
- **`Tics2Seconds()`**: Utility function to convert tics to seconds

### Gameplay Flags

#### dmflags (First Set)
- **`DF_NO_HEALTH`**: Do not spawn health items in deathmatch
- **`DF_NO_ITEMS`**: Do not spawn powerups in deathmatch
- **`DF_WEAPONS_STAY`**: Weapons remain after pickup in deathmatch
- **`DF_FORCE_FALLING*`**: Different falling damage models (ZDoom, Hexen, Strife)
- **`DF_SAME_LEVEL`**: Stay on the same map when someone exits
- **`DF_SPAWN_FARTHEST`**: Spawn players as far as possible from others
- **`DF_FORCE_RESPAWN`**: Automatically respawn dead players
- **`DF_NO_MONSTERS`**: Don't spawn monsters
- **`DF_MONSTERS_RESPAWN`**: Monsters respawn after death
- **`DF_ITEMS_RESPAWN`**: Items respawn after pickup
- **`DF_FAST_MONSTERS`**: Monsters move and attack faster
- **`DF_NO_JUMP`/`DF_YES_JUMP`**: Control jumping ability
- **`DF_NO_FREELOOK`/`DF_YES_FREELOOK`**: Control freelook ability
- **`DF_NO_FOV`**: Only arbitrator can set FOV
- **`DF_NO_CROUCH`/`DF_YES_CROUCH`**: Control crouching ability
- **`DF_COOP_LOSE_*`**: Control inventory loss on respawn in cooperative mode
- **`DF_INSTANT_REACTION`**: Monsters react instantly

#### dmflags2 (Second Set)
- **`DF2_YES_WEAPONDROP`**: Drop current weapon upon death
- **`DF2_NO_TEAM_SWITCH`**: Prevent team switching in team games
- **`DF2_YES_DOUBLEAMMO`**: Double ammo from pickups
- **`DF2_YES_DEGENERATION`**: Health slowly decreases when over 100%
- **`DF2_NO_FREEAIMBFG`**: Disallow BFG freeaiming
- **`DF2_BARRELS_RESPAWN`**: Exploded barrels respawn
- **`DF2_YES_RESPAWN_INVUL`**: Temporary invulnerability on respawn
- **`DF2_SAME_SPAWN_SPOT`**: Respawn in the same place as death
- **`DF2_YES_KEEPFRAGS`**: Don't clear frags between levels
- **`DF2_NO_RESPAWN`**: Player cannot respawn
- **`DF2_INFINITE_INVENTORY`**: Infinite inventory
- **`DF2_KILL_MONSTERS`**: All monsters must be killed before exit
- **`DF2_NO_AUTOMAP`**: Disable automap
- **`DF2_NOSUICIDE`**: Players cannot suicide
- **`DF2_NOAUTOAIM`**: Disable autoaim
- **`DF2_RESPAWN_SUPER`**: Respawn invulnerability and invisibility
- **`DF2_NO_EXTRA_AMMO`**: Don't add extra ammo when picking up weapons

#### dmflags3 (Third Set)
- **`DF3_NO_PLAYER_CLIP`**: Players can walk through each other
- **`DF3_COOP_SHARE_KEYS`**: Keys are given to all players in coop
- **`DF3_LOCAL_ITEMS`**: Items are picked up client-side
- **`DF3_NO_LOCAL_DROPS`**: Drops aren't picked up locally
- **`DF3_NO_COOP_ONLY_ITEMS`**: Disable coop-only items
- **`DF3_REMEMBER_LAST_WEAP`**: Keep last used weapon on respawn
- **`DF3_PISTOL_START`**: Reset inventory between levels

### Compatibility Flags

#### compatflags (First Set)
- **`COMPATF_SHORTTEX`**: Use Doom's shortest texture around behavior
- **`COMPATF_STAIRINDEX`**: Don't fix loop index for stair building
- **`COMPATF_LIMITPAIN`**: Pain elemental limited to 20 lost souls
- **`COMPATF_SILENTPICKUP`**: Pickups only heard locally
- **`COMPATF_NO_PASSMOBJ`**: Treat actors as infinitely tall
- **`COMPATF_MAGICSILENCE`**: Limit actors to one sound at a time
- **`COMPATF_WALLRUN`**: Enable buggier wall clipping for wall running
- **`COMPATF_NOTOSSDROPS`**: Spawn dropped items directly on floor
- **`COMPATF_SOUNDTARGET`**: Use sector-based sound target code
- **`COMPATF_DEHHEALTH`**: Limit deh.MaxHealth to health bonus
- **`COMPATF_INVISIBILITY`**: Monsters can see semi-invisible players
- **`COMPATF_MISSILECLIP`**: Use original Doom heights for projectile clipping
- **`COMPATF_CROSSDROPOFF`**: Monsters can't be pushed over dropoffs
- **`COMPATF_VILEGHOSTS`**: Crushed monsters resurrected as ghosts
- **`COMPATF_HITSCAN`**: Use original blockmap and hit check code
- **`COMPATF_LIGHT`**: Find neighboring light level like Doom
- **`COMPATF_POLYOBJ`**: Draw polyobjects the old way
- **`COMPATF_MASKEDMIDTEX`**: Ignore compositing for masked midtextures

#### compatflags2 (Second Set)
- **`COMPATF2_BADANGLES`**: Impossible to face directly NSEW
- **`COMPATF2_FLOORMOVE`**: Use Doom's floor motion behavior
- **`COMPATF2_POINTONLINE`**: Use original but buggy line side detection
- **`COMPATF2_MULTIEXIT`**: Level exit can be triggered multiple times
- **`COMPATF2_TELEPORT`**: Don't let indirect teleports trigger sector actions
- **`COMPATF2_EXPLODE1`**: No vertical explosion thrust
- **`COMPATF2_EXPLODE2`**: Use original explosion code
- **`COMPATF2_AVOID_HAZARDS`**: MBF monster hazard avoidance
- **`COMPATF2_STAYONLIFT`**: MBF monster behavior on lifts
- **`COMPATF2_NOMBF21`**: Disable MBF21 features
- **`COMPATF2_VOODOO_ZOMBIES`**: Allow voodoo doll zombies

### Bug Compatibility Flags

- **`BCOMPATF_SETSLOPEOVERFLOW`**: SetSlope things can overflow
- **`BCOMPATF_RESETPLAYERSPEED`**: Reset player speed between maps
- **`BCOMPATF_BADTELEPORTERS`**: Ignore tags on Teleport specials
- **`BCOMPATF_BADPORTALS`**: Restore old unstable portal behavior
- **`BCOMPATF_REBUILDNODES`**: Force node rebuild
- **`BCOMPATF_FLOATBOB`**: Use Hexen's original floatbobbing method
- **`BCOMPATF_NOSLOPEID`**: Disable line IDs on slopes
- **`BCOMPATF_CLIPMIDTEX`**: Always clip midtextures in software renderer
- **`BCOMPATF_NOMIRRORS`**: Disable mirrors for broken map setups

### Physics Constants

- **`MORE_FRICTION_VELOCITY`**: Mud factor based on velocity
- **`ORIG_FRICTION`**: Original friction value
- **`ORIG_FRICTION_FACTOR`**: Original friction factor
- **`FRICTION_LOW`**: Low friction value (ice)
- **`FRICTION_FLY`**: Friction value for flying

## Technical Details

### Range Checking

- Conditional compilation for parameter validation debugging code
- `RANGECHECK` define controls inclusion of range checking code

### Special Activation Types

- `SPAC_*` constants define how special lines are activated
- `GET_SPAC()` function extracts activation type from line flags

### Skill Level Handling

- `skill_t` type defined as float for flexible skill levels

## Connections with Other Modules

- Includes `i_net.h` for network definitions
- Referenced by most core engine files
- Provides fundamental constants used throughout the codebase
- Controls compatibility settings for different game versions
- Defines flags that modify gameplay behavior
