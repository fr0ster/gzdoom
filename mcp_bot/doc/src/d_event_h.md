# d_event.h

## File Purpose
This header file defines the event system and game action enumeration used throughout GZDoom. It provides structures and constants for handling player input events and game state transitions. The event system is a core component that connects user input to game actions and facilitates communication between different parts of the engine.

## Key Components

### Button Code Enumeration

```cpp
typedef enum
{
    BT_ATTACK       = 1<<0,  // Press "Fire".
    BT_USE          = 1<<1,  // Use button, to open doors, activate switches.
    BT_JUMP         = 1<<2,
    BT_CROUCH       = 1<<3,
    BT_TURN180      = 1<<4,
    BT_ALTATTACK    = 1<<5,  // Press your other "Fire".
    BT_RELOAD       = 1<<6,  // [XA] Reload key. Causes state jump in A_WeaponReady.
    BT_ZOOM         = 1<<7,  // [XA] Zoom key. Ditto.

    // The rest are all ignored by the play simulation and are for scripts.
    BT_SPEED        = 1<<8,
    BT_STRAFE       = 1<<9,

    BT_MOVERIGHT    = 1<<10,
    BT_MOVELEFT     = 1<<11,
    BT_BACK         = 1<<12,
    BT_FORWARD      = 1<<13,
    BT_RIGHT        = 1<<14,
    BT_LEFT         = 1<<15,
    BT_LOOKUP       = 1<<16,
    BT_LOOKDOWN     = 1<<17,
    BT_MOVEUP       = 1<<18,
    BT_MOVEDOWN     = 1<<19,
    BT_SHOWSCORES   = 1<<20,

    BT_USER1        = 1<<21,
    BT_USER2        = 1<<22,
    BT_USER3        = 1<<23,
    BT_USER4        = 1<<24,

    BT_RUN          = 1<<25,
} buttoncode_t;
```

This enumeration defines bit flags for all the possible button actions that can be performed in the game. Each button is assigned a unique bit position, allowing multiple buttons to be combined into a single integer value. The buttons are divided into several categories:

#### Primary Action Buttons
- `BT_ATTACK`: Primary attack/fire button
- `BT_USE`: Use button for interacting with objects and switches
- `BT_JUMP`: Jump button
- `BT_CROUCH`: Crouch button
- `BT_TURN180`: Quick 180-degree turn button
- `BT_ALTATTACK`: Secondary attack/fire button
- `BT_RELOAD`: Reload weapon button
- `BT_ZOOM`: Zoom view button

#### Movement Modifier Buttons
- `BT_SPEED`: Run/walk toggle button
- `BT_STRAFE`: Strafe modifier button
- `BT_RUN`: Alternative run button

#### Movement Buttons
- `BT_MOVERIGHT`: Strafe right button
- `BT_MOVELEFT`: Strafe left button
- `BT_BACK`: Move backward button
- `BT_FORWARD`: Move forward button
- `BT_RIGHT`: Turn right button
- `BT_LEFT`: Turn left button
- `BT_LOOKUP`: Look up button
- `BT_LOOKDOWN`: Look down button
- `BT_MOVEUP`: Move up button (jump or swim up)
- `BT_MOVEDOWN`: Move down button (crouch or swim down)

#### Interface Buttons
- `BT_SHOWSCORES`: Show scores or status screen button

#### User-Definable Buttons
- `BT_USER1`: User-definable button 1
- `BT_USER2`: User-definable button 2
- `BT_USER3`: User-definable button 3
- `BT_USER4`: User-definable button 4

### Render Function

```cpp
void D_Render(std::function<void()> action, bool interpolate);
```

A function that is called by IO functions when input is detected. It takes a function object that represents the rendering action to be performed and a boolean flag indicating whether interpolation should be used.

### Game Action Enumeration

```cpp
enum gameaction_t : int
{
    ga_nothing,
    ga_loadlevel, // not used.
    ga_newgame,
    ga_newgame2,
    ga_recordgame,
    ga_loadgame,
    ga_loadgamehidecon,
    ga_loadgameplaydemo,
    ga_autoloadgame,
    ga_savegame,
    ga_autosave,
    ga_playdemo,
    ga_completed,
    ga_slideshow,
    ga_worlddone,
    ga_screenshot,
    ga_togglemap,
    ga_fullconsole,
    ga_resumeconversation,
    ga_intro,
    ga_intermission,
    ga_titleloop,
    ga_mapwarp,
};
```

This enumeration defines all the possible game actions that can be triggered. These actions represent high-level state transitions in the game, such as starting a new game, loading a saved game, or completing a level. The game action is stored in the `gameaction` global variable and is processed by the main game loop.

#### Game Flow Actions
- `ga_nothing`: No action
- `ga_newgame`: Start a new game
- `ga_newgame2`: Start a new game with additional parameters
- `ga_completed`: Level completed
- `ga_worlddone`: World/episode completed
- `ga_intro`: Show intro sequence
- `ga_intermission`: Show intermission screen
- `ga_titleloop`: Return to title screen loop

#### Save/Load Actions
- `ga_loadlevel`: Load a level (not used)
- `ga_loadgame`: Load a saved game
- `ga_loadgamehidecon`: Load a saved game and hide the console
- `ga_loadgameplaydemo`: Load a saved game and play a demo
- `ga_autoloadgame`: Automatically load a saved game
- `ga_savegame`: Save the current game
- `ga_autosave`: Automatically save the current game

#### Demo Actions
- `ga_recordgame`: Record a game demo
- `ga_playdemo`: Play a recorded demo

#### Miscellaneous Actions
- `ga_slideshow`: Show a slideshow
- `ga_screenshot`: Take a screenshot
- `ga_togglemap`: Toggle the automap
- `ga_fullconsole`: Show the full console
- `ga_resumeconversation`: Resume a conversation
- `ga_mapwarp`: Warp to a specific map

### Global Variables

```cpp
extern gameaction_t gameaction;
```

A global variable that stores the current game action. This variable is set by various parts of the code to trigger state transitions in the game.

## Implementation Details

### Button Code Design
The button codes are designed as bit flags, with each button assigned a unique bit position. This allows multiple buttons to be combined into a single integer value, which is efficient for storage and transmission. The button state is typically stored in a `ticcmd_t` structure, which is sent over the network in multiplayer games.

### Game Action Processing
The game action is processed by the main game loop, which checks the `gameaction` variable each frame and performs the appropriate action. After the action is performed, `gameaction` is set back to `ga_nothing`. This design allows for asynchronous triggering of game state transitions from various parts of the code.

### Event Handling
While not shown in this header file, the event system typically includes functions for handling various types of events, such as keyboard events, mouse events, and joystick events. These events are translated into button presses and game actions, which are then processed by the game loop.

## Connections with Other Modules
- Used by the input system to translate physical input events into game actions
- Connected to the game loop for processing game actions
- Used by the network code for transmitting player input in multiplayer games
- Interfaces with the rendering system through the `D_Render` function
- Connected to the save/load system for triggering game saves and loads
- Used by the demo system for recording and playing back player input
