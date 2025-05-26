# wi_stuff.h

## File Purpose
This header file defines the structures and interface for the intermission screen system in GZDoom. The intermission screen appears between levels, showing the player's performance statistics for the completed level and information about the upcoming level. This file provides the data structures needed to pass information to the intermission system and the function to initialize an intermission screen.

## Key Components

### Player Statistics Structure

- **`wbplayerstruct_t`**: A structure that stores statistics for a single player.
  - `skills`: Number of monsters killed by the player.
  - `sitems`: Number of items collected by the player.
  - `ssecret`: Number of secrets found by the player.
  - `stime`: Time taken by the player to complete the level.
  - `frags`: Array of frags against each player in multiplayer games.
  - `fragcount`: Cumulative frags for this player across levels.

### Intermission Initialization Structure

- **`wbstartstruct_t`**: A structure that contains all the information needed to initialize an intermission screen.
  - **Episode Information**:
    - `finished_ep`: Index of the episode just finished.
    - `next_ep`: Index of the next episode.
  
  - **Level Names and Information**:
    - `current`: Name of the map just finished.
    - `next`: Name of the next map.
    - `nextname`: Printable name for the next level.
    - `thisname`: Printable name for the current level.
    - `nextauthor`: Author name for the next level.
    - `thisauthor`: Author name for the current level.
    - `LName0`, `LName1`: Texture IDs for level name graphics.
  
  - **Level Statistics**:
    - `totalkills`: Total number of monsters killed in the level.
    - `maxkills`: Maximum possible number of monsters in the level.
    - `maxitems`: Maximum possible number of items in the level.
    - `maxsecret`: Maximum possible number of secrets in the level.
    - `maxfrags`: Maximum possible number of frags in the level.
  
  - **Time Information**:
    - `partime`: Par time for the level in tics.
    - `sucktime`: "Suck time" for the level in minutes (time considered poor performance).
    - `totaltime`: Total time for the entire current game.
  
  - **Player Information**:
    - `pnum`: Index of this player in the game.
    - `plyr`: Array of player statistics for all players.

### Intermission Initialization Function

- **`WI_Start`**: Function to set up an intermission screen.
  - Takes a pointer to a `wbstartstruct_t` structure.
  - Returns a `DObject*` pointer to the created intermission object.

## Technical Details

### Data Structure Design

- The structures are designed to support both single-player and multiplayer games.
- Player statistics are tracked individually for each player.
- Level information includes both internal map names and user-friendly display names.
- Support for custom level authors is included.

### Intermission Initialization

- The `WI_Start` function creates an appropriate intermission object based on the game mode.
- It initializes the object with the provided statistics and level information.
- The returned object handles the rendering and interaction of the intermission screen.

## Connections with Other Modules

- Used by the game state system to transition between levels.
- Interfaces with the texture system for level name graphics.
- Connected to the rendering system for displaying the intermission screen.
- Interacts with the player statistics tracking system.
- Used by the game loop to determine when to advance to the next level.

## Notable Features

- Support for custom level names and authors.
- Tracking of detailed player statistics.
- Compatibility with different game modes (single-player, cooperative, deathmatch).
- Support for par times and performance evaluation.
- Integration with the episode/level structure of the game.
