# r_sky.h

## File Purpose
This header file defines the interface for sky rendering in GZDoom. It provides the necessary declarations for handling sky textures, including initialization, updating, and accessing sky-related data. The sky rendering system is responsible for creating the illusion of a distant sky background in the game world.

## Key Components

### Constants and Variables

```cpp
extern FTextureID skyflatnum;
extern int freelookviewheight;
#define SKYSTRETCH_HEIGHT 228
```

- `skyflatnum`: A global variable that stores the texture ID for the sky flat. This is used to identify surfaces that should be rendered as sky.
- `freelookviewheight`: A global variable that stores the view height for freelook (looking up and down).
- `SKYSTRETCH_HEIGHT`: A constant that defines the height to which sky textures are stretched when the sky stretching mode is enabled.

### Functions

```cpp
void InitSkyMap(FLevelLocals *Level);
void R_InitSkyMap();
void R_UpdateSky(uint64_t mstime);
```

- `InitSkyMap`: Initializes the sky mapping for a specific level. This function is called whenever the sky changes or the view size changes.
- `R_InitSkyMap`: Initializes the sky mapping for all levels. This is a wrapper function that calls `InitSkyMap` for each level.
- `R_UpdateSky`: Updates the sky scrolling based on the current time. This function is called regularly to animate the sky.

## Implementation Details

### Sky Texture Management
The sky in GZDoom is rendered as a texture map that wraps around the player. The sky texture is typically 256 columns wide and repeats 4 times on a 320-pixel wide screen, creating a 360-degree panorama. The sky can be a single texture or a double sky (two textures layered on top of each other).

### Sky Stretching
GZDoom supports different modes for rendering the sky:
- Normal mode: The sky texture is rendered unstretched and tiled.
- Stretched mode: The sky texture is stretched to a height of 228 pixels to provide better coverage when looking up and down.
- Capped mode: The sky texture is rendered with a cap at the top and bottom.

The sky stretching behavior is controlled by the `r_skymode` CVAR:
- 0: Normal mode
- 1: Stretched mode
- 2: Capped mode

### Sky Scrolling
The sky can be animated by scrolling the texture horizontally. This creates the illusion of clouds or other sky elements moving over time. The scrolling speed is defined per level and is applied in the `R_UpdateSky` function.

## Connections with Other Modules
- Used by the rendering system to draw the sky background
- Interfaces with the texture management system to access sky textures
- Connected to the level system to get level-specific sky settings
- Used by the view rendering code to determine how to render the sky based on the player's view angle
- Interfaces with the CVAR system to allow configuration of sky rendering options
