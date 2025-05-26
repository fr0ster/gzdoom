# a_corona.h

## File Purpose
This header file defines the interface for light coronas in GZDoom. Light coronas are visual effects that appear around light sources, creating a glow or halo effect. The file is currently mostly commented out, suggesting that this functionality might be in development or temporarily disabled.

## Key Components

### External CVAR
- **gl_coronas**: Boolean CVAR that controls whether light coronas are enabled or disabled in the game.

### ACorona Class (Commented Out)
A class that would represent a corona actor in the game. Although currently commented out (#if 0), it shows the intended structure:

- Inherits from AActor
- Contains a Tick() method for updating the corona
- Has a CoronaFade property to control the corona's opacity/visibility

## Usage
This header is intended to be included by source files that need to work with light corona effects. The commented-out nature of the main class suggests that the corona system might be:

1. Under development
2. Temporarily disabled
3. Preserved for future implementation

When implemented, the ACorona class would likely be used to create visual corona effects around light sources like lamps, fire, or other glowing objects in the game world.

## Connections with Other Modules
- Includes "actor.h" for the AActor base class
- Would interact with the rendering system to display corona effects
- Uses the CVAR system to allow enabling/disabling of the feature
- Would likely connect with the dynamic lighting system (a_dynlight.cpp/h)
