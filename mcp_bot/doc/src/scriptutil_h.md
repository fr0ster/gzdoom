# scriptutil.h

## File Purpose
This header file defines the `ScriptUtil` class, which provides a bridge between C++ code and the GZDoom scripting system. It offers a simple interface for executing script functions from C++ code with variable arguments of different types. This utility is essential for allowing the engine's native code to interact with script-defined functions, enabling seamless integration between the two programming environments.

## Key Components

### ScriptUtil Class

The `ScriptUtil` class is the main component of this file, providing static methods for script function execution:

- **`Exec`**: The primary method for executing script functions from C++ code. It takes a function name and a variable number of arguments, and returns an integer result.
- **`Clear`**: Clears any internal state or cached data used by the script utility.

### Parameter Type Enumeration

The class defines an unnamed enumeration for parameter types that can be passed to script functions:

- **`End`**: Marks the end of the parameter list.
- **`Int`**: Integer parameter.
- **`Pointer`**: Pointer parameter.
- **`Float`**: Floating-point parameter.
- **`String`**: String parameter.
- **`Class`**: Class reference parameter.

### Internal Helper Methods

- **`BuildParameters`**: A private method that processes the variable argument list and prepares parameters for script execution.
- **`RunFunction`**: A private method that handles the actual execution of the script function with the prepared parameters.

## Technical Details

### Parameter Passing

The `Exec` method uses C-style variable arguments (va_list) to allow calling script functions with different numbers and types of parameters. The parameter types are specified inline with the actual parameters, followed by `End` to mark the end of the parameter list.

### Function Execution

When executing a script function:
1. The `BuildParameters` method processes the variable arguments and converts them to the format expected by the VM.
2. The `RunFunction` method invokes the VM to execute the specified function with the prepared parameters.
3. The result is returned as an integer value.

### Memory Management

The `Clear` method is provided to clean up any resources or state maintained by the `ScriptUtil` class. This is important for preventing memory leaks, especially when the utility is used extensively.

## Connections with Other Modules

- Interfaces with the VM (Virtual Machine) system that executes script code.
- Used by various engine components that need to call script functions.
- Connected to the name system (`FName`) for identifying script functions.
- Provides a bridge between the native C++ engine code and the scripting system.

## Notable Features

- Simple interface for calling script functions from C++ code.
- Support for multiple parameter types (integers, floats, strings, pointers, classes).
- Static methods for easy access from anywhere in the codebase.
- Clean separation between the C++ and script execution environments.
