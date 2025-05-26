# am_map.cpp

## File Purpose
This implementation file provides the core functionality for the automap system in GZDoom. It implements the abstract interface defined in `am_map.h`, handling the creation, rendering, and interaction with the in-game map display. The automap shows the player's current location and the layout of the level, with various options for customization and interaction.

## Key Components

### DAutomap Class

```cpp
class DAutomap : public DAutomapBase
{
    // ... implementation details
};
```

The concrete implementation of the `DAutomapBase` abstract class. This class provides all the functionality for the automap, including rendering, input handling, and state management.

### Automap State Variables

```cpp
// Scale and location
static double scale_mtof;
static double scale_ftom;
static DVector2 f_pos;
static DVector2 m_pos;
static int f_w, f_h;
static int lightlev;

// Map boundaries
static double mapxstart;
static double mapystart;
static double mapwidth;
static double mapheight;

// Mode and options
static bool followplayer;
static bool am_showgrid;
static bool am_showitems;
static bool am_showtime;
static bool am_showmonsters;
static bool am_showsecrets;
static bool am_showthings;
static bool am_showtriggers;
static bool am_showlocks;
static bool am_showkeys;
```

Variables that store the current state of the automap, including scale, position, boundaries, and display options. These variables control how the automap is rendered and what information is shown.

### Automap Color Sets

```cpp
struct AMColorSet
{
    // ... color definitions
};

static TArray<AMColorSet> Colorsets;
```

Structures and arrays that define the color schemes used by the automap. Different color sets can be used for different game modes or player preferences.

### Automap Markers

```cpp
struct AM_Markpoint
{
    double x, y;
    char label[16];
};

static TArray<AM_Markpoint> markpoints;
```

Structures and arrays that store the markers placed on the automap. Markers can be added by the player to highlight important locations.

### Global Functions

#### Initialization and Management

```cpp
void AM_StaticInit()
void AM_ClearColorsets()
DAutomapBase *AM_Create(FLevelLocals *Level)
void AM_Stop()
void AM_ToggleMap()
```

Functions that handle the initialization, creation, and management of the automap system. These functions are called by the game engine to control the automap display.

#### Rendering Functions

```cpp
void DAutomap::Drawer(int bottom)
void DAutomap::drawWalls()
void DAutomap::drawFlat()
void DAutomap::drawGrid()
void DAutomap::drawThings()
void DAutomap::drawMarks()
void DAutomap::drawStats()
```

Functions that handle the rendering of different elements of the automap, including walls, flats (floors and ceilings), grid lines, things (monsters, items, etc.), markers, and statistics.

#### Input Handling

```cpp
bool DAutomap::Responder(event_t *ev, bool last)
```

Handles input events for the automap, such as panning, zooming, toggling features, and adding markers. This function processes keyboard, mouse, and gamepad inputs.

#### State Management

```cpp
void DAutomap::Ticker()
void DAutomap::LevelInit()
void DAutomap::UpdateShowAllLines()
void DAutomap::ResetFollowLocation()
```

Functions that handle the updating of the automap state, including initialization for new levels, updating display options, and resetting the follow location.

## Implementation Details

### Automap Rendering
The automap rendering is handled by the `Drawer` method, which calls various helper functions to draw different elements of the map. The rendering process includes:

1. Setting up the viewport and scaling factors
2. Drawing the background
3. Drawing the grid (if enabled)
4. Drawing the walls and other level geometry
5. Drawing things (monsters, items, etc.) if enabled
6. Drawing markers placed by the player
7. Drawing statistics and other overlay information

The rendering uses a combination of 2D drawing functions to create a top-down view of the level, with different colors used to represent different types of walls, floors, and objects.

### Automap Scaling and Positioning
The automap supports zooming and panning, allowing the player to adjust the view to focus on specific areas of the map. The scaling and positioning are controlled by several variables:

- `scale_mtof`: Map to frame scale (how many pixels per map unit)
- `scale_ftom`: Frame to map scale (how many map units per pixel)
- `f_pos`: Position of the center of the automap in frame coordinates
- `m_pos`: Position of the center of the automap in map coordinates

These variables are updated based on player input and the follow mode setting.

### Automap Follow Mode
The automap can operate in "follow mode," where the map automatically centers on the player's position as they move through the level. This mode is controlled by the `followplayer` variable and can be toggled by the player. When follow mode is enabled, the `m_pos` variable is updated each tick to match the player's position.

### Automap Display Options
The automap supports various display options that can be toggled by the player:

- Grid display: Shows a grid overlay on the map
- Item display: Shows items on the map
- Monster display: Shows monsters on the map
- Secret display: Shows secret areas on the map
- Thing display: Shows all things (objects) on the map
- Trigger display: Shows trigger lines on the map
- Lock display: Shows locked doors on the map
- Key display: Shows keys on the map

These options are controlled by corresponding boolean variables and can be toggled through the input handling system.

### Automap Markers
The automap allows the player to place markers at specific locations, which can be used to mark important points in the level. Markers are stored in the `markpoints` array and are drawn on the map with a label. The player can add markers using the `addMark` method and clear all markers using the `clearMarks` method.

### Automap Color Sets
The automap uses different color sets to represent different elements of the map, such as walls, floors, things, and markers. These color sets can be customized and are stored in the `Colorsets` array. Different color sets can be used for different game modes or player preferences.

## Connections with Other Modules
- Interfaces with the level system to access level data for rendering
- Connects to the input system for handling user input
- Interfaces with the rendering system for drawing the automap
- Used by the game loop for updating and rendering the automap
- Connects to the player system for tracking the player's position
- Interfaces with the configuration system for storing and loading automap preferences
