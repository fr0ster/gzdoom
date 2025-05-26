# a_dynlight.h

## File Purpose
This header file defines the dynamic lighting system for GZDoom. It provides a comprehensive framework for creating, managing, and rendering various types of dynamic lights in the game world. The system supports different light behaviors (point, pulse, flicker, etc.), light properties (color, intensity, attenuation), and special effects (subtractive lighting, spotlights).

## Key Components

### Enumerations

#### ELightType
Defines the different types of dynamic lights:
- `PointLight`: Standard non-changing light
- `PulseLight`: Light that smoothly changes intensity over time
- `FlickerLight`: Light that randomly switches between two intensity values
- `RandomFlickerLight`: Light that randomly varies intensity within a range
- `SectorLight`: Light that derives its intensity from sector light level
- `DummyLight`: Placeholder light type
- `ColorPulseLight`, `ColorFlickerLight`, `RandomColorFlickerLight`: Color-changing variants

#### Light Component Indices
Constants for accessing light color and intensity components:
- `LIGHT_RED`, `LIGHT_GREEN`, `LIGHT_BLUE`: Color components
- `LIGHT_INTENSITY`: Primary intensity value
- `LIGHT_SECONDARY_INTENSITY`: Secondary intensity (for effects like pulsing)

#### LightFlag
Flags that control light behavior:
- `LF_SUBTRACTIVE`: Creates darkening effect instead of brightening
- `LF_ADDITIVE`: Uses additive blending
- `LF_DONTLIGHTSELF`: Doesn't illuminate its owner
- `LF_ATTENUATE`: Uses distance attenuation
- `LF_NOSHADOWMAP`: Doesn't cast shadows
- `LF_DONTLIGHTACTORS`: Doesn't illuminate actors
- `LF_SPOT`: Creates a spotlight effect
- `LF_DONTLIGHTOTHERS`: Only illuminates its owner
- `LF_DONTLIGHTMAP`: Doesn't illuminate the world

### Classes

#### FLightDefaults
Defines default properties for a type of light:
- Stores name, type, arguments, parameters, position offset
- Methods for setting various light properties
- Methods for applying properties to a dynamic light instance
- Handles serialization of light definitions

#### FLightAssociation and FInternalLightAssociation
Classes for associating lights with specific actor sprites/frames:
- `FLightAssociation`: Links actor names and frame names to light names
- `FInternalLightAssociation`: Internal representation with sprite indices

#### FLightNode
Node in a linked list structure for tracking what a light affects:
- Links lights to walls (sides) and subsectors
- Maintains bidirectional links for efficient traversal

#### FDynamicLightTouchLists
Container for tracking what surfaces a light touches:
- Maps sections and walls to their respective light-affected versions

#### FDynamicLight
The core class representing a dynamic light in the game world:
- Position and offset properties
- Color and intensity properties
- Methods for activation, deactivation, and updating
- Methods for linking/unlinking from the world
- Collision detection for determining affected surfaces
- Support for special effects like spotlights
- Serialization support

## Technical Details

### Light Positioning and Offsets
- Lights can be positioned relative to actors
- Supports portal-aware positioning with group offsets
- Handles Z-positioning to avoid clipping into floors/ceilings

### Light Behavior
- Different light types have specific update behaviors
- Pulsing lights use cyclers for smooth transitions
- Flickering lights use random number generation
- Sector lights derive intensity from sector brightness

### Light Linking
- Sophisticated system for determining what surfaces a light affects
- Uses distance checks to limit light influence
- Handles portals for cross-portal lighting
- Maintains touch lists for efficient rendering

### Spotlights
- Support for inner and outer cone angles
- Pitch control for aiming the spotlight
- Special rendering flags for spotlight effects

## Connections with Other Modules
- Integrates with the actor system through "actor.h"
- Uses cyclers from "cycler.h" for smooth light transitions
- Connects to level data through "g_levellocals.h"
- Interfaces with the rendering system for light visualization
- Interacts with the sector system for sector-based lighting
- Uses serialization for saving/loading light states
