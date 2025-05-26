# r_state.h

## File Purpose
This header file defines the global rendering state variables used throughout the GZDoom rendering system. It contains declarations for key data structures and variables that maintain the state of the rendering engine, including view parameters and sprite lookup tables. These variables are essential for the rendering process as they define the current view properties and provide access to sprite definitions.

## Key Components

### View Window Parameters

- **`viewwindowx`**: The x-coordinate of the top-left corner of the view window within the screen.
- **`viewwindowy`**: The y-coordinate of the top-left corner of the view window within the screen.
- **`viewwidth`**: The width of the view window in pixels.
- **`viewheight`**: The height of the view window in pixels.

These variables define the dimensions and position of the game's view window on the screen. They are used throughout the rendering code to determine where and how to render the game world.

### Sprite System

- **`sprites`**: A dynamic array containing all sprite definitions (`spritedef_t`) used in the game.
- **`NumStdSprites`**: The number of standard sprites in the game, excluding any custom sprites added by mods.

These variables provide access to the sprite definitions used for rendering actors and objects in the game world. The `sprites` array contains all the information needed to render each sprite, including frame data and rotation information.

### Player Skin System

- **`R_FindSkin`**: A function that finds a player skin by name and player class.

This function is used to look up player skins, which are used to customize the appearance of players in the game.

## Technical Details

### View Window Coordinates

The view window parameters (`viewwindowx`, `viewwindowy`, `viewwidth`, `viewheight`) define the portion of the screen where the 3D world is rendered. This may be smaller than the full screen to accommodate the status bar, menu elements, or other UI components. These coordinates are used by the rendering system to properly clip and scale the rendered scene.

### Sprite Management

The sprite system in GZDoom uses the `sprites` array to store all sprite definitions. Each entry in this array corresponds to a specific sprite and contains information about:

- The number of frames the sprite has
- The rotations available for each frame
- The textures used for each frame and rotation

The `NumStdSprites` variable indicates how many sprites are part of the base game, which is useful for distinguishing between standard sprites and those added by mods or extensions.

## Connections with Other Modules

- Interfaces with the rendering system (`r_draw.cpp`, `r_things.cpp`, etc.) to provide essential state information.
- Connected to the actor system, which references sprites for visual representation.
- Used by the skin system to handle player appearance customization.
- Linked to the resource management system that loads sprite graphics.

## Notable Features

- Centralized storage of rendering state variables for easy access across the codebase.
- Support for dynamic sprite arrays that can be extended by mods.
- Integration with the player skin system for customizable player appearances.
- Minimal design that focuses on essential rendering state variables.
