# r_sky.cpp

## File Purpose
This implementation file provides the functionality for sky rendering in GZDoom. It handles the initialization, configuration, and animation of sky textures. The sky rendering system creates the illusion of a distant sky background in the game world, supporting features like scrolling skies, double-layered skies, and different sky rendering modes.

## Key Components

### Global Variables

```cpp
FTextureID skyflatnum;
```

- `skyflatnum`: A global variable that stores the texture ID for the sky flat. This is used to identify surfaces that should be rendered as sky.

### Console Variables

```cpp
CUSTOM_CVAR(Int, r_skymode, 2, CVAR_ARCHIVE|CVAR_NOINITCALL)
{
    R_InitSkyMap();
}
```

- `r_skymode`: A console variable that controls how the sky is rendered:
  - 0: Normal mode (unstretched and tiled)
  - 1: Stretched mode (sky texture is stretched to provide better coverage when looking up and down)
  - 2: Capped mode (default, sky texture is rendered with a cap at the top and bottom)
  
  When this variable is changed, `R_InitSkyMap()` is called to update the sky rendering.

### Functions

```cpp
void InitSkyMap(FLevelLocals *Level);
void R_InitSkyMap();
void R_UpdateSky(uint64_t mstime);
```

#### InitSkyMap
Initializes the sky mapping for a specific level. This function:
- Ensures valid sky textures are set (using a default texture if none is specified)
- Handles double-sky setup (two sky textures layered on top of each other)
- Determines the sky stretching mode based on texture height and game settings
- Sets up the sky rendering parameters for the level

#### R_InitSkyMap
A wrapper function that calls `InitSkyMap` for all active levels in the game.

#### R_UpdateSky
Updates the sky scrolling based on the current time. This function:
- Calculates the scroll position for each sky layer based on the elapsed time and scroll speed
- Updates both the software renderer values (`sky1pos`, `sky2pos`) and hardware renderer values (`hw_sky1pos`, `hw_sky2pos`, `hw_skymistpos`)
- Ensures the hardware renderer values are properly wrapped to create a seamless scrolling effect

## Implementation Details

### Sky Texture Management
The sky in GZDoom is rendered as a texture map that wraps around the player. The sky texture is typically 256 columns wide and repeats 4 times on a 320-pixel wide screen, creating a 360-degree panorama. The implementation supports:

- Single sky textures
- Double-layered skies (two textures rendered on top of each other)
- Sky mist (an additional layer that can be rendered over the sky)

### Sky Stretching Logic
The sky stretching behavior depends on the height of the sky texture:

- Height < 128: Unstretched and tiled, centered on horizon
- 128 ≤ Height < 200: Can be stretched depending on settings. When unstretched, the baseline is 28 rows below the horizon. When stretched, it is scaled to 228 pixels.
- Height == 200: Unstretched, baseline is on horizon
- Height > 200: Unstretched, but the baseline is shifted down

The actual stretching is controlled by several factors:
- The `r_skymode` CVAR setting
- The sky texture height
- Whether freelook is allowed in the current level
- Whether the level has the `LEVEL_FORCETILEDSKY` flag set

### Sky Scrolling
The sky can be animated by scrolling the texture horizontally. The scrolling speed is defined per level through the `skyspeed1`, `skyspeed2`, and `skymistspeed` variables. The `R_UpdateSky` function calculates the current position of each sky layer based on the elapsed time and these speed values.

The implementation handles both software and hardware rendering paths, with different position calculations for each:
- Software renderer: Positions are stored as fixed-point values in `sky1pos` and `sky2pos`
- Hardware renderer: Positions are stored as floating-point angles in `hw_sky1pos`, `hw_sky2pos`, and `hw_skymistpos`

## Connections with Other Modules
- Uses the texture management system (`TexMan`) to access and manipulate sky textures
- Interfaces with the level system to get level-specific sky settings and apply sky rendering parameters
- Connected to the CVAR system to allow configuration of sky rendering options
- Used by the rendering system (both software and hardware renderers) to draw the sky background
- Interacts with the freelook system to determine how to render the sky based on the player's view angle
