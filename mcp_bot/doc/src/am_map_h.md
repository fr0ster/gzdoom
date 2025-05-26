# am_map.h

## File Purpose
This header file defines the interface for the automap system in GZDoom. The automap is an in-game map display that shows the player's current location and the layout of the level. This file provides the abstract base class and global functions for creating, controlling, and rendering the automap.

## Key Components

### DAutomapBase Abstract Class

```cpp
class DAutomapBase : public DObject
{
    DECLARE_ABSTRACT_CLASS(DAutomapBase, DObject);
public:
    FLevelLocals *Level;    // temporary location so that it can be set from the outside.

    // Called by main loop.
    virtual bool Responder(event_t* ev, bool last) = 0;

    // Called by main loop.
    virtual void Ticker(void) = 0;

    // Called by main loop,
    // called instead of view drawer if automap active.
    virtual void Drawer(int bottom) = 0;

    virtual void NewResolution() = 0;
    virtual void LevelInit() = 0;
    virtual void UpdateShowAllLines() = 0;
    virtual void GoBig() = 0;
    virtual void ResetFollowLocation() = 0;
    virtual int addMark() = 0;
    virtual bool clearMarks() = 0;
    virtual DVector2 GetPosition() = 0;
    virtual void startDisplay() = 0;
};
```

The abstract base class for the automap system. It inherits from `DObject` and defines the interface that any automap implementation must provide. The class includes:

- `Level`: A pointer to the current level, which provides access to level data for the automap
- `Responder`: Handles input events for the automap, such as panning, zooming, and toggling features
- `Ticker`: Updates the automap state each game tick
- `Drawer`: Renders the automap to the screen
- `NewResolution`: Handles screen resolution changes
- `LevelInit`: Initializes the automap for a new level
- `UpdateShowAllLines`: Updates the display of all lines in the level
- `GoBig`: Switches to a full-screen automap view
- `ResetFollowLocation`: Resets the follow location to the player's current position
- `addMark`: Adds a marker at the player's current position
- `clearMarks`: Clears all markers
- `GetPosition`: Gets the current position of the automap view
- `startDisplay`: Starts the automap display

### Global Functions

```cpp
void AM_StaticInit();
void AM_ClearColorsets();
DAutomapBase *AM_Create(FLevelLocals *Level);
void AM_Stop();
void AM_ToggleMap();
```

Global functions for controlling the automap:
- `AM_StaticInit`: Initializes the automap system
- `AM_ClearColorsets`: Resets the automap color sets for a game restart
- `AM_Create`: Creates an automap instance for a specific level
- `AM_Stop`: Stops the automap display
- `AM_ToggleMap`: Toggles the automap display on or off

## Implementation Details

### Automap Creation and Management
The automap system is designed to be flexible, with an abstract base class (`DAutomapBase`) that defines the interface. The actual implementation is created by the `AM_Create` function, which returns a concrete instance of `DAutomapBase` for a specific level. This allows for different automap implementations for different game modes or levels.

### Automap Display
The automap display is handled by the `Drawer` method, which is called instead of the normal view drawer when the automap is active. The automap can be displayed in different modes, such as overlay mode (where the automap is drawn on top of the game view) or full-screen mode (where the automap takes up the entire screen).

### Automap Input Handling
Input events for the automap are handled by the `Responder` method, which processes events such as panning, zooming, toggling features, and adding markers. The automap can be controlled using keyboard, mouse, or gamepad inputs.

### Automap State Updates
The automap state is updated each game tick by the `Ticker` method, which handles animations, follow mode (where the automap centers on the player), and other time-based updates.

### Automap Markers
The automap supports adding markers at specific locations, which can be used to mark important points in the level. Markers are added with the `addMark` method and can be cleared with the `clearMarks` method.

## Connections with Other Modules
- Interfaces with the level system to access level data
- Connects to the input system for handling user input
- Interfaces with the rendering system for drawing the automap
- Used by the game loop for updating and rendering the automap
- Connects to the player system for tracking the player's position
