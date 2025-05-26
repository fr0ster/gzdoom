# wi_stuff.cpp

## File Purpose
This source file implements the intermission screens in GZDoom. Intermission screens appear between levels, showing the player's statistics for the completed level and information about the upcoming level. The file provides a flexible system for creating and customizing intermission screens, supporting both traditional Doom-style intermissions and more advanced scripted intermissions with animations and conditional elements.

## Key Components

### DInterBackground Class

- **Core intermission background class** that handles loading, rendering, and animating intermission screens.
- Supports multiple types of intermission backgrounds:
  - Simple static textures
  - Tiled backgrounds
  - Scripted backgrounds with animations and conditional elements
  - JSON-based animation sequences

### Background Loading and Rendering

- **`LoadBackground`**: Loads an intermission background from a texture or script.
  - Handles different game types (Doom, Heretic, Hexen, Strife, etc.)
  - Supports both entering and exiting intermission screens
  - Processes script commands for animations and map spots

- **`drawBackground`**: Renders the intermission background with all its elements.
  - Draws the base background (tiled or scaled)
  - Renders animations based on their conditions
  - Draws "splats" on visited map locations
  - Shows "You are here" pointers for the next level

### Animation System

- **`updateAnimatedBack`**: Updates all animations on the intermission screen.
  - Handles different animation types (always, frame-based, pic)
  - Processes animation timing and frame advancement
  - Supports conditional animations based on game state

### Intermission Scripting

- Support for script-based intermission screens with commands like:
  - `Background`: Sets the background texture
  - `Splat`: Defines the "visited location" marker
  - `Pointer`: Sets the "You are here" pointer
  - `Spots`: Defines map locations
  - `Animation`: Creates animated elements
  - Various conditional commands (`IfEntering`, `IfLeaving`, etc.)

### JSON Animation Support

- Support for modern JSON-based animation definitions with features like:
  - Multiple animation layers
  - Complex frame sequences with variable durations
  - Conditional display based on game state
  - Custom music for intermissions

### Intermission Initialization

- **`WI_Start`**: Creates and initializes the appropriate intermission screen.
  - Selects the correct screen class based on game mode
  - Handles single-player, cooperative, and deathmatch screens
  - Sets up scaling and layout parameters

## Technical Details

### Animation Types

- **Always**: Continuously looping animations
- **Pic**: Static images
- **Frame**: Frame-based animations with configurable timing
- **None**: Frozen frames (for infinite duration)

### Conditional Display

- Animations and layers can be conditionally displayed based on:
  - Whether the player is entering or leaving a level
  - Whether specific levels have been visited
  - The current level number
  - Whether the level is a secret level
  - Whether the player is traveling between specific levels

### Background Handling

- Backgrounds can be:
  - Scaled to fit the screen (for large textures)
  - Tiled across the screen (for small textures)
  - Automatically selected based on game type and level

### Coordinate System

- The intermission screen uses a virtual coordinate system (typically 320x200)
- Animations and elements are positioned within this coordinate space
- The system automatically scales to fit different screen resolutions

## Connections with Other Modules

- Interfaces with the texture system for loading graphics
- Connected to the music system for intermission music
- Uses the file system for loading scripts and JSON definitions
- Interacts with the game state system to get level information
- Connected to the rendering system for drawing the intermission screen
- Uses the serialization system for JSON parsing

## Notable Features

- Support for classic Doom-style intermission screens
- Flexible scripting system for custom intermissions
- Modern JSON-based animation definitions
- Conditional elements based on game state
- Support for different game types (Doom, Heretic, Hexen, Strife)
- Automatic selection of appropriate intermission screens
- Support for custom music during intermissions
