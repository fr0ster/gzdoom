# hu_scores.cpp

## File Purpose
This source file implements the scoreboard functionality for GZDoom, providing routines for drawing player scores and statistics during deathmatch games. It handles the visual representation of player performance, including frags/kills, and supports different game modes such as cooperative, deathmatch, and team deathmatch.

## Key Components

### Scoreboard Drawing Functions

- **`HU_DrawScores`**: The main entry point for drawing the scoreboard, which delegates to the status bar's implementation.
- **`HU_DoDrawScores`**: (Private) Handles the actual drawing of player scores.
- **`HU_DrawTimeRemaining`**: (Private) Draws the remaining time for timed matches.
- **`HU_DrawPlayer`**: (Private) Draws information for a single player on the scoreboard.
- **`HU_DrawColorBar`**: (Private) Draws a colored bar to represent a player's team or status.

### Player Sorting Functions

- **`comparepoints`**: Comparison function for sorting players by frags/kills and then by name.
- **`compareteams`**: Comparison function for sorting players by team, then by frags, then by name.

### Console Commands

- **`togglescoreboard`**: Command to manually toggle the visibility of the scoreboard.

### Configuration Variables

- **`sb_cooperative_enable`**: Controls whether the cooperative scoreboard is enabled.
- **`sb_cooperative_headingcolor`**: Sets the color for cooperative scoreboard headings.
- **`sb_cooperative_yourplayercolor`**: Sets the color for the local player in cooperative mode.
- **`sb_cooperative_otherplayercolor`**: Sets the color for other players in cooperative mode.
- **`sb_deathmatch_enable`**: Controls whether the deathmatch scoreboard is enabled.
- **`sb_deathmatch_headingcolor`**: Sets the color for deathmatch scoreboard headings.
- **`sb_deathmatch_yourplayercolor`**: Sets the color for the local player in deathmatch mode.
- **`sb_deathmatch_otherplayercolor`**: Sets the color for other players in deathmatch mode.
- **`sb_teamdeathmatch_enable`**: Controls whether the team deathmatch scoreboard is enabled.
- **`sb_teamdeathmatch_headingcolor`**: Sets the color for team deathmatch scoreboard headings.

### Global Variables

- **`SB_ForceActive`**: A boolean flag that can be used to force the scoreboard to be displayed.

## Technical Details

### Scoreboard Implementation

The scoreboard system provides a visual representation of player performance in multiplayer games. The implementation includes:
- Sorting players based on game mode (team or individual)
- Drawing player names, scores, and other statistics
- Highlighting the local player for easy identification
- Supporting different color schemes for different game modes
- Displaying the remaining time for timed matches

### Player Sorting

The implementation includes two sorting algorithms:
- For deathmatch: Players are sorted by frags/kills, then by name
- For team deathmatch: Players are sorted by team, then by frags, then by name

## Connections with Other Modules

- Interfaces with the status bar system for drawing the scoreboard
- Connected to the player information system for accessing player statistics
- Linked to the console command system for toggling the scoreboard
- Used by the game's main loop to display the scoreboard during gameplay

## Notable Features

- Support for different game modes (cooperative, deathmatch, team deathmatch)
- Customizable colors for different elements of the scoreboard
- Ability to toggle the scoreboard visibility via console command
- Integration with the status bar system for consistent UI presentation
