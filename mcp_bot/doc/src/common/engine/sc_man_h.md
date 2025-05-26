# sc_man.h

## File Purpose
This header file defines the script parsing system for GZDoom, providing a robust scanner/lexer for processing text-based script files. It serves as the foundation for parsing various configuration files, DECORATE scripts, ZScript, and other text-based formats used throughout the engine.

## Key Components

### Version Management

- **`VersionInfo`**: Structure for handling version information
  - Stores major, minor, and revision numbers
  - Provides comparison operators for version checking
  - Used to control feature availability based on script version

### FScanner Class

- **Core Scanning Class**: Main class for lexical analysis of script files
  - **File Management**:
    - `Open`: Opens a script from a named lump
    - `OpenFile`: Opens a script from a file
    - `OpenMem`: Opens a script from memory
    - `OpenString`: Opens a script from a string
    - `OpenLumpNum`: Opens a script from a lump number
    - `Close`: Closes the current script
  
  - **Parsing Configuration**:
    - `SetCMode`: Enables/disables C-style syntax
    - `SetEscape`: Controls escape sequence handling
    - `SetStateMode`: Enables special state parsing mode
    - `SetNoOctals`: Controls octal number interpretation
    - `SetParseVersion`: Sets the script version for feature detection
  
  - **Position Management**:
    - `SavePos`: Saves the current position in the script
    - `RestorePos`: Restores a previously saved position
    - `UnGet`: Pushes back the last token
  
  - **Token Retrieval**:
    - `GetString`: Gets the next string
    - `GetToken`: Gets the next token
    - `GetNumber`: Gets the next number
    - `GetFloat`: Gets the next floating-point number
    - Various `Must*` methods that require a specific token type
    - Various `Check*` methods that check for a specific token type
  
  - **Symbol Management**:
    - `AddSymbol`: Adds a symbol to the symbol table
    - `LookupSymbol`: Looks up a symbol in the symbol table
  
  - **Error Handling**:
    - `ScriptError`: Reports a script error
    - `ScriptMessage`: Reports a script message

### FScriptPosition Class

- **Error Tracking Class**: Tracks script positions for error reporting
  - Stores filename and line number
  - Provides error reporting methods
  - Tracks error and warning counts

### Token Types

- **Token Enumeration**: Defines the types of tokens recognized by the scanner
  - Basic tokens (identifiers, strings, numbers)
  - Special tokens (operators, keywords)
  - Extended tokens for specific language features

## Technical Details

### Scanner Implementation

The scanner uses a state-based approach to tokenize input:
- Recognizes various token types (identifiers, numbers, strings, etc.)
- Handles different parsing modes (C-mode, state mode)
- Supports escape sequences in strings
- Processes comments and whitespace

### Symbol Table

The scanner maintains a symbol table for:
- Defining constants and macros
- Supporting symbol lookup during parsing
- Allowing for context-sensitive parsing

### Error Handling

The error system provides:
- Detailed error messages with line numbers
- Different severity levels (error, warning, message)
- Error counting for tracking parsing problems
- Options for fatal vs. non-fatal errors

### Position Tracking

The scanner tracks:
- Current line number
- Current position in the script
- Previous token position for error reporting
- Ability to save and restore positions for lookahead

## Connections with Other Modules

- Used by the DECORATE parser for actor definitions
- Used by the ZScript parser for advanced scripting
- Used by the ACS compiler for script compilation
- Used by various configuration parsers throughout the engine
- Provides error reporting infrastructure for all text parsing

## Notable Features

- Support for different parsing modes (C-style, state mode)
- Version-based feature detection for backward compatibility
- Robust error reporting with line numbers
- Symbol table for constants and macros
- Position saving and restoring for complex parsing
- Support for different number formats (decimal, hex, octal)
- UTF-8 byte order mark detection and handling
- Flexible input sources (files, lumps, memory, strings)
