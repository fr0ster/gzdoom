# d_anonstats.cpp

## File Purpose
This file implements an anonymous statistics collection system for GZDoom. It gathers basic hardware and system information and sends it to a central server to help the development team understand the hardware environment their software runs on. The system is designed to be privacy-conscious, collecting only non-identifying technical data with explicit user consent.

## Key Components

### Core Functions

- `D_DoAnonStats()`: Main function that collects and sends the anonymous statistics
- `D_ConfirmSendStats()`: Displays a confirmation dialog to request user permission
- `D_DoHTTPRequest()`: Performs the HTTP request in a separate thread
- `I_HTTPRequest()`: Platform-specific implementation of HTTP requests

### Data Collection Functions

- `GetOSVersion()`: Retrieves the operating system version and architecture
- `GetCoreInfo()`: Determines the number of CPU cores
- `GetRenderInfo()`: Identifies the rendering backend (OpenGL, Vulkan, etc.)
- `GetGLVersion()`: Gets the OpenGL/Vulkan version number
- `GetDeviceName()`: Retrieves and sanitizes the GPU device name

### Helper Functions

- `URLencode()`: Encodes strings for safe transmission in URLs

### Console Variables (CVARs)

- `anonstats_enabled411`: Controls whether stats collection is enabled (-1: unasked, 0: disabled, 1: enabled)
- `anonstats_host`: The hostname to send statistics to (default: "gzstats.drdteam.org")
- `anonstats_port`: The port to connect to (default: 80)
- `sentstats_hwr_done`: Tracks whether stats have been sent for the current version

## Data Collected

The system collects the following information:
1. Rendering backend (OpenGL, Vulkan, Software)
2. Number of CPU cores
3. Operating system and architecture
4. OpenGL/Vulkan version
5. GPU vendor name
6. GPU model name

## Privacy Considerations

- User consent is explicitly requested before any data is sent
- Data is collected anonymously with no personally identifiable information
- Information is only sent once per system per version
- The confirmation dialog clearly explains what data will be collected and why
- Users can opt out, and their choice is remembered

## Implementation Details

### Platform-Specific Code

The file contains platform-specific implementations for:
- Windows (using WinSock)
- macOS (using CoreFoundation)
- Linux/Unix (using standard sockets)

### GPU Name Sanitization

The `GetDeviceName()` function performs several transformations on GPU names to:
- Remove unnecessary details (like "/SSE2", "/PCIe", etc.)
- Standardize naming conventions
- Add CPU information for integrated graphics to better identify the hardware
- Remove version-specific information that isn't relevant for statistics

### HTTP Request Format

The statistics are sent as a simple HTTP GET request with the following parameters:
- `render`: Rendering backend identifier
- `cores`: Number of CPU cores
- `os`: Operating system and architecture
- `glversion`: OpenGL/Vulkan version (multiplied by 10)
- `vendor`: GPU vendor name
- `model`: GPU model name

## Connections with Other Modules

- Interfaces with the screen system to get GPU information
- Uses the CPU detection system to get processor information
- Connects to the console variable system for configuration
- Uses the threading system for asynchronous HTTP requests
- Interacts with platform-specific UI systems for confirmation dialogs
