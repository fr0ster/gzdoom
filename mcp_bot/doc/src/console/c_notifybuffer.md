# c_notifybuffer.cpp

## File Purpose
This source file implements the notification message buffer system for GZDoom. It handles the display of temporary messages that appear on the screen during gameplay, such as pickup notifications, damage indicators, and other game events. The notification system manages the lifecycle of these messages, including their appearance, duration, and fading effects.

## Key Components

### FNotifyBuffer Class

- **`FNotifyBuffer`**: A class derived from `FNotifyBufferBase` that implements the notification buffer system for GZDoom.
- **`AddString`**: Method to add a new message to the notification buffer.
- **`Clear`**: Method to clear all messages from the notification buffer.
- **`Draw`**: Method to render the notification messages on the screen.

### Configuration Variables

- **`con_notifytime`**: Controls how long (in seconds) notification messages remain on screen.
- **`con_centernotify`**: Boolean that determines if notifications are centered horizontally.
- **`con_pulsetext`**: Boolean that enables a pulsing effect on notification text.
- **`con_scaletext`**: Integer that controls text scaling at high resolutions.
- **`con_notifylines`**: Integer that sets the maximum number of notification lines to display.
- **`show_messages`**: Boolean that enables or disables notification messages entirely.
- **`show_obituaries`**: Boolean that controls whether death messages are shown.

### Global Objects

- **`NotifyStrings`**: The global instance of the notification buffer.

## Technical Details

### Notification Message Lifecycle

1. Messages are added to the buffer via `AddString`
2. Each message is assigned a timeout value based on `con_notifytime`
3. Messages are drawn on screen with the `Draw` method
4. Messages fade out during their final seconds (controlled by `NOTIFYFADETIME`)
5. Messages are removed when their timeout reaches zero

### Message Display System

The `Draw` method handles rendering messages with these features:
- Vertical stacking of multiple messages
- Horizontal centering (optional)
- Alpha fading for smooth disappearance
- Color coding based on message priority level
- Text pulsing effect (optional)
- Proper scaling for different resolutions

### Status Bar Integration

The notification system integrates with the status bar:
- The status bar can optionally take over notification display
- This is handled through the virtual method `ProcessNotify`
- The `FlushNotify` method is called when notifications are cleared

### Text Scaling

The system supports dynamic text scaling:
- The `con_scaletext` CVAR controls whether scaling is applied
- The `active_con_scaletext` function determines the actual scale factor
- This allows notifications to remain readable at high resolutions

## Connections with Other Modules

- Interfaces with the console system for message output
- Connects to the status bar system for optional notification handling
- Uses the video system for text rendering
- Integrates with the game state system to determine when to show notifications
- Utilizes the font system for text display

## Notable Features

- Smooth fade-in/fade-out of notification messages
- Optional text pulsing effect for better visibility
- Support for centered or left-aligned messages
- Color coding based on message priority
- Integration with the status bar system
- Resolution-independent text scaling
- Configurable display duration and line count
