# doomtype.h

## File Purpose
This header file defines basic types and includes essential headers used throughout the GZDoom engine. It serves as a foundation for the type system, providing platform-specific definitions and including core utility headers. The file is designed to be included by most other source files, establishing a common set of types and utilities across the codebase.

## Key Components

### Platform-Specific Definitions

- **Windows Path Length Handling**:
  - Defines `PATH_MAX` as 260 for Microsoft Visual C++ to match Windows' `MAX_PATH`
  - Avoids including Windows headers directly in most source files
  - Disables warning about using unsized arrays in structs for MSVC

### Core Type Includes

- **Standard Library Includes**:
  - `<limits.h>`: For integer limits
  - `<tuple>`: For std::tuple support
  - `<algorithm>`: For standard algorithms

- **GZDoom Core Utilities**:
  - `tarray.h`: Dynamic array implementation
  - `name.h`: Name handling (FName class)
  - `zstring.h`: String handling (FString class)
  - `cmdlib.h`: Command-line utilities
  - `basics.h`: Basic type definitions
  - `printf.h`: Printf-style formatting utilities

### Type Definitions

- **Actor Class Mapping**:
  - `PClassActor`: Forward declaration of the actor class type
  - `FClassMap`: Type definition for mapping integers to actor classes using TMap

### Graphics-Related Includes

- **Rendering Support**:
  - `palentry.h`: Palette entry definitions
  - `textureid.h`: Texture identifier handling

### Lighting Mode Enumeration

- **`ELightMode` Enumeration**: Defines different lighting calculation modes
  - `NotSet`: Lighting mode not specified (-1)
  - `LinearStandard`: Standard linear lighting (0)
  - `DoomBright`: Bright Doom-style lighting (1)
  - `Doom`: Standard Doom lighting (2)
  - `DoomDark`: Dark Doom-style lighting (3)
  - `DoomLegacy`: Legacy Doom lighting (4)
  - `Build`: Build engine lighting style (5)
  - `ZDoomSoftware`: ZDoom software renderer lighting (8)
  - `DoomSoftware`: Doom software renderer lighting (16)

## Technical Details

- Uses `int8_t` as the underlying type for the `ELightMode` enumeration
- Employs C++11 scoped enumerations (`enum class`) for type safety
- Provides forward declarations to minimize header dependencies
- Includes only essential headers to reduce compilation time

## Connections with Other Modules

- Included by most other source files in the codebase
- Provides the foundation for the type system used throughout the engine
- Connects to the actor system through the PClassActor forward declaration
- Supports the rendering system through palette and texture includes
- Enables the lighting system through the ELightMode enumeration
