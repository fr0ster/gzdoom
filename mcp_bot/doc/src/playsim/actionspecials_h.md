# actionspecials.h

## File Purpose
This header file defines all the line action specials available in GZDoom. Line specials are numeric codes that determine what happens when a line in the map is activated, such as opening doors, moving floors, triggering effects, etc. This file serves as a comprehensive registry of all supported specials, their numeric identifiers, and their parameter requirements.

## Key Components

### DEFINE_SPECIAL Macro
The file consists entirely of `DEFINE_SPECIAL` macro invocations, each defining a single line special with the following format:

```cpp
DEFINE_SPECIAL(name, number, min_script_args, max_script_args, num_args_on_line)
```

Parameters:
- `name`: The name of the special (used in code and scripts)
- `number`: The numeric identifier for the special
- `min_script_args`: Minimum number of arguments when called from scripts (-1 for special cases)
- `max_script_args`: Maximum number of arguments when called from scripts (-1 for special cases)
- `num_args_on_line`: Number of arguments when used as a line special in a map

### Special Categories

The file organizes specials into several functional categories:

#### Polyobject Specials (1-8, 59, 86-93, 283)
Specials for manipulating polyobjects (movable wall segments):
- Rotation (left/right)
- Movement (normal/times8)
- Door behaviors (swing/slide)
- Starting lines and explicit lines

#### Door Specials (10-14, 105-106, 249, 274)
Specials for door operations:
- Opening, closing, and raising doors
- Locked doors
- Animated doors
- Wait-then-action doors

#### Floor Specials (20-28, 35-37, 46, 66-68, etc.)
Specials for floor manipulation:
- Raising and lowering floors
- Moving floors to specific heights
- Crushing floors
- Instant movement
- Donut effects (floor lowers, then outer portion raises)

#### Ceiling Specials (40-47, 69, 97, 104, etc.)
Specials for ceiling manipulation:
- Raising and lowering ceilings
- Crushing ceilings
- Moving ceilings to specific heights
- Instant movement

#### Platform Specials (60-65, 206-207, 228, 230-231)
Specials for platform (moving floor) behaviors:
- Perpetual raising
- Down-wait-up-stay
- Up-wait-down-stay
- Up/down by value

#### Stair Building Specials (26-27, 31-32, 217, 270-273)
Specials for creating staircase effects:
- Building up and down
- Synchronized building
- Doom-style stairs
- Crushing stairs

#### Teleportation Specials (70-71, 74-78, 154, 215)
Specials for teleportation effects:
- Standard teleportation
- Silent teleportation (no fog)
- Map changing teleports
- Group teleportation
- Teleporting other actors

#### Thing Manipulation Specials (17-19, 72-73, 119, 125, 130-139, etc.)
Specials for manipulating actors ("things"):
- Activating and deactivating
- Damaging and destroying
- Moving and thrusting
- Spawning (with and without fog)
- Changing properties

#### Light Specials (109-117, 232-234)
Specials for light manipulation:
- Changing light levels
- Light fading
- Glowing lights
- Flickering and strobing lights

#### ACS Script Specials (80-85, 226)
Specials for controlling ACS scripts:
- Executing scripts
- Suspending and terminating scripts
- Locked execution
- Always execute

#### Sector Effect Specials (9, 33-34, 48-51, 54, 57-58, etc.)
Specials for sector effects:
- Horizon lines
- Force fields
- Sector linking
- Portals
- Changing sector flags and properties

#### Scroll Specials (52-53, 100-103, 221-225)
Specials for scrolling textures and surfaces:
- Wall scrolling
- Texture scrolling (in all directions)
- Floor and ceiling scrolling
- Model-based scrolling

#### Generic Specials (169, 200-205, 284)
Flexible specials that can be configured for various effects:
- Generic floor movement
- Generic ceiling movement
- Generic doors
- Generic lifts
- Generic stairs
- Generic crushers

#### Miscellaneous Specials
Various other specials for specific effects:
- Earthquake effects (120)
- Wind and current effects (218, 220)
- Camera changes (237)
- Exit specials (243-244)
- Healing (248)
- And many more specialized functions

## Implementation Details

The file only contains the definitions of the specials, not their implementations. The actual code that executes when these specials are triggered is located elsewhere in the engine.

The `-1` values for min/max script arguments indicate special cases where the argument handling is more complex and handled separately in the implementation.

Many specials have both a basic version and enhanced versions with additional features (e.g., Floor_RaiseByValue and Floor_RaiseByValueTimes8).

## Connections with Other Modules
- Used by the map loader to interpret line special numbers in maps
- Connected to the ACS scripting system for script-triggered specials
- Interfaces with the play simulation system for executing the special effects
- Links to the polyobject system for manipulating polyobjects
- Connects to the sector movement system for floor/ceiling/platform movement
- Interfaces with the lighting system for light effects
- Used by the teleportation system for teleport specials
