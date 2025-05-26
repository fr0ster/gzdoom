# d_defcvars.h

## File Purpose
This header file provides functionality for blacklisting specific console variables (CVars) in the GZDoom engine. It was split from `d_main.cpp` to improve code organization and maintainability. The file defines a macro used to check if a specific CVar should be blacklisted from certain operations.

## Key Components

### SHOULD_BLACKLIST Macro

The file defines a single macro, `SHOULD_BLACKLIST(name)`, which is the core functionality:

```c++
#define SHOULD_BLACKLIST(name) \
    if (#name[0]==CurrentFindCVar[0]) \
        if (CurrentFindCVar.Compare(#name) == 0) \
            blacklisted = true;
```

This macro:
1. Takes a CVar name as input
2. Performs a quick first-character comparison for efficiency
3. If the first character matches, performs a full string comparison
4. Sets a `blacklisted` boolean to true if the CVar name matches the current CVar being checked

## Technical Details

- The macro uses string literal conversion (`#name`) to convert the parameter into a string
- It performs a two-step comparison (first character, then full string) for optimization
- It assumes the existence of a `CurrentFindCVar` string variable in the scope where the macro is used
- It assumes the existence of a `blacklisted` boolean variable that it will modify

## Usage Context

This macro is typically used in a loop that processes CVars to determine which ones should be excluded from certain operations, such as:
- Saving to configuration files
- Being modified by scripts
- Being displayed in the console
- Being reset to defaults

The implementation follows a pattern where:
1. A `blacklisted` variable is initialized to false
2. The `SHOULD_BLACKLIST` macro is called for each CVar that should be blacklisted
3. After all potential blacklisted CVars are checked, the code takes appropriate action based on the final value of `blacklisted`

## Connections with Other Modules

- Used by the console variable system (`c_cvars.cpp`)
- Integrated with the main initialization code (`d_main.cpp`)
- Supports the configuration file handling system (`m_config.cpp`)
- Works in conjunction with `d_defcvars.cpp`, which likely contains the actual implementation of CVar blacklisting functionality
