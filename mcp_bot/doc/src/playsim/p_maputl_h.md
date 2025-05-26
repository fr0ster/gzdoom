# p_maputl.h

## File Purpose
This header file defines utility structures and functions for map operations in GZDoom. It provides essential tools for line-of-sight calculations, collision detection, spatial partitioning, and traversal of the game world. These utilities are fundamental to many aspects of the game, including movement, combat, and AI pathfinding.

## Key Components

### Basic Structures

#### divline_t
```cpp
struct divline_t
{
    double  x;
    double  y;
    double  dx;
    double  dy;
};
```

Represents a dividing line used for various geometric calculations, particularly in line-of-sight checks and collision detection. It stores a point (x, y) and a direction vector (dx, dy).

#### intercept_t
```cpp
struct intercept_t
{
    double      frac;
    bool        isaline;
    bool        done;
    union {
        AActor *thing;
        line_t *line;
    } d;
};
```

Represents an intersection between a trace line and either a map line or an actor. Used extensively in line-of-sight and projectile trajectory calculations.

#### FLineOpening
```cpp
struct FLineOpening
{
    double          top;
    double          bottom;
    double          range;
    double          lowfloor;
    sector_t        *bottomsec;
    sector_t        *topsec;
    FTextureID      ceilingpic;
    FTextureID      floorpic;
    secplane_t      frontfloorplane;
    secplane_t      backfloorplane;
    int             floorterrain;
    bool            touchmidtex;
    bool            abovemidtex;
    uint8_t         lowfloorthroughportal;
    F3DFloor        *topffloor;
    F3DFloor        *bottomffloor;
};
```

Stores information about the vertical opening at a line, used for determining if actors can pass through or over lines.

### Geometric Utility Functions

#### P_PointOnLineSide and Variants
```cpp
int P_PointOnLineSidePrecise(double x, double y, const linebase_t *line);
int P_PointOnLineSidePrecise(const DVector2 &pt, const linebase_t *line);
int P_PointOnLineSidePrecise(const DVector3& pt, const linebase_t* line);
int P_PointOnLineSide(double x, double y, const line_t *line);
int P_PointOnLineSide(const DVector2 & p, const line_t *line);
```

Determines which side of a line a point is on. Returns 0 for front/on and 1 for back. Multiple variants are provided for different input types and precision requirements.

#### P_PointOnDivlineSide
```cpp
int P_PointOnDivlineSide(double x, double y, const divline_t *line);
int P_PointOnDivlineSide(const DVector2 &pos, const divline_t *line);
```

Similar to P_PointOnLineSide but works with divlines instead of map lines.

#### P_MakeDivline
```cpp
void P_MakeDivline(const line_t *li, divline_t *dl);
```

Converts a map line to a divline for use in geometric calculations.

#### P_LineOpening
```cpp
void P_LineOpening(FLineOpening &open, AActor *thing, const line_t *linedef, const DVector2 &xy, const DVector2 *ref = nullptr, int flags = 0);
```

Calculates the vertical opening at a line, considering floor and ceiling heights, 3D floors, and other factors.

### Portal Group Management

#### FPortalGroupArray
```cpp
struct FPortalGroupArray
{
    // ... methods and members
};
```

A specialized array for managing portal groups, with optimizations for common cases to avoid frequent heap allocations.

### Block Map Iterators

#### FBlockLinesIterator
```cpp
class FBlockLinesIterator
{
    // ... methods and members
public:
    FBlockLinesIterator(FLevelLocals *Level, int minx, int miny, int maxx, int maxy, bool keepvalidcount = false);
    FBlockLinesIterator(FLevelLocals *Level, const FBoundingBox &box);
    line_t *Next();
    void Reset();
};
```

Iterates through all lines in a rectangular region of the blockmap, used for collision detection and other spatial queries.

#### FMultiBlockLinesIterator
```cpp
class FMultiBlockLinesIterator
{
    // ... methods and members
public:
    struct CheckResult
    {
        line_t *line;
        DVector3 Position;
        int portalflags;
    };

    FMultiBlockLinesIterator(FPortalGroupArray &check, AActor *origin, double checkradius = -1);
    FMultiBlockLinesIterator(FPortalGroupArray &check, FLevelLocals *Level, double checkx, double checky, double checkz, double checkh, double checkradius, sector_t *newsec);
    bool Next(CheckResult *item);
    void Reset();
    void StopUp();
    void StopDown();
    const FBoundingBox &Box() const;
};
```

An enhanced version of FBlockLinesIterator that can traverse portals, allowing for spatial queries across connected areas of the map.

#### FBlockThingsIterator
```cpp
class FBlockThingsIterator
{
    // ... methods and members
public:
    FBlockThingsIterator(FLevelLocals *Level, int minx, int miny, int maxx, int maxy);
    FBlockThingsIterator(FLevelLocals *l, const FBoundingBox &box);
    void init(const FBoundingBox &box, bool clearhash = true);
    AActor *Next(bool centeronly = false);
    void Reset();
};
```

Iterates through all actors in a rectangular region of the blockmap, used for collision detection and other spatial queries.

#### FMultiBlockThingsIterator
```cpp
class FMultiBlockThingsIterator
{
    // ... methods and members
public:
    struct CheckResult
    {
        AActor *thing;
        DVector3 Position;
        int portalflags;
    };

    FMultiBlockThingsIterator(FPortalGroupArray &check, AActor *origin, double checkradius = -1, bool ignorerestricted = false);
    FMultiBlockThingsIterator(FPortalGroupArray &check, FLevelLocals *Level, double checkx, double checky, double checkz, double checkh, double checkradius, bool ignorerestricted, sector_t *newsec);
    bool Next(CheckResult *item);
    void Reset();
    const FBoundingBox &Box() const;
};
```

An enhanced version of FBlockThingsIterator that can traverse portals, allowing for spatial queries across connected areas of the map.

### Path Traversal

#### FPathTraverse
```cpp
class FPathTraverse
{
    // ... methods and members
public:
    intercept_t *Next();
    FPathTraverse(FLevelLocals *l, double x1, double y1, double x2, double y2, int flags, double startfrac = 0);
    void init(double x1, double y1, double x2, double y2, int flags, double startfrac = 0);
    int PortalRelocate(intercept_t *in, int flags, DVector3 *optpos = nullptr);
    void PortalRelocate(const DVector2 &disp, int flags, double hitfrac);
    virtual ~FPathTraverse();
    const divline_t &Trace() const;
    DVector2 InterceptPoint(const intercept_t *in);
};
```

Traces a line through the map, finding all intersections with lines and optionally actors. Used for line-of-sight checks, projectile trajectories, and other ray-casting operations.

### Miscellaneous Functions

```cpp
int P_AproxDistance(int dx, int dy);
double P_InterceptVector(const divline_t *v2, const divline_t *v1);
int BoxOnLineSide(const FBoundingBox& box, const line_t* ld);
```

Various utility functions for geometric calculations, including distance approximation, vector intersection, and box-line collision tests.

## Implementation Details

### Line Side Determination
The `P_PointOnLineSide` functions determine which side of a line a point is on by calculating the cross product of the line's direction vector and the vector from the line's start point to the given point. This is a fundamental operation for many geometric calculations in the game.

### Portal Traversal
The multi-block iterators (`FMultiBlockLinesIterator` and `FMultiBlockThingsIterator`) can traverse portals, allowing for spatial queries that span connected areas of the map. This is essential for proper handling of 3D environments with portals.

### Blockmap Optimization
The blockmap iterators use spatial partitioning to efficiently query only the relevant portions of the map, rather than checking every line or actor. This is a critical optimization for performance in complex maps.

### Path Traversal
The `FPathTraverse` class implements a sophisticated algorithm for tracing a line through the map, finding all intersections with lines and optionally actors. It handles portal traversal and can be used for various ray-casting operations.

### Line Opening Calculation
The `P_LineOpening` function calculates the vertical opening at a line, considering floor and ceiling heights, 3D floors, and other factors. This is used to determine if actors can pass through or over lines.

## Connections with Other Modules
- Used by the movement code for collision detection and traversal
- Used by the combat code for line-of-sight checks and projectile trajectories
- Used by the AI code for pathfinding and target acquisition
- Interfaces with the portal system for seamless traversal of connected areas
- Used by the rendering code for visibility determination
- Connects to the actor system for spatial queries involving actors
