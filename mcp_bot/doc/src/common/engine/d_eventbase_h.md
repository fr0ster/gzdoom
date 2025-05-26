# d_eventbase.h

## File Purpose
This header file defines the core event system for GZDoom, providing the fundamental structures and functions for handling user input events such as keyboard, mouse, and GUI interactions. It serves as the foundation for the game's input processing pipeline.

## Key Components

### Event Types Enumeration

- **`EGenericEvent`**: Enumeration defining the basic types of input events:
  - **`EV_None`**: No event
  - **`EV_KeyDown`**: Key press event
  - **`EV_KeyUp`**: Key release event
  - **`EV_Mouse`**: Mouse movement event
  - **`EV_GUI_Event`**: GUI-specific event (with subtypes defined in d_gui.h)
  - **`EV_DeviceChange`**: Device connection/disconnection event

### Event Structure

- **`event_t`**: The core structure for representing input events:
  - **`type`**: The main event type (from EGenericEvent)
  - **`subtype`**: Additional event type information (used for GUI events)
  - **`data1, data2, data3`**: Event-specific data fields (keys, buttons, modifiers)
  - **`x, y`**: Coordinates for mouse movement or position

### Event Queue

- **`events[]`**: Array that stores pending events
- **`eventhead, eventtail`**: Indices for managing the circular event queue
- **`MAXEVENTS`**: Constant defining the maximum number of events in the queue (128)

### Event Processing Functions

- **`D_PostEvent`**: Adds an event to the event queue
- **`D_RemoveNextCharEvent`**: Removes character events from the queue
- **`D_ProcessEvents`**: Processes all pending events in the queue
- **`PostMouseMove`**: Helper function for posting mouse movement events

### ZScript Interface Structures

- **`FUiEvent`**: Translates GUI events to a format accessible from ZScript
- **`FInputEvent`**: Translates regular input events to a format accessible from ZScript

## Technical Details

### Event Queue Implementation

The event system uses a circular buffer to store events:
- Events are added at `eventhead` and processed from `eventtail`
- The queue can hold up to `MAXEVENTS` (128) events
- When the queue is full, new events will overwrite the oldest ones

### Event Processing Flow

1. Input devices generate events through platform-specific code
2. Events are posted to the queue via `D_PostEvent`
3. `D_ProcessEvents` is called regularly to process all pending events
4. Events are sent through a responder chain (console, menu, game)
5. The first responder to handle an event stops further processing

### ZScript Integration

The `FUiEvent` and `FInputEvent` structures provide a bridge between the native event system and ZScript:
- They translate the compact `event_t` structure into a more accessible format
- They provide named fields for different event properties
- They handle the conversion of key codes and character values

## Connections with Other Modules

- Interfaces with platform-specific input code that generates events
- Connects to the console system through the `C_Responder` function
- Integrates with the menu system through the `M_Responder` function
- Provides input to the game through the `G_Responder` callback
- Links to the GUI system through the `EV_GUI_Event` event type
- Exposes event data to ZScript through the `FUiEvent` and `FInputEvent` structures

## Notable Features

- Unified event system for all input types
- Circular buffer for efficient event queuing
- Responder chain for prioritized event handling
- Support for both game and GUI events
- ZScript integration for scripted event handling
- Device change detection for controller hot-plugging
