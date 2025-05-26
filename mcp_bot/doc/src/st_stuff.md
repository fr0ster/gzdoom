# st_stuff.cpp

## File Purpose
This source file implements the cheat code system in GZDoom. It provides functionality for detecting and processing cheat code sequences entered by the player during gameplay. The file contains the definitions of various cheat codes for different games (Doom, Heretic, Hexen, Strife, and Chex Quest), along with the implementation of the cheat detection system and the actions triggered by each cheat.

## Key Components

### Cheat Sequence Structure

- **`cheatseq_t`**: A structure that defines a cheat code sequence.
  - Contains the sequence of keys that trigger the cheat.
  - Tracks the current position in the sequence.
  - Stores arguments extracted from the sequence.
  - Includes a pointer to the handler function for the cheat.

### Cheat Detection Functions

- **`ST_Responder`**: The main entry point for cheat detection.
  - Processes keyboard events to detect cheat sequences.
  - Selects the appropriate cheat list based on the current game.
  - Returns true if a cheat was detected and the event should be consumed.

- **`CheatCheckList`**: Checks a keyboard event against a list of cheats.
  - Iterates through the cheat list to find matches.
  - Calls the appropriate handler when a cheat is completed.

- **`CheatAddKey`**: Adds a key to a cheat sequence.
  - Updates the position in the sequence.
  - Extracts arguments from the sequence.
  - Returns true when a sequence is completed.

### Cheat Handler Functions

- **`Cht_Generic`**: Handles generic cheats that send a simple command to the network.
- **`Cht_Music`**: Changes the background music.
- **`Cht_BeholdMenu`**: Displays the "beholder" menu for power-ups.
- **`Cht_PumpupMenu`**: Displays the "pumpup" menu for Strife.
- **`Cht_AutoMap`**: Toggles automap cheats.
- **`Cht_ChangeLevel`**: Changes the current level.
- **`Cht_ChangeStartSpot`**: Changes the starting spot in the current level.
- **`Cht_WarpTransLevel`**: Warps to a specific level in Hexen.
- **`Cht_MyPos`**: Toggles position display.
- **`Cht_Ticker`**: Toggles the ticker.
- **`Cht_Sound`**: Displays sound debug information.

### Cheat Code Definitions

The file contains extensive arrays of cheat code sequences for different games:

- **Doom Cheats**: Classic Doom cheats like IDDQD, IDKFA, IDCLIP, etc.
- **Heretic Cheats**: Heretic-specific cheats like QUICKEN, KITTY, RAMBO, etc.
- **Hexen Cheats**: Hexen-specific cheats like SATAN, CASPER, NRA, etc.
- **Strife Cheats**: Strife-specific cheats like OMNIPOTENT, GRIPPER, JIMMY, etc.
- **Chex Quest Cheats**: Chex Quest-specific cheats, many named after developers.
- **Special Cheats**: Additional cheats that work across games.

## Technical Details

### Cheat Sequence Format

- Cheat sequences are defined as arrays of bytes (uint8_t).
- Each array contains the ASCII values of the keys that make up the cheat.
- The sequence is terminated with a value of 255 (0xFF).
- Some cheats include placeholders (0) for arguments that are extracted during input.

### Cheat Processing

- The system tracks the current position in each cheat sequence.
- When a key is pressed, it's compared against the expected next character in each sequence.
- If a match is found, the position is advanced; otherwise, the sequence is reset.
- When a sequence is completed, its handler function is called.
- Arguments embedded in the sequence (like level numbers) are extracted and passed to the handler.

### Cheat Activation Control

- The `allcheats` CVAR enables all cheats regardless of the current game.
- The `nocheats` CVAR disables all cheats.
- The `cl_blockcheats` CVAR blocks cheats in multiplayer games.
- Game-specific flags can also disable keyboard cheats.

## Connections with Other Modules

- Interfaces with the event system (`d_event.h`) to receive keyboard events.
- Connects to the network system (`d_net.cpp`) to send cheat commands in multiplayer games.
- Interacts with the console system (`c_dispatch.cpp`) to execute console commands.
- Uses the game information system (`gameinfo`) to determine which set of cheats to use.
- Connects to the automap system to toggle cheat modes.
- Interfaces with the string system (`GStrings`) for localized messages.

## Notable Features

- Support for game-specific cheat codes.
- Ability to enable all cheats across games with the `allcheats` CVAR.
- Network-safe cheat implementation for multiplayer games.
- Extraction of arguments from cheat sequences.
- Special handling for partial cheat sequences to prevent key binding conflicts.
- Easter egg cheats referencing developers and pop culture.
