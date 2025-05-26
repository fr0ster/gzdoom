# events.h

## File Purpose
This header file defines the event handling system for GZDoom, providing a comprehensive framework for game events, network communication, and modding support. It establishes the classes and structures needed for event handlers, event data, and the event management system. This system allows both the engine and mods to respond to various in-game events, from actor spawning to player actions, enabling extensive customization of game behavior.

## Key Components

### Network Communication

#### Network Command Enumerations
- **`ENetCmd`**: Defines data types for network commands
  - `NET_INT8`, `NET_INT16`, `NET_INT`: Integer types of various sizes
  - `NET_FLOAT`, `NET_DOUBLE`: Floating-point types
  - `NET_STRING`: String type

#### Network Command Handling
- **`FNetworkCommand`**: Structure for handling network commands
  - Stores player index and command name
  - Provides methods for reading different data types from a byte stream
  - Handles endianness and data type conversion

#### Network Buffer
- **`DNetworkBuffer`**: Class for building network command buffers
  - Stores values of different types (integers, floats, strings)
  - Tracks buffer size and content
  - Provides serialization support

### Event Handler System

#### Handler Types
- **`EventHandlerType`**: Enumeration for handler scopes
  - `Global`: Handlers that persist across maps
  - `PerMap`: Handlers that are specific to a map

#### Base Event Handler Classes
- **`DStaticEventHandler`**: Base class for event handlers
  - Linked list structure with `prev` and `next` pointers
  - Ordering system for prioritizing handlers
  - UI processing capabilities
  - Comprehensive set of event handling methods
  - Serialization support

- **`DEventHandler`**: Derived class for non-static handlers
  - Overrides `IsStatic()` to return false

### Event Data Structures

- **`FRenderEvent`**: Data for rendering events
  - Camera position and orientation
  - Fractional tic value for interpolation
  - HUD state information

- **`FWorldEvent`**: Data for world events
  - Map loading/unloading information
  - Actor spawning, damage, and destruction details
  - Line activation parameters
  - Sector and line damage information
  - Attack parameters for hitscan and railgun attacks

- **`FPlayerEvent`**: Data for player events
  - Player index
  - Return status flag

- **`FConsoleEvent`**: Data for console events
  - Player index
  - Command name and arguments
  - Manual execution flag

- **`FReplaceEvent`** and **`FReplacedEvent`**: Data for actor replacement events
  - Original and replacement actor classes
  - Finalization flag

### Event Management

- **`EventManager`**: Core class that manages the event system
  - Maintains a linked list of event handlers
  - Registration and unregistration of handlers
  - Methods for dispatching events to handlers
  - Network event transmission
  - Event data preparation
  - Handler initialization and shutdown

## Technical Details

### Handler Registration and Execution

- Handlers are organized in a doubly-linked list
- Handlers have an `Order` property to control execution priority
- The event manager iterates through handlers to dispatch events
- Handlers can be registered and unregistered dynamically

### Event Types

- **World Events**: Map loading/unloading, actor spawning/destruction, line activation, etc.
- **Player Events**: Player entering/leaving, spawning, dying, etc.
- **Render Events**: Frame rendering, overlay/underlay rendering
- **Input Events**: Processing of user input
- **UI Events**: Processing of UI-related events
- **Console Events**: Processing of console commands
- **Network Events**: Processing of network commands
- **Replacement Events**: Actor class replacement

### Network Communication

- Binary serialization of different data types
- Support for various numeric types and strings
- Endianness handling for cross-platform compatibility
- Buffer management for efficient network transmission

## Connections with Other Modules

- Integrates with the object system through `dobject.h`
- Connects to the serialization system through `serializer.h`
- Uses event definitions from `d_event.h`
- Interfaces with the play simulation through `p_local.h`
- Connects to the status bar system through `sbar.h`
- Uses actor information from `info.h`
- Integrates with the virtual machine through `vm.h`
- Provides hooks for ZScript through the event handler system
- Enables mod developers to respond to game events
