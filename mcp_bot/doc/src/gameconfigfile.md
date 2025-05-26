# gameconfigfile.cpp

## File Purpose
This source file implements the `FGameConfigFile` class defined in `gameconfigfile.h`. It provides the functionality for parsing, managing, and saving GZDoom's configuration files (zdoom.ini). The implementation handles various aspects of the game's configuration, including search paths for game files, console variables, key bindings, autoload WADs, and autoexec scripts. It also manages the migration of settings between different versions of the game.

## Key Components

### Constructor and Destructor

- **`FGameConfigFile::FGameConfigFile`**: Initializes the configuration file, sets up default search paths, and adds documentation to the file.
- **`FGameConfigFile::~FGameConfigFile`**: Cleans up resources used by the configuration file.

### Configuration Setup Methods

- **`DoAutoloadSetup`**: Creates and organizes autoload sections for different game IWADs.
- **`DoGlobalSetup`**: Processes global configuration settings and handles version-specific migrations.
- **`DoGameSetup`**: Processes game-specific configuration settings.
- **`DoKeySetup`**: Sets up key bindings for the game.
- **`DoModSetup`**: Sets up mod-specific configuration settings.
- **`ReadNetVars`**: Reads network-related configuration variables.

### Configuration Archiving Methods

- **`ArchiveGlobalData`**: Saves global configuration data.
- **`ArchiveGameData`**: Saves game-specific configuration data.
- **`WriteCommentHeader`**: Writes a comment header to the configuration file.

### Utility Methods

- **`ReadCVars`**: Reads console variables from a section of the configuration file.
- **`GetConfigPath`**: Determines the path to the configuration file.
- **`CreateStandardAutoExec`**: Creates a standard autoexec section in the configuration file.
- **`AddAutoexec`**: Adds autoexec files to a command-line argument list.
- **`SetRavenDefaults`**: Sets default values for Raven Software games (Heretic/Hexen).
- **`SetStrifeDefaults`**: Sets default values for Strife.

## Technical Details

### Configuration File Initialization

The constructor performs several important tasks:
1. Determines the appropriate path for the configuration file
2. Loads the existing configuration file if it exists
3. Sets up default search paths for IWADs, game files, and soundfonts
4. Adds documentation to the configuration file

### Search Path Management

The implementation sets up several types of search paths:
- **IWAD Search Paths**: Directories to search for game IWADs
- **File Search Paths**: Directories to search for additional WAD files
- **Soundfont Search Paths**: Directories to search for soundfonts

These paths are platform-specific, with different default paths for Windows, macOS, and Unix-like systems.

### Version Migration

The `DoGlobalSetup` method includes extensive code for migrating settings between different versions of the game. This ensures that when a user upgrades to a new version of GZDoom, their settings are properly updated to match any changes in the configuration system. Examples include:
- Updating sound channel settings
- Migrating texture filtering options
- Adjusting UI scaling parameters
- Converting old-style settings to new formats

### Autoload and Autoexec Management

The implementation handles two types of automatic file handling:
- **Autoload**: WAD files that are automatically loaded when the game starts
- **Autoexec**: Configuration scripts that are automatically executed when the game starts

The `DoAutoloadSetup` method organizes autoload sections hierarchically, allowing for both game-wide and IWAD-specific autoload files.

### Console Variable Handling

The `ReadCVars` method reads console variables from the configuration file and sets their values. It handles variables with different flags, such as:
- `CVAR_ARCHIVE`: Variables that should be saved to the configuration file
- `CVAR_USERINFO`: Variables that contain user information
- `CVAR_SERVERINFO`: Variables that contain server information
- `CVAR_GLOBALCONFIG`: Variables that are part of the global configuration
- `CVAR_MOD`: Variables that are specific to a mod

## Connections with Other Modules

- Interfaces with the file system for reading and writing configuration files
- Connected to the console variable system for loading and saving settings
- Linked to the key binding system for loading and saving key bindings
- Interacts with the IWAD management system for setting up autoload sections
- Uses the command-line argument system for handling configuration paths

## Notable Features

- Platform-specific search paths for game files
- Hierarchical organization of autoload sections
- Extensive version migration code
- Support for mod-specific configuration settings
- Integration with the console variable system
- Management of key bindings and console aliases
- Self-documentation of configuration file sections
