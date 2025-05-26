# a_flashfader.cpp

## File Purpose
This file implements the screen blending (fading) effects in GZDoom. It provides functionality for creating smooth transitions between different screen colors and opacities, which are used for various visual effects like damage feedback, power-ups, environmental effects, and transitions.

## Key Components

### DFlashFader Class
The main class that handles screen fading effects:

```cpp
class DFlashFader : public DThinker
```

This class inherits from DThinker to receive regular tick updates and manages the following:
- Starting and ending blend colors (RGBA values)
- Transition duration
- Target player/actor
- Termination behavior

### Key Methods

#### Construct
```cpp
void DFlashFader::Construct(float r1, float g1, float b1, float a1,
                           float r2, float g2, float b2, float a2,
                           float time, AActor *who, bool terminate)
```
Initializes a new flash fader with:
- Starting color/alpha (r1, g1, b1, a1)
- Ending color/alpha (r2, g2, b2, a2)
- Duration in seconds (converted to tics)
- Target actor (typically a player)
- Termination flag

#### OnDestroy
```cpp
void DFlashFader::OnDestroy()
```
Handles cleanup when the fader is destroyed:
- If terminate flag is set, clears the secondary fade
- Sets the final blend state
- Calls parent destructor

#### Tick
```cpp
void DFlashFader::Tick()
```
Called every game tick to update the fade effect:
- Decrements remaining time
- Updates the blend values based on progress
- Destroys itself when complete or if target is invalid

#### SetBlend
```cpp
void DFlashFader::SetBlend(float time)
```
Sets the current blend values based on interpolation:
- Takes a time parameter (0.0 to 1.0) representing progress
- Linearly interpolates between start and end colors
- Updates the player's blend values directly

#### Cancel
```cpp
void DFlashFader::Cancel()
```
Immediately cancels the fade effect:
- Sets remaining time to zero
- Clears the target alpha to ensure no lingering effect

### Serialization Support
The class implements serialization methods to save/load fade states:
```cpp
void DFlashFader::Serialize(FSerializer &arc)
```

## Implementation Details

### Blend Calculation
- Uses linear interpolation between start and end colors
- Calculates current blend as: `start_value * (1-time) + end_value * time`
- Time progresses from 0.0 (start) to 1.0 (end)

### Timing System
- Duration is stored in tics (game frames)
- Converts seconds to tics using the TICRATE constant
- Counts down RemainingTics each frame

### Player Integration
- Directly modifies player's BlendR, BlendG, BlendB, and BlendA values
- These values are used by the rendering system for screen effects
- Checks for valid player pointer before applying effects

### Termination Behavior
- Can optionally clear the blend effect when destroyed
- Useful for effects that should be cleanly removed rather than lingering

## Connections with Other Modules
- Integrates with the player system through "d_player.h"
- Uses the thinker system for regular updates
- Connects to the serialization system for save/load support
- Indirectly connects to the rendering system through player blend values
