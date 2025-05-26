# doomdata.h

## File Purpose
This header file defines the fundamental data structures used for map representation in GZDoom. It contains the original Doom map format structures as well as extensions for Hexen, Strife, and other game variants. These structures define how map data is stored in WAD files and how it's processed by the engine. The file serves as a bridge between the raw map data and the engine's internal representation.

## Key Components

### Map Lump Enumeration

- **`ML_*` Constants**: Define the order and purpose of lumps in a map WAD file
  - `ML_LABEL`: Map name (e.g., E1M1, MAP01)
  - `ML_THINGS`: Monster and item placements
  - `ML_LINEDEFS`: Line definitions for walls and triggers
  - `ML_SIDEDEFS`: Side definitions for texturing
  - `ML_VERTEXES`: Vertex coordinates
  - `ML_SEGS`, `ML_SSECTORS`, `ML_NODES`: BSP tree data
  - `ML_SECTORS`: Sector definitions
  - `ML_REJECT`, `ML_BLOCKMAP`: Optimization lookup tables
  - Extended lumps for Hexen scripts, Strife conversations, etc.

### Map Data Structures

#### Vertex Definition
- **`mapvertex_t`**: Defines a point in 2D space
  - `x`, `y`: 16-bit coordinates

#### Line Definitions
- **`maplinedef_t`**: Original Doom line definition
  - `v1`, `v2`: Vertex indices
  - `flags`: Line behavior flags
  - `special`: Special effect type
  - `tag`: Sector tag for activation
  - `sidenum`: Side definition indices

- **`maplinedef2_t`**: Hexen-compatible line definition
  - Similar to `maplinedef_t` but with `args` array instead of `tag`

#### Side Definition
- **`mapsidedef_t`**: Defines the visual appearance of a wall
  - `textureoffset`, `rowoffset`: Texture positioning
  - `toptexture`, `bottomtexture`, `midtexture`: Texture names
  - `sector`: Front sector index

- **`intmapsidedef_t`**: Internal side definition with FString textures

#### Sector Definition
- **`mapsector_t`**: Defines a volume of space
  - `floorheight`, `ceilingheight`: Floor and ceiling heights
  - `floorpic`, `ceilingpic`: Floor and ceiling texture names
  - `lightlevel`: Sector brightness
  - `special`: Sector special effect
  - `tag`: Sector identifier for activation

#### BSP Tree Structures
- **`mapsubsector_t`**: Subsector definition
  - `numsegs`: Number of segments
  - `firstseg`: Index of first segment

- **`mapseg_t`**: Line segment definition
  - `v1`, `v2`: Vertex indices
  - `angle`: Segment angle
  - `linedef`: Parent linedef index
  - `side`: Which side of linedef
  - `offset`: Offset along linedef

- **`mapnode_t`**: BSP node definition
  - `x`, `y`, `dx`, `dy`: Partition line
  - `bbox`: Bounding boxes for children
  - `children`: Child node indices

#### Thing Definition
- **`mapthing_t`**: Original Doom thing definition
  - `x`, `y`: Position
  - `angle`: Facing direction
  - `type`: Thing type
  - `options`: Skill level and appearance flags

- **`mapthinghexen_t`**: Hexen-compatible thing definition
  - Adds `z`, `special`, and `args` fields

- **`FMapThing`**: Internal thing representation
  - Expanded with additional properties like gravity, alpha, scale, etc.

### Flag Enumerations

- **`ELineFlags`**: Line behavior flags
  - `ML_BLOCKING`: Blocks movement
  - `ML_BLOCKMONSTERS`: Blocks only monsters
  - `ML_TWOSIDED`: Line has two sides
  - Texture pegging flags
  - Sound blocking flags
  - Extended flags for various behaviors

- **`SPAC`**: Special activation types
  - `SPAC_Cross`: Activated when player crosses line
  - `SPAC_Use`: Activated when player uses line
  - `SPAC_Impact`: Activated when projectile hits line
  - Various other activation methods

- **`EMapThingFlags`**: Thing placement flags
  - Skill level filters
  - Game mode filters (single, coop, deathmatch)
  - Behavior flags (ambush, dormant, friendly)
  - Appearance flags (shadow, standstill)

## Technical Details

### Map Format Compatibility

- Supports multiple map formats:
  - Original Doom format
  - Hexen format (with scripts)
  - Strife format (with conversations)
  - UDMF text map format (via `ML_TEXTMAP`)

### Extended Node Formats

- **4-byte Node Formats**:
  - `mapsubsector4_t`, `mapseg4_t`, `mapnode4_t`
  - Support for larger maps with more vertices
  - Different bit flags for subsector marking

### Player Start Structure

- **`FPlayerStart`**: Simplified structure for player start positions
  - Used for spawning players in multiplayer games
  - Derived from map things with appropriate type values

## Connections with Other Modules

- Used by the map loader to read map data from WAD files
- Provides structures for the BSP builder
- Connects to the rendering system for visual representation
- Interfaces with the gameplay system for thing behavior
- Supports the scripting system through special line and thing types
