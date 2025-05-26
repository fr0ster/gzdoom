# g_cvars.h

## File Purpose
This header file declares external console variables (CVars) used throughout the GZDoom engine. It serves as a central declaration point for game-related configuration variables that control various aspects of the engine's behavior, particularly related to rendering and lighting.

## Key Components

### Lighting-Related CVars

- **`r_dynlights`**: Boolean CVar that controls whether dynamic lights are enabled in the game.
- **`gl_lights`**: Boolean CVar that controls whether OpenGL lighting is enabled.

## Technical Details

- Uses the `EXTERN_CVAR` macro to declare external references to console variables defined elsewhere.
- Includes `c_cvars.h` to access the console variable system.
- Uses `#pragma once` directive to prevent multiple inclusions of the header.

## Connections with Other Modules

- Connects to the console variable system through `c_cvars.h`.
- Referenced by modules that need access to these specific CVars.
- Part of a larger effort to centralize CVar declarations that were previously scattered throughout the codebase.
