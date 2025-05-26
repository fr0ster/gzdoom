# d_gui.h

## File Purpose
This header file defines the GUI event system for GZDoom, providing enumerations and constants for handling user interface interactions. It establishes the foundation for the game's graphical user interface event handling, including keyboard, mouse, and other input events specific to UI contexts.

## Key Components

### GUI Event Types Enumeration

- **`EGUIEvent`**: Enumeration defining the types of GUI-specific events:
  - **`EV_GUI_None`**: No GUI event
  - **`EV_GUI_KeyDown`**: Key press event in GUI context
  - **`EV_GUI_KeyRepeat`**: Key repeat event in GUI context
  - **`EV_GUI_KeyUp`**: Key release event in GUI context
  - **`EV_GUI_Char`**: Character input event (for text entry)
  - **Mouse Events**: Various mouse events including movement, button clicks, double-clicks, and wheel actions
  - **Navigation Button Events**: Events for browser-style back/forward buttons

### GUI Key Modifiers

- **`GUIKeyModifiers`**: Enumeration defining bit flags for key modifiers:
  - **`GKM_SHIFT`**: Shift key modifier
  - **`GKM_CTRL`**: Control key modifier
  - **`GKM_ALT`**: Alt key modifier
  - **`GKM_META`**: Meta key modifier (Command on macOS)
  - **`GKM_LBUTTON`**: Left mouse button modifier

### Special GUI Key Codes

- **`ESpecialGUIKeys`**: Enumeration defining special key codes for GUI navigation and control:
  - Navigation keys: Page Up/Down, Home, End, arrow keys
  - Function keys: F1-F12
  - Control keys: Backspace, Tab, Return, Escape, Delete
  - Special keys: Browser back, color escape

## Technical Details

### GUI Event Data Structure

GUI events use the general `event_t` structure defined in d_eventbase.h with specific field usage:
- `type`: Set to `EV_GUI_Event` for all GUI events
- `subtype`: Contains the specific GUI event type from `EGUIEvent`
- `data1`, `data2`, `data3`: Used differently based on the event type:
  - For key events: scan code, ASCII code, and modifiers
  - For mouse events: button state and coordinates
- `x`, `y`: Mouse coordinates for GUI events

### Key Event Handling

For keyboard events, the data fields contain:
- `data1`: Unshifted ASCII or special key code
- `data2`: Shifted ASCII (for key events) or alt state (for char events)
- `data3`: Modifier flags (combination of GKM_* values)

### Mouse Event Handling

For mouse events, the data fields contain:
- `data1`: X coordinate (for mouse events)
- `data2`: Y coordinate (for mouse events)
- `data3`: Modifier flags (for wheel events)
- `x`, `y`: Absolute mouse position

## Connections with Other Modules

- Integrates with the general event system defined in d_eventbase.h
- Used by the menu system for user interaction
- Used by the console system for text input
- Provides the foundation for custom UI widgets
- Connects to the input mapping system for translating raw input to game actions

## Notable Features

- Comprehensive support for all common GUI input types
- Special handling for text input with character events
- Support for modifier keys to enable complex input combinations
- Mouse wheel support for scrolling interfaces
- Double-click detection for enhanced interaction
- Browser-style navigation button support
- Special key codes that combine both ASCII values and extended keys
