# p_acs.h

## File Purpose
This header file defines the structures and classes for the ACS (Action Code Script) system in GZDoom. ACS is a scripting language originally developed for Hexen, which allows map authors to create interactive and dynamic maps with custom behaviors. The file provides the foundation for script execution, variable management, string handling, and the overall ACS virtual machine infrastructure.

## Key Components

### Global Variables and Arrays
```cpp
extern BoundsCheckingArray<int32_t, NUM_GLOBALVARS> ACS_GlobalVars;
extern BoundsCheckingArray<FWorldGlobalArray, NUM_GLOBALVARS> ACS_GlobalArrays;
```

These global arrays store ACS global variables and arrays that persist across all maps in a game session.

### BoundsCheckingArray Template
```cpp
template <typename T, unsigned int N>
struct BoundsCheckingArray
{
    T &operator[](const unsigned int index);
    T *Pointer();
    unsigned int Size() const;
    void Fill(const T &value);
private:
    T buffer[N];
};
```

A template class that provides bounds-checking for array access, used to prevent buffer overflows in the ACS virtual machine.

### ACSStringPool Class
```cpp
class ACSStringPool
{
public:
    ACSStringPool();
    int AddString(const char *str);
    int AddString(FString &str);
    const char *GetString(int strnum);
    void LockString(int levelnum, int strnum);
    void UnlockAll();
    // ... more methods
private:
    // ... implementation details
};
```

Manages the global string table for ACS scripts. It handles string storage, reference counting, and garbage collection for strings used by ACS scripts.

### ACSLocalVariables Class
```cpp
class ACSLocalVariables
{
public:
    ACSLocalVariables(TArray<int32_t> &variables);
    void Reset(int32_t *const memory, const size_t count);
    int32_t& operator[](const size_t index);
    const int32_t *GetPointer() const;
private:
    int32_t *memory;
    size_t count;
};
```

Manages local variables for ACS script instances, providing bounds-checked access to the variable storage.

### ACSLocalArrays Structure
```cpp
struct ACSLocalArrays
{
    unsigned int Count;
    ACSLocalArrayInfo *Info;

    ACSLocalArrays();
    ~ACSLocalArrays();
    void Set(ACSLocalVariables &locals, int arraynum, int arrayentry, int value);
    int Get(ACSLocalVariables &locals, int arraynum, int arrayentry);
};
```

Manages local arrays for ACS script instances, providing bounds-checked access to array elements.

### Script Pointer Structures
```cpp
struct ScriptPtr
{
    int Number;
    uint32_t Address;
    uint8_t Type;
    uint8_t ArgCount;
    uint16_t VarCount;
    uint16_t Flags;
    ACSLocalArrays LocalArrays;
    ACSProfileInfo ProfileData;
};
```

The in-memory representation of an ACS script, containing its number, address, type, argument count, and other metadata.

Several other script pointer structures (`ScriptPtr1`, `ScriptPtr2`, `ScriptPtr3`) are defined for compatibility with different ACS formats.

### Script Function Structures
```cpp
struct ScriptFunction
{
    uint8_t ArgCount;
    uint8_t HasReturnValue;
    uint8_t ImportNum;
    int  LocalCount;
    uint32_t Address;
    ACSLocalArrays LocalArrays;
};
```

Represents an ACS function, containing its argument count, return value flag, and other metadata.

### FBehavior Class
```cpp
class FBehavior
{
public:
    FBehavior();
    ~FBehavior();
    bool Init(FLevelLocals *l, int lumpnum, FileReader * fr = NULL, int len = 0, int reallumpnum = -1);
    bool IsGood();
    // ... many more methods
private:
    // ... implementation details
};
```

Represents an ACS script module (typically loaded from a lump in a WAD file). It manages script execution, function calls, variable access, and other aspects of the ACS virtual machine.

### FBehaviorContainer Structure
```cpp
struct FBehaviorContainer
{
    FLevelLocals *Level;
    TArray<FBehavior *> StaticModules;

    FBehaviorContainer(FLevelLocals *l);
    FBehavior *LoadModule(int lumpnum, FileReader *fr = nullptr, int len = 0, int reallumpnum = -1);
    void LoadDefaultModules();
    // ... more methods
};
```

Manages multiple `FBehavior` instances, providing methods to load, unload, and access ACS modules.

### DACSThinker Class
```cpp
class DACSThinker : public DThinker
{
    DECLARE_CLASS(DACSThinker, DThinker)
    HAS_OBJECT_POINTERS
public:
    static const int DEFAULT_STAT = STAT_SCRIPTS;
    void Construct();
    ~DACSThinker();
    void Serialize(FSerializer &arc);
    void Tick();
    typedef TMap<int, DLevelScript *> ScriptMap;
    ScriptMap RunningScripts;
    void DumpScriptStatus();
    void StopScriptsFor(AActor *actor);
private:
    DLevelScript *LastScript = nullptr;
    DLevelScript *Scripts = nullptr;
};
```

A thinker class that manages running ACS scripts. It updates scripts each tick and maintains a list of all active scripts.

## Implementation Details

### Script Types
```cpp
enum
{
    SCRIPT_Closed       = 0,
    SCRIPT_Open         = 1,
    SCRIPT_Respawn      = 2,
    // ... more script types
};
```

Defines the various types of ACS scripts, which determine when they are automatically executed:
- `SCRIPT_Closed`: Executed when triggered by another script or a line special
- `SCRIPT_Open`: Executed when the level starts
- `SCRIPT_Respawn`: Executed when a player respawns
- And many more for different game events

### Script Flags
```cpp
enum
{
    SCRIPTF_Net = 0x0001,        // Safe to "puke" in multiplayer
    SCRIPTF_ClientSide = 0x0002, // Executed locally for clients but not across them
};
```

Flags that control script behavior, particularly in multiplayer games.

### ACS Formats
```cpp
enum ACSFormat { ACS_Old, ACS_Enhanced, ACS_LittleEnhanced, ACS_Unknown };
```

Identifies the different ACS format versions:
- `ACS_Old`: The original Hexen format
- `ACS_Enhanced`: The ZDoom extended format
- `ACS_LittleEnhanced`: A variant of the enhanced format with different endianness
- `ACS_Unknown`: An unrecognized format

### String Pool Management
The `ACSStringPool` class provides sophisticated string management for ACS scripts:
- Strings are stored in a hash table for efficient lookup
- Reference counting prevents premature deletion of strings
- Garbage collection removes unused strings
- Strings can be locked to specific map levels

### Variable Scopes
ACS supports several variable scopes:
- Global variables (persist across all maps)
- Map variables (persist within a single map)
- Local variables (exist only within a script instance)
- World variables (accessible by all scripts)
- Global arrays (dynamic arrays with global scope)

### Script Execution
The `FBehavior` class handles script execution:
- Scripts are identified by number and type
- Scripts can be started by map events, line specials, or other scripts
- Functions can be called with arguments and return values
- Variables and arrays can be accessed and modified

### Module Management
The `FBehaviorContainer` structure manages ACS modules:
- Modules can be loaded from WAD lumps
- Default modules are loaded automatically
- Modules can import functions from other modules
- Module states are serialized for save games

## Connections with Other Modules
- Interfaces with the `DThinker` system for script execution
- Connects to the level system for map-specific scripts
- Interfaces with the actor system for script activators
- Connects to the serialization system for save/load functionality
- Used by line specials to trigger scripts
- Interfaces with the console variable system for script-accessible CVARs
