# r_utility.cpp

## File Purpose
This implementation file provides the core utility functions for the rendering system in GZDoom. It handles view setup, interpolation, and various rendering-related calculations. These utilities form the foundation of the rendering pipeline, ensuring that the game world is properly displayed from the player's perspective with smooth camera movement and correct visual effects.

## Key Components

### Structures and Classes

#### InterpolationViewer
```cpp
struct InterpolationViewer
{
    struct instance
    {
        DVector3 Pos, ViewPos;
        DRotator Angles;
        DRotator ViewAngles;
    };

    AActor* ViewActor;
    DVector3 ViewOffset, RelativeViewOffset;
    DRotator AngleOffsets;
    int prevTic;
    instance Old, New;
};
```

This structure stores the data needed for view interpolation:
- `instance`: A nested structure that stores position and angle data for a specific point in time
- `ViewActor`: The actor being viewed
- `ViewOffset` and `RelativeViewOffset`: Offsets applied to the view position
- `AngleOffsets`: Offsets applied to the view angles
- `prevTic`: The previous game tic
- `Old` and `New`: Instances representing the previous and current states for interpolation

### Global Variables

```cpp
static TArray<InterpolationViewer> PastViewers;
static FCRandom pr_torchflicker ("TorchFlicker");
static FCRandom pr_hom;
bool NoInterpolateView;
static TArray<DVector3a> InterpolationPath;

FRenderViewpoint r_viewpoint;
FViewWindow r_viewwindow;
int viewwindowx;
int viewwindowy;
int viewwidth;
int viewheight;
int freelookviewheight;
int setblocks;
bool r_NoInterpolate;
int validcount = 1;
int dl_validcount = 1;
angle_t LocalViewAngle;
int LocalViewPitch;
bool LocalKeyboardTurner;
unsigned int R_OldBlend = ~0;
```

These global variables store the state of the rendering system:
- `PastViewers`: Array of past viewer states for interpolation
- `pr_torchflicker` and `pr_hom`: Random number generators for visual effects
- `NoInterpolateView`: Flag to disable view interpolation
- `InterpolationPath`: Path of points for complex camera movements
- `r_viewpoint`: The current viewpoint for rendering
- `r_viewwindow`: The current view window parameters
- `viewwindowx`, `viewwindowy`, `viewwidth`, `viewheight`: View window dimensions
- `freelookviewheight`: View height for freelook
- `setblocks`: Current view size in blocks
- `r_NoInterpolate`: Flag to disable interpolation
- `validcount` and `dl_validcount`: Counters for rendering operations
- `LocalViewAngle` and `LocalViewPitch`: Local view angle and pitch offsets
- `LocalKeyboardTurner`: Flag indicating if the keyboard was used for turning
- `R_OldBlend`: Previous blend value for sector effects

### Console Variables

```cpp
CVAR (Bool, r_deathcamera, false, CVAR_ARCHIVE)
CVAR (Int, r_clearbuffer, 0, 0)
CVAR (Bool, r_drawvoxels, true, 0)
CVAR (Bool, r_drawplayersprites, true, 0)
CVARD (Bool, r_radarclipper, false, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_CHEAT, "Use the horizontal clipper from camera->tracer's perspective")
CVARD (Bool, r_dithertransparency, false, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_CHEAT, "Use dithered-transparency shading for actor-occluding level geometry")
CUSTOM_CVAR(Float, r_quakeintensity, 1.0f, CVAR_ARCHIVE | CVAR_GLOBALCONFIG)
CUSTOM_CVARD(Int, r_actorspriteshadow, 1, CVAR_ARCHIVE | CVAR_GLOBALCONFIG, "render actor sprite shadows. 0 = off, 1 = default, 2 = always on")
CUSTOM_CVARD(Float, r_actorspriteshadowdist, 1500.0, CVAR_ARCHIVE | CVAR_GLOBALCONFIG, "how far sprite shadows should be rendered")
CUSTOM_CVARD(Float, r_actorspriteshadowalpha, 0.5, CVAR_ARCHIVE | CVAR_GLOBALCONFIG, "maximum sprite shadow opacity, only effective with hardware renderers")
CUSTOM_CVARD(Float, r_actorspriteshadowfadeheight, 0.0, CVAR_ARCHIVE | CVAR_GLOBALCONFIG, "distance over which sprite shadows should fade")
CUSTOM_CVAR (Int, screenblocks, 10, CVAR_ARCHIVE)
CUSTOM_CVAR(Float, r_visibility, 8.0f, CVAR_NOINITCALL)
CUSTOM_CVAR (Int, r_skymode, 2, CVAR_ARCHIVE|CVAR_NOINITCALL)
CUSTOM_CVAR(Float, maxviewpitch, 90.f, CVAR_ARCHIVE | CVAR_SERVERINFO)
```

These console variables control various aspects of the rendering system:
- `r_deathcamera`: Enables the death camera view
- `r_clearbuffer`: Controls buffer clearing behavior
- `r_drawvoxels`: Enables voxel rendering
- `r_drawplayersprites`: Enables player sprite rendering
- `r_radarclipper`: Uses the horizontal clipper from the camera tracer's perspective
- `r_dithertransparency`: Uses dithered transparency for actor-occluding geometry
- `r_quakeintensity`: Controls the intensity of quake effects
- `r_actorspriteshadow`: Controls actor sprite shadow rendering
- `r_actorspriteshadowdist`: Controls the distance at which sprite shadows are rendered
- `r_actorspriteshadowalpha`: Controls the opacity of sprite shadows
- `r_actorspriteshadowfadeheight`: Controls the fade distance for sprite shadows
- `screenblocks`: Controls the size of the view window
- `r_visibility`: Controls the visibility distance
- `r_skymode`: Controls the sky rendering mode
- `maxviewpitch`: Controls the maximum view pitch angle

### Functions

#### View Setup Functions

```cpp
void R_SetFOV(FRenderViewpoint &viewpoint, DAngle fov);
void R_SetViewSize(int blocks);
void R_SetWindow(FRenderViewpoint &viewpoint, FViewWindow &viewwindow, int windowSize, int fullWidth, int fullHeight, int stHeight, bool renderingToCanvas);
void R_ExecuteSetViewSize(FRenderViewpoint &viewpoint, FViewWindow &viewwindow);
```

These functions set up the view for rendering:
- `R_SetFOV`: Sets the field of view for a viewpoint
- `R_SetViewSize`: Sets the view size in blocks
- `R_SetWindow`: Sets up the view window parameters
- `R_ExecuteSetViewSize`: Executes the view size change

#### Visibility Functions

```cpp
double R_ClampVisibility(double vis);
double R_GetGlobVis(const FViewWindow &viewwindow, double vis);
```

These functions handle visibility calculations:
- `R_ClampVisibility`: Clamps the visibility value to a valid range
- `R_GetGlobVis`: Calculates the global visibility constant

#### Interpolation Functions

```cpp
void R_InterpolateView(FRenderViewpoint& viewPoint, const player_t* const player, const double ticFrac, InterpolationViewer* const iView);
void R_ResetViewInterpolation();
void R_RebuildViewInterpolation(player_t *player);
bool R_GetViewInterpolationStatus();
void R_ClearInterpolationPath();
void R_AddInterpolationPoint(const DVector3a &vec);
InterpolationViewer *FindPastViewer(AActor *actor);
void R_FreePastViewers();
void R_ClearPastViewer(AActor *actor);
```

These functions handle view interpolation:
- `R_InterpolateView`: Interpolates the view between two states
- `R_ResetViewInterpolation`: Resets the view interpolation state
- `R_RebuildViewInterpolation`: Rebuilds the view interpolation for a player
- `R_GetViewInterpolationStatus`: Returns the current interpolation status
- `R_ClearInterpolationPath`: Clears the interpolation path
- `R_AddInterpolationPoint`: Adds a point to the interpolation path
- `FindPastViewer`: Finds or creates a past viewer for an actor
- `R_FreePastViewers`: Frees all past viewer data
- `R_ClearPastViewer`: Clears the past viewer data for an actor

#### Frame Setup Functions

```cpp
void R_SetupFrame(FRenderViewpoint& viewPoint, const FViewWindow& viewWindow, AActor* const camera);
```

This function sets up the frame for rendering, handling:
- Camera position and orientation
- View interpolation
- Sector effects
- Quake effects
- View angle calculations

#### Miscellaneous Functions

```cpp
static double QuakePower(double factor, double intensity, double offset);
static void R_DoActorTickerAngleChanges(player_t* const player, DRotator& angles, const double scale);
bool P_NoInterpolation(player_t const *player, AActor const *actor);
bool R_ShouldDrawSpriteShadow(AActor *thing);
void R_Init();
void R_Shutdown();
```

These functions handle various rendering tasks:
- `QuakePower`: Calculates the power of a quake effect
- `R_DoActorTickerAngleChanges`: Applies actor ticker angle changes
- `P_NoInterpolation`: Determines if interpolation should be skipped
- `R_ShouldDrawSpriteShadow`: Determines if a sprite shadow should be drawn
- `R_Init`: Initializes the rendering system
- `R_Shutdown`: Shuts down the rendering system

## Implementation Details

### View Setup Process
The view setup process in `R_SetupFrame` involves several steps:
1. Calculating the view interpolation fraction (`TicFrac`)
2. Finding or creating a past viewer for the camera actor
3. Setting up the view position and orientation
4. Handling quake effects
5. Interpolating the view between the previous and current states
6. Setting the view angle and calculating derived values
7. Keeping the view within sector boundaries
8. Setting up sector effects

### View Interpolation
View interpolation in `R_InterpolateView` smooths camera movement by:
1. Interpolating the position between the previous and current states
2. Handling portal transitions using the interpolation path
3. Interpolating the view angles
4. Applying view offsets and angle offsets
5. Ensuring the view stays within valid bounds

### Visibility Calculation
The visibility calculation in `R_GetGlobVis` determines how far the player can see:
1. Clamping the visibility value to a valid range
2. Adjusting for aspect ratio
3. Calculating the wall visibility
4. Preventing overflow on walls
5. Scaling the visibility based on the field of view

### Sprite Shadow Rendering
The sprite shadow rendering logic in `R_ShouldDrawSpriteShadow` determines if a sprite should cast a shadow:
1. Checking if the sprite is a wall or flat sprite (which cannot cast shadows)
2. Checking the actor's render flags
3. Checking the sprite shadow mode setting
4. Checking the render style for compatibility with shadows

## Connections with Other Modules
- Used by the rendering system to set up the view for rendering
- Connected to the player system to get player position and angles
- Interfaces with the BSP system for scene traversal
- Used by the portal system for handling view transitions
- Connected to the sector system for handling sector effects
- Interfaces with the sprite rendering system for determining sprite visibility
- Used by the quake effect system for applying screen shakes
- Connected to the console variable system for configuration
