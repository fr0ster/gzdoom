# version.h

## File Purpose
This header file defines version information and related constants for GZDoom. It provides a centralized location for version numbers, build identifiers, and compatibility information that is used throughout the codebase. This file is essential for maintaining version consistency across the engine and for ensuring compatibility between different components.

## Key Components

### Version Information Functions

- **`GetGitDescription`**: Returns a string describing the current Git version.
- **`GetGitHash`**: Returns the Git hash of the current build.
- **`GetGitTime`**: Returns the timestamp of the Git commit used for the build.
- **`GetVersionString`**: Returns a formatted version string for display purposes.

### Version Constants

- **`VERSIONSTR`**: A string representation of the current version (e.g., "4.15pre").
- **`RC_FILEVERSION`** and **`RC_PRODUCTVERSION`**: Version numbers used in Windows resource files.
- **`VER_MAJOR`**, **`VER_MINOR`**, **`VER_REVISION`**: Components of the version number for content versioning.
- **`ENG_MAJOR`**, **`ENG_MINOR`**, **`ENG_REVISION`**: Engine version components, which should always refer to the GZDoom version a derived port is based on.

### Compatibility Constants

- **`LASTRUNVERSION`**: Version stored in the ini's [LastRun] section, used for configuration migration.
- **`DEMOGAMEVERSION`**: Protocol version used in demos.
- **`MINDEMOVERSION`**: Minimum demo version that can be played.
- **`SAVEVER`** and **`MINSAVEVER`**: Current and minimum savegame versions.

### Game Identity Constants

- **`GAMESIG`**: Signature used in savegames to identify the game.
- **`BASEWAD`** and **`OPTIONALWAD`**: Names of the base and optional WAD files.
- **`GAMENAME`**, **`WGAMENAME`**, and **`GAMENAMELOWERCASE`**: Different forms of the game name.
- **`QUERYIWADDEFAULT`**: Whether to show the IWAD selection dialog by default.
- **`FORUM_URL`** and **`BUGS_FORUM_URL`**: URLs for the game's forums.

### Display and Interface Constants

- **`SAVEPICWIDTH`** and **`SAVEPICHEIGHT`**: Dimensions for savegame screenshots.
- **`VID_MIN_WIDTH`** and **`VID_MIN_HEIGHT`**: Minimum supported screen dimensions.
- **`GAME_DIR`**: Directory name for game data, which varies by platform.
- **`DEFAULT_DISCORD_APP_ID`**: Default Discord application ID for Rich Presence integration.

## Technical Details

### Version Numbering System

The version numbering system uses a three-part scheme (major.minor.revision) for both the game content and the engine. This allows for precise tracking of compatibility and feature sets.

### Savegame Versioning

The savegame versioning system uses a separate numbering scheme (SAVEVER) that is not directly comparable to the game version. This allows savegame formats to evolve independently of the game version.

### Demo Compatibility

The demo system uses its own versioning to ensure that recorded demos can be played back correctly. The DEMOGAMEVERSION is incremented when demo commands change, and MINDEMOVERSION specifies the oldest demo version that can still be played.

## Connections with Other Modules

- Used by the configuration system to handle version-specific settings
- Connected to the savegame system for compatibility checking
- Linked to the demo recording and playback system
- Referenced by various UI components for displaying version information
- Used by platform-specific code for file locations and resource identification

## Notable Features

- Support for Git-based version information
- Separate versioning for content, engine, demos, and savegames
- Platform-specific paths for game data
- Integration with Discord Rich Presence
- Minimum display resolution requirements
