# g_cvars.cpp

## File Purpose
This source file implements console variables (CVars) that were previously scattered throughout the GZDoom codebase. It serves as a central location for defining game-related configuration variables that control various aspects of the engine's behavior, including rendering, gameplay mechanics, and performance settings.

## Key Components

### Decal and Particle System CVars

- **`cl_spreaddecals`**: Controls whether decals are spread throughout the game world.
- **`cl_maxdecals`**: Sets the maximum number of impact decals allowed in the game world.
- **`r_maxparticles`**: Defines the maximum number of particles that can exist simultaneously.

### Physics and Gameplay CVars

- **`var_pushers`**: Controls whether push forces are active in the game.
- **`var_friction`**: Controls whether friction is applied to moving objects.
- **`alwaysapplydmflags`**: Determines if deathmatch flags should always be applied, even in non-deathmatch games.

### Movement Control CVars

- **`turnspeedwalkfast`**: Controls the turning speed when walking fast.
- **`turnspeedsprintfast`**: Controls the turning speed when sprinting fast.
- **`turnspeedwalkslow`**: Controls the turning speed when walking slowly.
- **`turnspeedsprintslow`**: Controls the turning speed when sprinting slowly.

### Rendering and Graphics CVars

- **`gl_lights`**: Toggles OpenGL lighting effects.
- **`gl_cachenodes`**: Controls whether BSP nodes are cached.
- **`gl_cachetime`**: Sets the time for which BSP nodes remain cached.
- **`cl_scaleweaponfov`**: Controls the scaling of weapon field of view.

### Multiplayer CVars

- **`sv_corpsequeuesize`**: Sets the maximum number of corpses that can exist in the game world.
- **`teamdamage`**: Controls the amount of damage players can inflict on teammates.

## Technical Details

- Uses `CVAR` and `CUSTOM_CVAR` macros to define console variables with various flags.
- Implements custom validation and side effects for certain CVars through callback functions.
- Applies changes to all game levels when appropriate through the `AllLevels()` iterator.
- Uses flags like `CVAR_ARCHIVE`, `CVAR_SERVERINFO`, and `CVAR_GLOBALCONFIG` to control CVar behavior.
- Includes bounds checking and correction for numeric CVars.

## Implementation Details

### CVar Callbacks

- **`gl_lights`**: When changed, recreates or deletes attached lights in all levels.
- **`sv_corpsequeuesize`**: When reduced, removes excess corpses from the queue.
- **`cl_maxdecals`**: When reduced, removes excess decals from the world.
- **`r_maxparticles`**: When changed, reinitializes the particle system with new limits.
- **`teamdamage`**: When changed, updates the teamdamage value for all levels.
- **`turnspeed*`**: Ensures values are always positive.

## Connections with Other Modules

- Includes `c_cvars.h` for the console variable system.
- Includes `g_levellocals.h` and `g_game.h` for game state access.
- Includes `gstrings.h` for string handling.
- Includes `i_system.h` for system-level interfaces.
- Includes `v_font.h` for font handling.
- Includes `utf8.h` for UTF-8 text support.
- Includes `gi.h` for game information.
- Includes `i_interface.h` for interface functions.
