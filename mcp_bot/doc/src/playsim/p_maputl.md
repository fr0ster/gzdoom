# p_maputl.cpp

## File Purpose
This implementation file provides the core functionality for map utility operations in GZDoom. It implements the structures and functions declared in `p_maputl.h`, handling line-of-sight calculations, collision detection, spatial partitioning, and traversal of the game world. These utilities are fundamental to many aspects of the game, including movement, combat, and AI pathfinding.

## Key Components

### Geometric Utility Functions

#### P_PointOnLineSide and Variants
```cpp
int P_VanillaPointOnLineSide(double x, double y, const line_t* line)
```

Implements the original Doom algorithm for determining which side of a line a point is on, used for compatibility with vanilla Doom behavior. This function is called by `P_PointOnLineSide` when the line has the `ML_COMPATSIDE` flag set.

#### P_InterceptVector
```cpp
double P_InterceptVector(const divline_t *v2, const divline_t *v1)
```

Calculates the intersection point of two divlines, returning the fractional distance along the first divline where the intersection occurs. This is used extensively in line-of-sight and projectile trajectory calculations.

#### P_AproxDistance
```cpp
int P_AproxDistance(int dx, int dy)
```

Provides a fast approximation of the distance between two points using the Manhattan distance plus a correction factor. This is used for performance-critical distance calculations where exact precision is not required.

#### BoxOnLineSide
```cpp
int BoxOnLineSide(const FBoundingBox& box, const line_t* ld)
```

Determines which side of a line a bounding box is on, or if it crosses the line. Returns -1 if the box is entirely on the front side, 1 if it's entirely on the back side, and 0 if it crosses the line.

### Line Opening Calculation

#### P_LineOpening
```cpp
void P_LineOpening(FLineOpening &open, AActor *thing, const line_t *linedef, const DVector2 &xy, const DVector2 *ref, int flags)
```

Calculates the vertical opening at a line, considering floor and ceiling heights, 3D floors, and other factors. This is used to determine if actors can pass through or over lines. The implementation handles various special cases, including:
- One-sided lines (which are always impassable)
- Two-sided lines with different floor and ceiling heights
- Lines with 3D floors
- Lines with portals
- Middle textures that can block movement

### Block Map Iterators

#### FBlockLinesIterator
```cpp
FBlockLinesIterator::FBlockLinesIterator(FLevelLocals *Level, int minx, int miny, int maxx, int maxy, bool keepvalidcount)
line_t *FBlockLinesIterator::Next()
```

Implements an iterator for lines in a rectangular region of the blockmap. The constructor sets up the iterator with the specified bounds, and `Next()` returns the next line in the region, or `nullptr` when all lines have been processed.

#### FMultiBlockLinesIterator
```cpp
FMultiBlockLinesIterator::FMultiBlockLinesIterator(FPortalGroupArray &check, AActor *origin, double checkradius)
bool FMultiBlockLinesIterator::Next(CheckResult *item)
```

Implements an enhanced iterator that can traverse portals, allowing for spatial queries across connected areas of the map. The constructor sets up the iterator with the specified origin and radius, and `Next()` returns the next line in the region, potentially across portals.

#### FBlockThingsIterator
```cpp
FBlockThingsIterator::FBlockThingsIterator(FLevelLocals *Level, int minx, int miny, int maxx, int maxy)
AActor *FBlockThingsIterator::Next(bool centeronly)
```

Implements an iterator for actors in a rectangular region of the blockmap. The constructor sets up the iterator with the specified bounds, and `Next()` returns the next actor in the region, or `nullptr` when all actors have been processed.

#### FMultiBlockThingsIterator
```cpp
FMultiBlockThingsIterator::FMultiBlockThingsIterator(FPortalGroupArray &check, AActor *origin, double checkradius, bool ignorerestricted)
bool FMultiBlockThingsIterator::Next(CheckResult *item)
```

Implements an enhanced iterator that can traverse portals, allowing for spatial queries across connected areas of the map. The constructor sets up the iterator with the specified origin and radius, and `Next()` returns the next actor in the region, potentially across portals.

### Path Traversal

#### FPathTraverse
```cpp
FPathTraverse::FPathTraverse(FLevelLocals *l, double x1, double y1, double x2, double y2, int flags, double startfrac)
intercept_t *FPathTraverse::Next()
```

Implements a sophisticated algorithm for tracing a line through the map, finding all intersections with lines and optionally actors. The constructor sets up the trace with the specified start and end points, and `Next()` returns the next intersection along the trace, or `nullptr` when all intersections have been processed.

#### AddLineIntercepts
```cpp
void FPathTraverse::AddLineIntercepts(int bx, int by)
```

Adds all line intercepts in a specific blockmap cell to the intercepts list. This is called by `FPathTraverse::init()` for each blockmap cell that the trace line passes through.

#### AddThingIntercepts
```cpp
void FPathTraverse::AddThingIntercepts(int bx, int by, FBlockThingsIterator &it, bool compatible)
```

Adds all thing intercepts in a specific blockmap cell to the intercepts list. This is called by `FPathTraverse::init()` for each blockmap cell that the trace line passes through, if the `PT_ADDTHINGS` flag is set.

#### PortalRelocate
```cpp
int FPathTraverse::PortalRelocate(intercept_t *in, int flags, DVector3 *optpos)
void FPathTraverse::PortalRelocate(const DVector2 &disp, int flags, double hitfrac)
```

Handles the relocation of the trace line when it passes through a portal. This is essential for proper handling of 3D environments with portals.

### Portal Group Management

#### FPortalGroupArray
```cpp
void FPortalGroupArray::Clear()
void FPortalGroupArray::Add(uint32_t num)
```

Implements a specialized array for managing portal groups, with optimizations for common cases to avoid frequent heap allocations. The `Clear()` method resets the array, and `Add()` adds a new portal group to the array.

## Implementation Details

### Line Side Determination
The implementation of `P_PointOnLineSide` and its variants uses the cross product of the line's direction vector and the vector from the line's start point to the given point. This is a fundamental operation for many geometric calculations in the game. The implementation includes both the precise version and the vanilla Doom version for compatibility.

### Portal Traversal
The multi-block iterators (`FMultiBlockLinesIterator` and `FMultiBlockThingsIterator`) implement portal traversal by maintaining a list of portal groups and iterating through them. When a portal is encountered, the iterator adds the connected portal group to its list and continues the iteration in that group.

### Blockmap Optimization
The blockmap iterators use the game's blockmap data structure to efficiently query only the relevant portions of the map, rather than checking every line or actor. The implementation includes optimizations such as:
- Skipping empty blockmap cells
- Using a hash table to avoid processing the same line or actor multiple times
- Maintaining a validcount to avoid redundant checks

### Path Traversal
The `FPathTraverse` class implements a sophisticated algorithm for tracing a line through the map:
1. It converts the trace line to a divline
2. It determines which blockmap cells the line passes through
3. For each cell, it adds all line intercepts (and optionally thing intercepts) to a list
4. It sorts the intercepts by distance along the trace line
5. It returns the intercepts one by one, in order of increasing distance

The implementation handles special cases such as:
- Lines that are parallel to the trace line
- Lines that are coincident with the trace line
- Portals that the trace line passes through

### Line Opening Calculation
The `P_LineOpening` function calculates the vertical opening at a line by:
1. Determining the floor and ceiling heights on both sides of the line
2. Considering any 3D floors that might affect the opening
3. Checking for middle textures that might block the opening
4. Handling special cases such as portals and self-referencing sectors

The implementation is complex due to the many factors that can affect the opening, but it's essential for determining if actors can pass through or over lines.

## Connections with Other Modules
- Used by the movement code for collision detection and traversal
- Used by the combat code for line-of-sight checks and projectile trajectories
- Used by the AI code for pathfinding and target acquisition
- Interfaces with the portal system for seamless traversal of connected areas
- Used by the rendering code for visibility determination
- Connects to the actor system for spatial queries involving actors
