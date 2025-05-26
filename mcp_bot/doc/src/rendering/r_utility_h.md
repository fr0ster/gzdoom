# r_utility.h

## File Purpose
This header file defines utility functions and structures for the rendering system in GZDoom. It provides essential components for setting up the view, handling interpolation, and managing rendering state. These utilities are used throughout the rendering code to ensure consistent behavior and to simplify complex operations.

## Key Components

### FRenderViewpoint Structure

```cpp
struct FRenderViewpoint
{
    FRenderViewpoint();

    player_t        *player;        // For which player is this viewpoint being renderered?
    DVector3        Pos;            // Camera position
    DVector3        ActorPos;       // Camera actor's position
    DRotator        Angles;         // Camera angles
    FRotator        HWAngles;       // Actual rotation angles for the hardware renderer
    DVector2        ViewVector;     // HWR only: direction the camera is facing
    DVector3        ViewVector3D;   // 3D direction the camera is facing
    DVector3        OffPos;         // Viewpoint position to use for Ortho and OoB calculations
    AActor          *ViewActor;     // either the same as camera or nullptr
    FLevelLocals    *ViewLevel;     // The level this viewpoint is on

    DVector3        Path[2];        // View path for portal calculations
    double          Cos;            // cos(Angles.Yaw)
    double          Sin;            // sin(Angles.Yaw)
    double          TanCos;         // FocalTangent * cos(Angles.Yaw)
    double          TanSin;         // FocalTangent * sin(Angles.Yaw)
    double          PitchCos;       // cos(Angles.Pitch)
    double          PitchSin;       // sin(Angles.Pitch)
    double          floordistfact;  // used for isometric sprites Y-billboarding compensation
    double          cotfloor;       // used for isometric sprites Y-billboarding compensation
    angle_t         FrustAngle;     // FrustumAngle() result

    AActor          *camera;        // camera actor
    sector_t        *sector;        // keep track of sector viewing from
    DAngle          FieldOfView;    // current field of view
    double          ScreenProj;     // Screen projection factor for orthographic projection
    double          ScreenProjX;    // Same for X-axis (screenspace)

    double          TicFrac;        // fraction of tic for interpolation
    uint32_t        FrameTime;      // current frame's time in tics
    
    int             extralight;     // extralight to be added to this viewpoint
    bool            showviewer;     // show the camera actor?
    bool            bForceNoViewer; // Never show the camera Actor

    void SetViewAngle(const FViewWindow& viewWindow);
    bool IsAllowedOoB();            // Checks if camera actor exists, has viewpos, and viewpos has VPSF_ALLOWOUTOFBOUNDS flag set
    bool IsOrtho();                 // Checks if camera actor exists, has viewpos, and viewpos has VPSF_ORTHOGRAPHIC flag set
};
```

This structure stores all the information needed to render the scene from a specific viewpoint. It includes:
- Camera position and orientation
- View angles and derived values (sine, cosine, etc.)
- Field of view and projection parameters
- References to the player, camera actor, and current sector
- Flags for controlling view behavior

### FViewWindow Structure

```cpp
struct FViewWindow
{
    double FocalTangent = 0.0;
    int centerx = 0;
    int centerxwide = 0;
    int centery = 0;
    float WidescreenRatio = 0.0f;
};
```

This structure stores information about the view window, including:
- The focal tangent (derived from the field of view)
- The center coordinates of the view window
- The widescreen ratio for aspect ratio calculations

### Global Variables

```cpp
extern FRenderViewpoint r_viewpoint;
extern FViewWindow r_viewwindow;
extern int setblocks;
extern bool r_NoInterpolate;
extern int validcount;
extern int dl_validcount;
extern angle_t LocalViewAngle;
extern int LocalViewPitch;
extern bool LocalKeyboardTurner;
extern unsigned int R_OldBlend;
```

These global variables store the current rendering state:
- `r_viewpoint`: The current viewpoint for rendering
- `r_viewwindow`: The current view window parameters
- `setblocks`: The current view size in blocks
- `r_NoInterpolate`: Flag to disable view interpolation
- `validcount`: Counter used for various rendering operations
- `dl_validcount`: Counter used for dynamic light operations
- `LocalViewAngle`: Local view angle offset
- `LocalViewPitch`: Local view pitch offset
- `LocalKeyboardTurner`: Flag indicating if the keyboard was used for turning
- `R_OldBlend`: Previous blend value for sector effects

### Point on Side Functions

```cpp
inline constexpr int R_PointOnSide(fixed_t x, fixed_t y, const node_t *node);
inline int R_PointOnSide(double x, double y, const node_t *node);
inline int R_PointOnSide(const DVector2 &pos, const node_t *node);
```

These functions determine which side of a BSP node a point is on. They are used for BSP traversal during rendering.

### View Interpolation Functions

```cpp
void R_ResetViewInterpolation();
void R_RebuildViewInterpolation(player_t *player);
bool R_GetViewInterpolationStatus();
void R_ClearInterpolationPath();
void R_AddInterpolationPoint(const DVector3a &vec);
```

These functions handle view interpolation, which smooths camera movement between frames:
- `R_ResetViewInterpolation`: Resets the view interpolation state
- `R_RebuildViewInterpolation`: Rebuilds the view interpolation for a player
- `R_GetViewInterpolationStatus`: Returns the current interpolation status
- `R_ClearInterpolationPath`: Clears the interpolation path
- `R_AddInterpolationPoint`: Adds a point to the interpolation path

### View Setup Functions

```cpp
void R_SetViewSize(int blocks);
void R_SetFOV(FRenderViewpoint &viewpoint, DAngle fov);
void R_SetupFrame(FRenderViewpoint& viewPoint, const FViewWindow& viewWindow, AActor* const camera);
void R_SetViewAngle(FRenderViewpoint &viewpoint, const FViewWindow &viewwindow);
```

These functions set up the view for rendering:
- `R_SetViewSize`: Sets the view size in blocks
- `R_SetFOV`: Sets the field of view for a viewpoint
- `R_SetupFrame`: Sets up the frame for rendering
- `R_SetViewAngle`: Sets the view angle and calculates derived values

### Initialization Functions

```cpp
void R_Init(void);
void R_ExecuteSetViewSize(FRenderViewpoint &viewpoint, FViewWindow &viewwindow);
```

These functions initialize the rendering system:
- `R_Init`: Initializes the rendering system
- `R_ExecuteSetViewSize`: Executes the view size change

### Visibility Functions

```cpp
double R_GetGlobVis(const FViewWindow &viewwindow, double vis);
double R_ClampVisibility(double vis);
```

These functions handle visibility calculations:
- `R_GetGlobVis`: Calculates the global visibility constant
- `R_ClampVisibility`: Clamps the visibility value to a valid range

### Miscellaneous Functions

```cpp
void R_FreePastViewers();
void R_ClearPastViewer(AActor *actor);
bool R_ShouldDrawSpriteShadow(AActor *thing);
```

These functions handle various rendering tasks:
- `R_FreePastViewers`: Frees the past viewer data
- `R_ClearPastViewer`: Clears the past viewer data for an actor
- `R_ShouldDrawSpriteShadow`: Determines if a sprite shadow should be drawn

## Implementation Details

### View Setup Process
The view setup process involves several steps:
1. Setting the view size based on the `setblocks` value
2. Calculating the view window parameters
3. Setting up the viewpoint with the camera position and angles
4. Calculating derived values like sine, cosine, and tangent
5. Handling view interpolation for smooth camera movement

### View Interpolation
View interpolation smooths camera movement between frames by interpolating between the previous and current camera positions and angles. This is controlled by:
- The `r_NoInterpolate` flag
- The `TicFrac` value, which represents the fraction of a tic for interpolation
- The interpolation path, which stores waypoints for complex camera movements

### BSP Traversal
The `R_PointOnSide` functions are used during BSP traversal to determine which side of a node a point is on. This is a critical part of the rendering process, as it determines which parts of the scene are visible.

### Visibility Calculation
The visibility calculation functions determine how far the player can see in the game world. This affects fog density and the distance at which objects are rendered.

## Connections with Other Modules
- Used by the rendering system to set up the view for rendering
- Connected to the player system to get player position and angles
- Interfaces with the BSP system for scene traversal
- Used by the portal system for handling view transitions
- Connected to the sector system for handling sector effects
- Interfaces with the sprite rendering system for determining sprite visibility
