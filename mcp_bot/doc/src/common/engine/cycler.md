# cycler.cpp

## File Purpose
This source file implements the FCycler class defined in cycler.h. It provides the functionality for cycling values between a start and end point using various interpolation methods. The cycler system is primarily used for dynamic lights and texture shaders in GZDoom to create smooth transitions and animations.

## Key Components

### Serialization Function

- **`Serialize(FSerializer &arc, const char *key, FCycler &c, FCycler *def)`**: Implements serialization and deserialization for FCycler objects, allowing them to be saved and loaded with game states.

### FCycler Methods

- **`SetParams(double start, double end, double cycle, bool update)`**: Implements the parameter setting functionality, handling both fresh initialization and updates to existing cyclers.
- **`Update(double diff)`**: Implements the core cycling logic, updating the current value based on elapsed time and the selected interpolation method.

## Technical Details

### Serialization Implementation

The serialization function:
- Uses the `BeginObject` and `EndObject` methods of the serializer to create a structured representation
- Serializes all member variables of the FCycler class
- Uses the provided default values when deserializing
- Handles the enumeration type properly with the `.Enum()` method

### SetParams Implementation

This method handles two scenarios:
1. **Fresh initialization or cycle duration change**:
   - Resets the timer to zero
   - Sets the increment flag to true (starting direction)
   - Sets the current value to the start value

2. **Parameter update with same cycle duration**:
   - Calculates the current position as a factor between start and end
   - Scales this factor to the new range to maintain relative position
   - Updates the start and end values

### Update Implementation

This method implements the different interpolation types:
1. **Linear**: 
   - In increment mode: interpolates from start to end
   - In decrement mode: interpolates from end to start

2. **Sin/Cos**:
   - Converts the time position to an angle (0 to 2π)
   - Applies the sine or cosine function
   - Normalizes the result to the 0-1 range
   - Scales to the start-end range

3. **SawTooth**:
   - Simple linear interpolation from start to end
   - Resets to start when the cycle completes

4. **Square**:
   - Uses the increment flag to determine whether to use start or end value
   - No intermediate values are used

The method also handles cycle completion:
- Resets the timer when it reaches the cycle duration
- Toggles the increment flag to reverse direction

## Connections with Other Modules

- Integrates with the serialization system through the `serializer.h` header
- Used by dynamic light systems for smooth intensity transitions
- Utilized by texture shaders for animated effects
- Employed by various visual effects that require smooth value cycling

## Notable Features

- Efficient implementation of multiple interpolation methods
- Smooth transitions between values with configurable patterns
- Support for maintaining relative position when updating parameters
- Complete serialization support for save/load functionality
- Direction toggling for ping-pong style animations
