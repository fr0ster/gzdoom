# d_buttons.h

## File Purpose
This header file defines the button action enumeration used throughout GZDoom for handling player input. It provides a standardized set of action identifiers that are used to map physical input devices (keyboard, mouse, gamepad) to in-game actions. This abstraction layer allows for flexible input configuration and consistent handling of player actions across different parts of the codebase.

## Key Components

### Button Action Enumeration

```cpp
enum
{
    Button_AM_PanLeft,
    Button_User2,    
    Button_Jump,    
    Button_Right,    
    Button_Zoom,    
    Button_Back,    
    Button_AM_ZoomIn,
    Button_Reload,    
    Button_LookDown,
    Button_AM_ZoomOut,
    Button_User4,    
    Button_Attack,    
    Button_User1,    
    Button_Klook,    
    Button_Forward,    
    Button_MoveDown,
    Button_AltAttack,
    Button_MoveLeft,
    Button_MoveRight,
    Button_AM_PanRight,
    Button_AM_PanUp,
    Button_Mlook,    
    Button_Crouch,    
    Button_Left,    
    Button_LookUp,    
    Button_User3,    
    Button_Strafe,    
    Button_AM_PanDown,
    Button_ShowScores,
    Button_Speed,    
    Button_Use,        
    Button_MoveUp,    
    NUM_ACTIONS
};
```

This enumeration defines all the possible button actions that can be performed in the game. Each action is assigned a unique identifier that is used throughout the codebase to reference that action. The actions include:

#### Movement Actions
- `Button_Forward`: Move forward
- `Button_Back`: Move backward
- `Button_Left`: Turn left
- `Button_Right`: Turn right
- `Button_MoveLeft`: Strafe left
- `Button_MoveRight`: Strafe right
- `Button_MoveUp`: Jump or swim up
- `Button_MoveDown`: Crouch or swim down
- `Button_Strafe`: Enable strafing mode (when held, turning buttons cause strafing)
- `Button_Speed`: Run (increase movement speed)
- `Button_Jump`: Jump
- `Button_Crouch`: Crouch

#### Combat Actions
- `Button_Attack`: Primary attack
- `Button_AltAttack`: Secondary attack
- `Button_Use`: Use object or open door
- `Button_Reload`: Reload weapon

#### View Control Actions
- `Button_LookUp`: Look up
- `Button_LookDown`: Look down
- `Button_Klook`: Enable keyboard looking (when held, forward/back buttons cause looking up/down)
- `Button_Mlook`: Toggle mouse looking mode
- `Button_Zoom`: Zoom view

#### Automap Actions
- `Button_AM_PanUp`: Pan automap up
- `Button_AM_PanDown`: Pan automap down
- `Button_AM_PanLeft`: Pan automap left
- `Button_AM_PanRight`: Pan automap right
- `Button_AM_ZoomIn`: Zoom automap in
- `Button_AM_ZoomOut`: Zoom automap out

#### Interface Actions
- `Button_ShowScores`: Show scores or status screen

#### User-Definable Actions
- `Button_User1`: User-definable action 1
- `Button_User2`: User-definable action 2
- `Button_User3`: User-definable action 3
- `Button_User4`: User-definable action 4

#### Special Value
- `NUM_ACTIONS`: Total number of actions (used for array sizing and iteration)

## Implementation Details

### Button Mapping
While not shown in this header file, these button actions are typically mapped to physical inputs through a button mapping system. This system allows players to customize their controls by assigning different physical inputs (keyboard keys, mouse buttons, gamepad buttons) to these actions.

### Button State Tracking
The game tracks the state of each button action (pressed or released) and uses this information to control player movement, weapon firing, and other game actions. This state tracking is typically done through a button state array or object that is updated each frame based on input events.

### Action Priorities
Some actions may have priority over others. For example, if both `Button_Forward` and `Button_Back` are pressed simultaneously, the game may choose to prioritize one over the other or cancel out the movement entirely. These priorities are handled by the input processing code.

### User-Definable Actions
The `Button_User1` through `Button_User4` actions are typically reserved for user-definable actions that can be assigned to custom functions or scripts. This allows for additional flexibility in control customization.

## Connections with Other Modules
- Used by the input system to map physical inputs to game actions
- Connected to the player movement code for controlling player movement
- Used by the weapon system for handling weapon firing and reloading
- Interfaces with the automap system for controlling the automap view
- Connected to the user interface system for showing scores and other UI elements
- Used by the console system for binding commands to buttons
