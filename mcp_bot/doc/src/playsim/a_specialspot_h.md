# a_specialspot.h

## File Purpose
This header file defines the interface for managing special spot actors in GZDoom. Special spots are markers or points of interest in the game world that can be referenced by other game systems. Examples include brain targets in Doom II's final boss, mace spawners in Heretic, and other gameplay-specific markers. The file provides a centralized system for tracking, accessing, and managing these special spots.

## Key Components

### DSpotState Class
The main class that manages all special spots in the game:

```cpp
class DSpotState : public DObject
```

This class inherits from DObject and maintains lists of special spots organized by type. It provides methods for:
- Adding and removing spots
- Finding spots based on various criteria
- Serializing spot data for save/load

#### Key Methods

##### GetSpotState
```cpp
static DSpotState *GetSpotState(bool create = true);
```

Static method to access the global spot state:
- Returns the current spot state object
- Creates a new one if none exists and `create` is true

##### FindSpotList
```cpp
FSpotList *FindSpotList(PClassActor *type);
```

Finds or creates a list of spots for a specific actor type:
- `type`: The actor class to find spots for
- Returns a pointer to the spot list for that type

##### AddSpot
```cpp
bool AddSpot(AActor *spot);
```

Adds a spot to the appropriate list:
- `spot`: The actor to add as a spot
- Returns whether the addition was successful

##### RemoveSpot
```cpp
bool RemoveSpot(AActor *spot);
```

Removes a spot from its list:
- `spot`: The actor to remove
- Returns whether the removal was successful

##### GetNextInList
```cpp
AActor *GetNextInList(PClassActor *type, int skipcounter);
```

Gets the next spot of a specific type in sequence:
- `type`: The actor class to find spots for
- `skipcounter`: How many spots to skip before returning one
- Returns the next spot in the rotation, or NULL if none

##### GetSpotWithMinMaxDistance
```cpp
AActor *GetSpotWithMinMaxDistance(PClassActor *type, double x, double y, double mindist, double maxdist);
```

Finds a spot within a specific distance range:
- `type`: The actor class to find spots for
- `x`, `y`: The coordinates to measure distance from
- `mindist`: Minimum distance required
- `maxdist`: Maximum distance allowed (0 for unlimited)
- Returns a spot meeting the criteria, or NULL if none

##### GetRandomSpot
```cpp
AActor *GetRandomSpot(PClassActor *type, bool onlyonce = false);
```

Gets a random spot of a specific type:
- `type`: The actor class to find spots for
- `onlyonce`: If true, only returns spots on the first call
- Returns a randomly selected spot, or NULL if none

### FSpotList Structure
Internal structure used by DSpotState to organize spots by type:

```cpp
struct FSpotList;
```

This structure is forward-declared in the header and fully defined in the implementation file. It maintains:
- A list of actors of a specific type
- An index for cycling through the list
- Counters for tracking usage

## Implementation Details

The header only declares the interface for the spot system. The actual implementation in a_specialspot.cpp includes:

- The full definition of the FSpotList structure
- Implementation of all DSpotState methods
- Serialization support for saving/loading spot lists
- Random number generation for spot selection

The system is designed to be flexible, allowing different game features to use the same underlying mechanism for tracking and selecting special locations in the game world.

## Connections with Other Modules
- Includes "actor.h" for the AActor class
- Includes "tarray.h" for dynamic arrays
- Used by boss-specific code like the Doom II final boss
- Used by special weapon systems like Heretic's mace
- Connects to the serialization system for save/load support
