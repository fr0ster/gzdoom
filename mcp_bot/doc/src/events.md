# events.cpp

## File Purpose
This source file implements the event handling system for GZDoom, providing the functionality for the event framework defined in `events.h`. It manages the registration, execution, and communication of events throughout the engine, enabling both internal systems and external mods to respond to various game events. The implementation supports network communication, serialization, and virtual machine integration for ZScript.

## Key Components

### Network Buffer Implementation

- **`DNetworkBuffer` Class Implementation**: 
  - Methods for adding different data types to the buffer
  - Serialization support for saving/loading buffer contents
  - Memory management for buffer contents

### Event Manager Implementation

- **`EventManager` Methods**:
  - Handler registration and unregistration
  - Event dispatching to appropriate handlers
  - Network event transmission
  - Event data preparation
  - Handler initialization and shutdown

### Event Handler Implementation

- **`DStaticEventHandler` Methods**:
  - Event callback implementations
  - Virtual function overrides for event handling
  - Serialization support
  - Handler lifecycle management

### Network Command Processing

- **`FNetworkCommand` Methods**:
  - Data reading functions for different types
  - Stream position management
  - Endianness handling

### ZScript Integration

- **Action Function Definitions**:
  - Native function bindings for ZScript
  - Parameter handling for script calls
  - Return value processing

### Console Commands

- **`interfaceevent`**: Triggers UI-related events
- **`event`**: Triggers local events
- **`netevent`**: Triggers networked events

## Technical Details

### Handler Registration and Management

- Handlers are organized in a doubly-linked list with proper garbage collection
- Registration inserts handlers at the appropriate position based on their order
- Unregistration properly maintains the linked list structure
- Static handlers are marked as transient objects for garbage collection

### Event Dispatching

- Events are dispatched to handlers in order of registration
- Special handling for static vs. non-static handlers
- Support for event filtering and early termination
- Proper handling of savegame restoration

### Network Communication

- Binary serialization of different data types
- Support for various numeric types and strings
- Endianness handling for cross-platform compatibility
- Buffer management for efficient network transmission

### Virtual Machine Integration

- Virtual function calls to ZScript event handlers
- Parameter marshalling between C++ and VM
- Return value handling
- Performance optimization by checking for empty handlers

## Implementation Details

### Handler Execution Order

- Most events are processed from first to last handler
- Some events (like destruction events) are processed from last to first
- Static handlers are processed separately from level-specific handlers

### Network Command Structure

- Commands include player index and command name
- Binary data stream for parameters
- Methods for reading different data types with proper error handling

### Event Data Preparation

- Events are populated with relevant data before dispatch
- World events include map state, actor information, etc.
- Render events include camera position, angles, etc.
- Player events include player index and state information

### Optimization Techniques

- Empty handler detection to avoid unnecessary VM calls
- Conditional event processing based on game state
- Proper memory management for transient objects

## Connections with Other Modules

- Integrates with the object system through `dobject.h`
- Connects to the serialization system through `serializer.h`
- Uses event definitions from `d_event.h`
- Interfaces with the play simulation through `p_local.h`
- Connects to the rendering system through `r_utility.h`
- Interfaces with the network system through `d_net.h`
- Integrates with the virtual machine through `vmintern.h`
- Provides hooks for ZScript through the event handler system
- Enables mod developers to respond to game events
