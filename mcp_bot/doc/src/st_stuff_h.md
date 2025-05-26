# st_stuff.h

## File Purpose
This header file defines the interface for the status bar's event handling system in GZDoom. While the actual status bar implementation is in separate files (referenced in the header as `*_sbar.cpp`), this header specifically focuses on the cheat code handling functionality. It provides a mechanism for intercepting keyboard events and processing them as potential cheat code inputs before they are passed to other parts of the game.

## Key Components

### Event Handling Function

- **`ST_Responder`**: The main function that processes keyboard events to detect and handle cheat codes.
  - Takes an `event_t` pointer as input, which contains information about the keyboard event.
  - Returns a boolean indicating whether the event was consumed (true) or should be passed to other handlers (false).
  - Acts as the entry point for the cheat system in the game's event processing pipeline.

## Technical Details

### Event Processing

- The `ST_Responder` function intercepts keyboard events before they reach other parts of the game.
- It checks if the input matches any known cheat code sequences.
- If a cheat code is detected, it executes the corresponding action and may consume the event to prevent it from being processed further.

### Integration with Event System

- The function is called from the main event processing loop in the game engine.
- It returns `true` if it consumes an event (typically when a cheat is activated), preventing other handlers from processing it.
- It returns `false` if the event should be passed on to other handlers.

## Connections with Other Modules

- Interfaces with the event system (`d_event.h`) to receive keyboard events.
- Connected to the cheat code implementation in `st_stuff.cpp`.
- Indirectly connected to the status bar implementation files (`*_sbar.cpp`).
- Used by the main game loop to process potential cheat inputs.

## Notable Features

- Simple and focused interface with just one function.
- Clear separation between the cheat system interface and implementation.
- Integration with the game's event handling system.
- Support for intercepting and consuming keyboard events when they match cheat patterns.
