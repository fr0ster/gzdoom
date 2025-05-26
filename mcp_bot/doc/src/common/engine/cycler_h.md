# cycler.h

## File Purpose
This header file defines the FCycler class, which provides a flexible system for cycling values between a start and end point using various interpolation methods. It's primarily used for dynamic lights and texture shaders in GZDoom to create smooth transitions and animations.

## Key Components

### CycleType Enumeration

- **`CYCLE_Linear`**: Linear interpolation between start and end values
- **`CYCLE_Sin`**: Sinusoidal interpolation for smooth, wave-like transitions
- **`CYCLE_Cos`**: Cosine-based interpolation, similar to sine but with different phase
- **`CYCLE_SawTooth`**: Sawtooth pattern that rises linearly and then resets
- **`CYCLE_Square`**: Square wave pattern that alternates between start and end values

### FCycler Class

- **Core Methods**:
  - **`Update(double diff)`**: Updates the current value based on elapsed time
  - **`SetParams(double start, double end, double cycle, bool update)`**: Sets the cycling parameters
  - **`ShouldCycle(bool sc)`**: Enables or disables cycling
  - **`SetCycleType(CycleType ct)`**: Sets the interpolation method
  - **`GetVal()`**: Returns the current value
  - **`operator double()`**: Allows using the cycler directly as a double value

- **Member Variables**:
  - **`m_start, m_end, m_current`**: Start, end, and current values
  - **`m_time, m_cycle`**: Current time position and total cycle duration
  - **`m_increment, m_shouldCycle`**: Direction flag and cycling enable flag
  - **`m_cycleType`**: The interpolation method being used

### Serialization Support

- **`Serialize(FSerializer &arc, const char *key, FCycler &c, FCycler *def)`**: Function for serializing and deserializing FCycler objects

## Technical Details

### Cycling Mechanism

The FCycler class maintains an internal timer (`m_time`) that tracks progress through the cycle. When `Update()` is called with a time difference, it:

1. Increments the internal timer
2. Calculates a multiplier based on the timer and cycle duration
3. Uses the selected interpolation method to determine the current value
4. Handles cycle completion and direction changes

### Interpolation Methods

- **Linear**: Simple linear interpolation between start and end values
- **Sin/Cos**: Uses trigonometric functions to create smooth, periodic transitions
- **SawTooth**: Creates a pattern that rises linearly and then immediately resets
- **Square**: Alternates between start and end values with no intermediate values

### Parameter Updates

The `SetParams()` method allows updating the cycler's parameters:
- When `update` is false or the cycle duration changes, it resets the timer
- When `update` is true and the cycle duration remains the same, it scales the current value to maintain relative position

## Connections with Other Modules

- Used by dynamic light systems for smooth light intensity changes
- Utilized by texture shaders for animated effects
- Integrated with the serialization system for save/load functionality
- Employed by various visual effects that require smooth transitions

## Notable Features

- Support for multiple interpolation methods
- Seamless cycling between values
- Ability to pause/resume cycling
- Serialization support for save/load functionality
- Operator overloading for convenient usage in expressions
