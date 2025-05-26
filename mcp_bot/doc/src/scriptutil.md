# scriptutil.cpp

## File Purpose
This source file implements the `ScriptUtil` class defined in `scriptutil.h`, providing a generalized interface for executing ZScript functions from C++ code. It serves as a bridge between the native engine code and the scripting system, allowing C++ code to call functions defined in ZScript. This implementation is particularly useful for implementing ACS/FS (Action Code Script/FraggleScript) functions in ZScript, enabling better integration between different scripting systems in GZDoom.

## Key Components

### Global Variables

- **`parameters`**: A static array of `VMValue` objects that stores the parameters to be passed to script functions.
- **`functions`**: A static map that caches VMFunction pointers for script functions, indexed by function name.

### ScriptUtil Implementation

- **`Clear`**: Clears the parameter array and function cache, freeing resources.
- **`BuildParameters`**: Processes a variable argument list and converts the arguments to `VMValue` objects stored in the `parameters` array.
- **`RunFunction`**: Looks up a script function by name and executes it with the provided parameters.
- **`Exec`**: The main entry point for executing script functions, handling parameter building, function execution, and cleanup.

## Technical Details

### Parameter Handling

The `BuildParameters` method processes a variable argument list where each parameter is preceded by a type identifier:
- `Int`: Integer values
- `Pointer`: Generic pointer values
- `Class`: Class pointers (treated as generic pointers)
- `String`: String pointers (must point to persistent memory)
- `Float`: Floating-point values

The parameters are converted to `VMValue` objects and stored in the global `parameters` array.

### Function Lookup and Caching

The `RunFunction` method looks up script functions in the `ScriptUtil` class namespace:
1. First checks the function cache (`functions` map)
2. If not found, looks up the function using `PClass::FindFunction(NAME_ScriptUtil, functionname)`
3. Caches the function pointer for future use
4. Reports an error if the function doesn't exist

### Exception Handling

The `Exec` method includes exception handling to ensure proper cleanup of the parameter array even if an error occurs during function execution. This prevents parameter leakage between function calls.

### Parameter Stack Management

The implementation maintains a parameter stack that grows with each function call:
1. The current position in the parameter array is saved before adding new parameters
2. After function execution, the array is "clamped" back to its original size
3. This allows nested function calls without parameter interference

## Connections with Other Modules

- Interfaces with the VM (Virtual Machine) system for script execution
- Connected to the ZScript class system for function lookup
- Used by ACS and other scripting systems to delegate functionality to ZScript
- Linked to the object system through `dobject.h`

## Notable Features

- Efficient caching of function pointers for repeated calls
- Support for various parameter types (integers, floats, pointers, etc.)
- Clean exception handling to prevent resource leaks
- Parameter stack management for nested function calls
- Simple interface for C++ code to call ZScript functions
