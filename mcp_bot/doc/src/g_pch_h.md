# g_pch.h

## File Purpose
This header file serves as a precompiled header (PCH) for the GZDoom codebase. Precompiled headers are used to improve compilation times by including commonly used headers that rarely change. This file includes standard C/C++ library headers, system headers, and some GZDoom-specific headers that are used throughout the codebase, allowing the compiler to process them once and reuse the results in multiple compilation units.

## Key Components

### Standard C Library Headers

- **`stddef.h`**, **`stdlib.h`**, **`stdio.h`**: Basic C standard library headers for memory allocation, I/O operations, and standard definitions.
- **`string.h`**: String manipulation functions.
- **`float.h`**, **`math.h`**: Floating-point and mathematical functions.
- **`limits.h`**: Defines limits of various data types.
- **`stdarg.h`**: Variable argument list handling.
- **`errno.h`**: Error code definitions.
- **`ctype.h`**: Character type functions.
- **`stdint.h`**: Fixed-width integer types.

### Compression Library

- **`miniz.h`**: A lightweight compression library used for ZIP/deflate compression.

### C++ Standard Library Headers

- **`new`**: Dynamic memory allocation operators.
- **`algorithm`**: Standard algorithms like sort, find, etc.
- **`forward_list`**: Singly-linked list container.
- **`limits`**: Numeric limits for C++ types.
- **`memory`**: Smart pointers and memory management.
- **`tuple`**: Fixed-size collection of heterogeneous values.
- **`vector`**: Dynamic array container.
- **`utility`**: Utility components like pair, move, etc.
- **`functional`**: Function objects, function invocations, and related types.

### System Headers

- **`sys/stat.h`**, **`sys/types.h`**: System-specific definitions for file stats and data types.
- **`cassert`**: Assertion macro for debugging.

### Platform-Specific Headers

- **`direct.h`**, **`io.h`**: Windows-specific headers for directory operations and I/O functions, included only when compiling with Microsoft Visual C++.

### GZDoom-Specific Headers

- **`tarray.h`**: GZDoom's template-based dynamic array implementation.
- **`zstring.h`**: GZDoom's string class implementation.

## Technical Details

### Precompiled Header Mechanism

The file uses the `#pragma once` directive to ensure it's only included once per compilation unit. It's designed to be included at the beginning of source files to provide access to commonly used declarations and definitions.

### Platform Compatibility

The file includes conditional compilation for Windows-specific headers using the `_MSC_VER` preprocessor macro, ensuring platform-specific code is only compiled on the appropriate platform.

### Performance Considerations

The comment in the file notes that `tarray.h` and `zstring.h` are included because they are used nearly everywhere, and the overall savings from precompiling them outweigh the cost of potential recompilations when they change.

## Connections with Other Modules

- As a precompiled header, this file is connected to virtually all parts of the GZDoom codebase.
- It provides the basic C/C++ library functionality used throughout the engine.
- It includes GZDoom-specific container classes that are used extensively.

## Notable Features

- Comprehensive inclusion of standard library headers
- Platform-specific conditional compilation
- Inclusion of GZDoom's custom container classes
- Designed to optimize compilation times
- Careful selection of headers to balance compilation speed and flexibility
