# gameconfigfile.h

## File Purpose
This header file defines the `FGameConfigFile` class, which is a specialized configuration file parser specifically designed for handling GZDoom's configuration files (zdoom.ini). It extends the base `FConfigFile` class to provide game-specific configuration management, including handling of autoload files, key bindings, console variables, and other game settings.

## Key Components

### FGameConfigFile Class

The `FGameConfigFile` class is the main component of this file, providing methods for:

- **Configuration Setup**: Methods to set up various aspects of the game configuration.
- **Configuration Archiving**: Methods to save configuration data back to the file.
- **Autoexec Management**: Methods to handle automatic execution of configuration scripts.
- **Path Management**: Methods to determine the correct path for configuration files.

### Public Methods

- **`DoAutoloadSetup`**: Sets up autoload sections for different game IWADs.
- **`DoGlobalSetup`**: Processes global configuration settings.
- **`DoGameSetup`**: Processes game-specific configuration settings.
- **`DoKeySetup`**: Sets up key bindings for the game.
- **`DoModSetup`**: Sets up mod-specific configuration settings.
- **`ArchiveGlobalData`**: Saves global configuration data.
- **`ArchiveGameData`**: Saves game-specific configuration data.
- **`AddAutoexec`**: Adds autoexec files to a command-line argument list.
- **`GetConfigPath`**: Determines the path to the configuration file.
- **`ReadNetVars`**: Reads network-related configuration variables.

### Protected Methods

- **`WriteCommentHeader`**: Writes a comment header to the configuration file.
- **`CreateStandardAutoExec`**: Creates a standard autoexec section in the configuration file.

### Private Methods

- **`SetRavenDefaults`**: Sets default values for Raven Software games (Heretic/Hexen).
- **`SetStrifeDefaults`**: Sets default values for Strife.
- **`ReadCVars`**: Reads console variables from a section of the configuration file.

### Member Variables

- **`bModSetup`**: Flag indicating whether mod-specific setup has been performed.
- **`section`**: Buffer for constructing section names.
- **`subsection`**: Pointer to the subsection part of the section name.
- **`sublen`**: Length of the subsection part of the section name.

## Technical Details

### Configuration File Structure

The configuration file is organized into sections and subsections, with each section containing key-value pairs. The section names are constructed using the game name as a prefix, followed by a dot and a subsection name. For example:
- `Doom.Player`
- `Doom.LocalServerInfo`
- `Doom.ConsoleVariables`

### Console Variable Handling

The class provides methods for reading and writing console variables (CVars) to and from the configuration file. CVars can be marked with various flags to control how they are handled:
- `CVAR_ARCHIVE`: The CVar should be saved to the configuration file.
- `CVAR_USERINFO`: The CVar contains user information that should be sent to servers.
- `CVAR_SERVERINFO`: The CVar contains server information that should be sent to clients.
- `CVAR_GLOBALCONFIG`: The CVar is part of the global configuration.
- `CVAR_MOD`: The CVar is specific to a mod.

### Autoexec and Autoload

The class manages two types of automatic file handling:
- **Autoexec**: Files that are automatically executed when the game starts.
- **Autoload**: WAD files that are automatically loaded when the game starts.

## Connections with Other Modules

- Extends `FConfigFile` from the configuration system.
- Interfaces with the command-line argument system (`FArgs`).
- Connected to the IWAD management system (`FIWadManager`).
- Used by the console variable system for loading and saving settings.
- Linked to the key binding system for loading and saving key bindings.

## Notable Features

- Support for game-specific configuration sections.
- Handling of mod-specific configuration settings.
- Automatic migration of settings between different versions of the game.
- Support for multiple search paths for game files.
- Integration with the console variable system.
- Management of key bindings and console aliases.
