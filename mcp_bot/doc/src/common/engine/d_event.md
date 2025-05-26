# d_event.cpp

## File Purpose
This source file implements the event processing system for GZDoom, handling the flow of input events from devices to the game. It manages the event queue, processes events through the responder chain, and provides the bridge between native events and ZScript-accessible event structures.

## Key Components

### Event Queue Management

- **`eventhead` and `eventtail`**: Global variables that manage the circular event queue
- **`events[]`**: The array that stores pending events
- **`D_PostEvent`**: Function that adds events to the queue
- **`D_ProcessEvents`**: Function that processes all pending events

### Mouse Sensitivity Controls

- **`m_sensitivity_x` and `m_sensitivity_y`**: CVARs controlling mouse sensitivity
- **`invertmouse` and `invertmousex`**: CVARs controlling mouse axis inversion
- **`PostMouseMove`**: Function that applies sensitivity and inversion to mouse movements

### Event Processing Logic

- **Event Responder Chain**: Processes events through console, menu, and game responders
- **Key Event Tracking**: Tracks key states to handle delayed key-up events
- **Device Change Handling**: Special handling for device connection/disconnection events

### ZScript Integration

- **`FInputEvent` Constructor**: Translates native events to ZScript-accessible format
- **`FUiEvent` Constructor**: Translates GUI events to ZScript-accessible format
- **DEFINE_FIELD_X Macros**: Expose event fields to the ZScript VM

## Technical Details

### Event Queue Implementation

The event queue is implemented as a circular buffer:
- New events are added at `eventhead`
- Events are processed from `eventtail`
- The indices wrap around when they reach `MAXEVENTS`
- The queue is processed in FIFO (First In, First Out) order

### Event Processing Flow

1. `D_PostEvent` adds events to the queue
2. `D_ProcessEvents` is called regularly from the main loop
3. Events are processed in order through the responder chain:
   - First, the console gets a chance to handle the event
   - Then, the menu system
   - Finally, the game itself
4. The first responder to handle an event stops further processing

### Special Event Handling

- **Delayed Key-Up Events**: Key-up events are delayed if they correspond to a key that was just pressed
- **Character Event Removal**: `D_RemoveNextCharEvent` removes character events that follow key-down events
- **Device Change Filtering**: Duplicate device change events are filtered out

### Mouse Movement Processing

The `PostMouseMove` function:
- Applies sensitivity scaling to mouse movements
- Applies inversion based on user settings
- Creates and posts a mouse event if there's any movement

## Connections with Other Modules

- Interfaces with the console system through `C_Responder`
- Connects to the menu system through `M_Responder`
- Integrates with the game through the `G_Responder` callback
- Links to the joystick system for device change events
- Exposes events to ZScript through field definitions
- Uses the CVAR system for user-configurable settings

## Notable Features

- Efficient circular buffer implementation for event queuing
- Prioritized event handling through the responder chain
- Support for delayed key-up events to handle complex input sequences
- Configurable mouse sensitivity and inversion
- Complete ZScript integration for scripted event handling
- Device hot-plugging support
