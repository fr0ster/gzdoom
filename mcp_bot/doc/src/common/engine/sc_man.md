# sc_man.cpp

## File Purpose
This source file implements the script parsing system for GZDoom, providing the core functionality for lexical analysis and token processing. It contains the implementation of the `FScanner` class and related utilities that form the foundation of GZDoom's text parsing capabilities.

## Key Components

### Version Information Implementation

- **`VersionInfo::operator=`**: Parses version strings into major, minor, and revision components
  - Handles string-to-version conversion
  - Validates version format
  - Sets appropriate defaults for missing components

### FScanner Implementation

- **Constructors and Initialization**:
  - Default constructor with optional external symbol table
  - Constructor that immediately opens a lump
  - Various initialization methods for different input sources

- **File Management**:
  - `Open`: Opens a script from a named lump
  - `OpenFile`: Opens a script from a file
  - `OpenMem`: Opens a script from memory buffer
  - `OpenString`: Opens a script from a string
  - `OpenLumpNum`: Opens a script from a lump number
  - `Close`: Closes the current script
  - `PrepareScript`: Prepares script content for parsing

- **Token Processing**:
  - `ScanString`: Core scanning function that processes the next token
  - `GetString`, `GetToken`, `GetNumber`, `GetFloat`: Token retrieval methods
  - `MustGetString`, `MustGetToken`, etc.: Methods that require specific tokens
  - `CheckString`, `CheckToken`, etc.: Methods that check for specific tokens
  - `UnGet`: Pushes back the last token for re-reading

- **Symbol Table Management**:
  - `AddSymbol`: Adds symbols (constants) to the symbol table
  - `LookupSymbol`: Looks up symbols in the symbol table

- **Position Management**:
  - `SavePos`: Saves the current position in the script
  - `RestorePos`: Restores a previously saved position
  - `CheckOpen`: Verifies that a script is open

- **Error Handling**:
  - `ScriptError`: Reports a script error
  - `ScriptMessage`: Reports a script message

- **Special Parsing Features**:
  - `SetCMode`: Enables/disables C-style syntax
  - `SetEscape`: Controls escape sequence handling
  - `SetStateMode`: Enables special state parsing mode
  - `SkipToEndOfBlock`: Skips to the end of a brace-enclosed block
  - `StartBraces`: Processes the start of a brace-enclosed block
  - `FoundEndBrace`: Checks if the end of a block has been reached

### FScriptPosition Implementation

- **Error Tracking**:
  - Static counters for errors and warnings
  - Configuration for error handling behavior
  - Constructor from filename and line number
  - Constructor from scanner state

- **Error Reporting**:
  - `Message`: Reports a message with appropriate severity
  - Support for different message types (error, warning, debug, etc.)
  - Formatting of error messages with context information

### Utility Functions

- **`ParseHex`**: Parses a hexadecimal string into an integer
  - Validates hex format
  - Reports errors for invalid hex strings

## Technical Details

### Script Preparation

The implementation handles several preprocessing steps:
- Removing UTF-8 byte order marks
- Ensuring scripts end with a newline
- Setting up internal state for parsing

### Token Scanning

The core scanning logic:
- Uses a state machine approach for tokenization
- Handles different token types (identifiers, numbers, strings, etc.)
- Processes comments and whitespace
- Supports different parsing modes (C-mode, state mode)

### Symbol Processing

The symbol table implementation:
- Stores constants and their values
- Supports different value types (integer, float)
- Allows for symbol lookup during parsing

### Error System

The error handling system:
- Provides detailed error messages with line numbers
- Supports different severity levels
- Counts errors and warnings
- Can be configured for fatal or non-fatal errors

## Connections with Other Modules

- Integrates with the file system for loading scripts
- Provides parsing services to higher-level script systems
- Used by configuration parsers throughout the engine
- Supports the DECORATE and ZScript language parsers

## Notable Features

- Robust error reporting with line numbers and context
- Support for different parsing modes
- Symbol table for constants and macros
- Position saving and restoring for complex parsing
- UTF-8 support with BOM detection
- Flexible input sources (files, lumps, memory, strings)
- Version-based feature detection
