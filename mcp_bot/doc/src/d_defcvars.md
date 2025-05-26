# d_defcvars.cpp

## File Purpose
This file implements the default console variable (CVar) loading system for GZDoom. It was split from `d_main.cpp` to improve code organization and maintainability. The file provides functionality to load default CVar values from a DEFCVARS lump in WAD files, allowing for version-specific default settings while maintaining backward compatibility.

## Key Components

### D_GrabCVarDefaults Function

The main function `D_GrabCVarDefaults()` handles the loading and processing of default CVar values:

1. Searches for "DEFCVARS" lumps in loaded WAD files
2. Validates that DEFCVARS is only loaded from IWAD files (not user WADs)
3. Checks the version compatibility of the DEFCVARS lump
4. Processes each CVar definition, applying default values to archive CVars
5. Handles blacklisted CVars that shouldn't be modified
6. Manages version-specific CVar name changes and removals

## DEFCVARS Format

The DEFCVARS lump follows a specific format:
```
version 221
set cvar_name value
set another_cvar another_value
...
```

Where:
- The first line must declare the version number
- Each subsequent line sets a default value for a CVar
- The "set" keyword is optional

## Version Compatibility

The file includes specific version compatibility handling:

- Requires at least version 219
- Version 220 changes:
  - Renamed `gamma` to `vid_gamma`
  - Renamed `fullscreen` to `vid_fullscreen`
  - Removed `cd_drive`
- Version 221 changes:
  - Removed `mouse_sensitivity`
  - Removed `m_noprescale`

## Blacklisted CVars

The file implements a blacklist system for CVars that should not have their defaults modified:

- System-only CVars (those with the `CVAR_SYSTEM_ONLY` flag)
- Explicitly blacklisted CVars using the `SHOULD_BLACKLIST` macro:
  - Input-related CVars (mouse, joystick, keyboard settings)
  - Graphics-related system CVars
  - Statistics and logging CVars
  - Directory path CVars

## Error Handling

The file includes several error and warning messages:
- Error if trying to load DEFCVARS from a user WAD
- Error for unsupported versions
- Warning for blacklisted CVars
- Warning for non-archive CVars (which can't have defaults set)
- Warning for unknown CVars

## Technical Details

- Uses the `SHOULD_BLACKLIST` macro from `d_defcvars.h` to check for blacklisted CVars
- Leverages the `FScanner` class to parse the DEFCVARS lump
- Uses `FindCVar` to locate CVar objects by name
- Sets default values using `SetGenericRepDefault` with string values

## Connections with Other Modules

- Works with the console variable system (`c_cvars.cpp`)
- Integrates with the file system for lump access
- Uses the version information from `version.h`
- Implements the blacklisting mechanism defined in `d_defcvars.h`
- Supports the configuration system by setting appropriate defaults
