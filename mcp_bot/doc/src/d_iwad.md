# d_iwad.cpp

## File Purpose
This file implements the IWAD (Internal WAD) detection and management system for GZDoom. It handles the discovery, validation, and selection of game data files (IWADs) that provide the core assets for different games (Doom, Heretic, Hexen, etc.). The file also manages the loading order of these files and any additional resources they require.

## Key Components

### FIWadManager Class

The central class that manages all IWAD-related functionality:

- **Constructor**: Initializes the manager with paths to base WAD files
- **ParseIWadInfo**: Parses IWADINFO lumps to extract metadata about IWADs
- **ScanIWAD**: Examines an IWAD file to determine which game it belongs to
- **CheckIWADInfo**: Validates an IWAD by checking for the IWADINFO lump
- **CollectSearchPaths**: Gathers directories to search for IWADs
- **AddIWADCandidates**: Scans directories for potential IWAD files
- **ValidateIWADs**: Verifies that found files are valid IWADs
- **IWADPathFileSearch**: Searches for a specific file in IWAD paths
- **IdentifyVersion**: Main function to find and select an appropriate IWAD
- **FindIWAD**: High-level function to locate an IWAD for the current game

### Data Structures

- **FIWADInfo**: Contains metadata about an IWAD (name, game type, required files, etc.)
- **FFoundWadInfo**: Tracks information about discovered IWAD files
- **mIWadInfos**: Collection of all known IWAD types
- **mIWadNames**: List of recognized IWAD filenames
- **mOrderNames**: Preferred order for IWAD selection
- **mSearchPaths**: Directories to search for IWADs
- **mFoundWads**: List of discovered IWAD files

## IWAD Discovery Process

1. **Search Path Collection**:
   - Current directory
   - Executable directory
   - Environment variables (DOOMWADDIR, HOME)
   - Platform-specific locations (Steam, GOG, Bethesda)
   - User-configured paths from config file

2. **IWAD Candidate Collection**:
   - Files with .iwad, .ipk3, or .ipk7 extensions
   - Files matching known IWAD names

3. **IWAD Validation**:
   - Check for IWADINFO lump
   - Scan for required lumps
   - Verify dependencies

4. **IWAD Selection**:
   - Command-line specified IWAD (-iwad parameter)
   - IWAD matching requested game
   - User selection via dialog
   - Default preference from configuration

## IWADINFO Format

The file parses IWADINFO lumps with the following structure:
```
IWAD
{
    Name = "Game Name"
    Autoname = "ShortName"
    IWadname = "filename.wad", priority
    Config = "ConfigName"
    Game = "Doom|Heretic|Hexen|Strife|Chex"
    Mapinfo = "mapinfo/file.txt"
    MustContain = "lump1", "lump2", ...
    BannerColors = "color1", "color2"
    // Additional properties...
}
```

## Special Features

### IWAD Dependencies

The system supports IWAD dependencies, where one IWAD requires another to function properly (e.g., HexenDK requiring Hexen).

### Support WADs

IWADs can specify support WADs that provide additional functionality:
- Loaded automatically in single-player mode
- Optional in multiplayer (controlled by i_loadsupportwad CVAR)

### Additional Resources

IWADs can specify additional files to load:
- Files from the same directory as the IWAD
- Files from the game's resource directories

### Game Startup Customization

IWADs can define custom startup parameters
