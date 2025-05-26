# dthinker.cpp

## File Purpose
This implementation file provides the core functionality for the thinker system in GZDoom. It implements the methods declared in `dthinker.h`, handling the management, execution, and lifecycle of thinkers. The thinker system is fundamental to GZDoom's game loop, as it provides the mechanism for updating actors, effects, and other dynamic elements in the game world.

## Key Components

### FThinkerCollection Methods

#### Link
```cpp
void FThinkerCollection::Link(DThinker *thinker, int statnum)
```

Adds a thinker to the appropriate list based on its stat number and whether it has just been spawned. Newly spawned thinkers go into the `FreshThinkers` list, while established thinkers go into the regular `Thinkers` list.

#### RunThinkers
```cpp
void FThinkerCollection::RunThinkers(FLevelLocals *Level)
```

The main method that processes all thinkers in a level. It:
1. Ticks all established thinkers in order of stat number
2. Ticks all fresh thinkers and moves them to the established list
3. Repeats step 2 until no new thinkers are created
4. Updates dynamic lights and particle effects

This method also includes performance profiling capabilities that can be activated with the `profilethinkers` console command.

#### RunClientsideThinkers
```cpp
void FThinkerCollection::RunClientsideThinkers(FLevelLocals* Level)
```

Similar to `RunThinkers`, but specifically for client-side thinkers in multiplayer games. This runs independently of the networked game state.

#### DestroyAllThinkers
```cpp
void FThinkerCollection::DestroyAllThinkers(bool fullgc = true)
```

Destroys all thinkers in all lists, optionally performing a full garbage collection afterward. This is used when changing levels or exiting the game.

#### SerializeThinkers
```cpp
void FThinkerCollection::SerializeThinkers(FSerializer &arc, bool hubLoad)
```

Saves or loads all thinkers to/from a serializer. This is essential for save game functionality. When loading, it reconstructs the thinker lists and calls `PostSerialize` on each thinker.

#### FirstThinker
```cpp
DThinker *FThinkerCollection::FirstThinker(int statnum)
```

Returns the first thinker in the specified stat number's list, checking both the established and fresh lists.

#### MarkRoots
```cpp
void FThinkerCollection::MarkRoots()
```

Marks all sentinel nodes in the thinker lists as roots for garbage collection. This prevents the garbage collector from collecting thinkers that are still in use.

### FThinkerList Methods

#### AddTail
```cpp
void FThinkerList::AddTail(DThinker *thinker)
```

Adds a thinker to the end of the list. If the list doesn't have a sentinel node yet, it creates one.

#### GetHead, GetTail, IsEmpty
```cpp
DThinker *FThinkerList::GetHead() const
DThinker *FThinkerList::GetTail() const
bool FThinkerList::IsEmpty() const
```

Basic list operations for accessing the first and last thinkers in the list, and checking if the list is empty.

#### DestroyThinkers and DoDestroyThinkers
```cpp
void FThinkerList::DestroyThinkers()
bool FThinkerList::DoDestroyThinkers()
```

Destroys all thinkers in the list. `DoDestroyThinkers` does the actual work and returns whether any errors occurred, while `DestroyThinkers` calls it and throws an error if necessary.

#### TickThinkers
```cpp
int FThinkerList::TickThinkers(FThinkerList *dest)
```

Updates all thinkers in the list. If `dest` is not null, it moves thinkers that have just spawned to the destination list after ticking them. Returns the number of thinkers ticked.

#### ProfileThinkers
```cpp
int FThinkerList::ProfileThinkers(FThinkerList *dest)
```

Similar to `TickThinkers`, but also collects performance profiling information for each thinker class.

#### SaveList
```cpp
void FThinkerList::SaveList(FSerializer &arc)
```

Serializes all thinkers in the list to the given serializer.

### DThinker Methods

#### OnDestroy
```cpp
void DThinker::OnDestroy()
```

Called when a thinker is being destroyed. Removes the thinker from its list if it's still in one.

#### Remove
```cpp
void DThinker::Remove()
```

Removes the thinker from its list, updating the `NextToThink` pointer if necessary.

#### PostBeginPlay and CallPostBeginPlay
```cpp
void DThinker::PostBeginPlay()
void DThinker::CallPostBeginPlay()
```

Called just before the first tick of a thinker. `CallPostBeginPlay` handles the virtual function call, while `PostBeginPlay` is the default implementation that can be overridden.

#### PostSerialize and CallPostSerialize
```cpp
void DThinker::PostSerialize()
void DThinker::CallPostSerialize()
```

Called after a thinker is deserialized. `CallPostSerialize` handles the virtual function call, while `PostSerialize` is the default implementation that can be overridden.

#### Tick and CallTick
```cpp
void DThinker::Tick()
void DThinker::CallTick()
```

Called every game tick to update the thinker. `CallTick` handles the virtual function call, while `Tick` is the default implementation that can be overridden.

#### ChangeStatNum
```cpp
void DThinker::ChangeStatNum(int statnum)
```

Changes the thinker's priority level (stat number). This removes the thinker from its current list and adds it to the appropriate list for the new stat number.

#### PropagateMark
```cpp
size_t DThinker::PropagateMark()
```

Marks the thinker's linked list pointers for garbage collection. This ensures that thinkers in the linked lists are not collected prematurely.

### FThinkerIterator Methods

#### Constructors
```cpp
FThinkerIterator::FThinkerIterator(FLevelLocals *l, const PClass *type, int statnum, bool clientside)
FThinkerIterator::FThinkerIterator(FLevelLocals *l, const PClass *type, int statnum, DThinker *prev, bool clientside)
```

Creates an iterator for traversing thinkers of a specific type. The first constructor starts from the beginning, while the second starts after a specific thinker.

#### Next
```cpp
DThinker *FThinkerIterator::Next(bool exact)
```

Returns the next thinker of the specified type. If `exact` is true, it only returns thinkers of exactly the specified class, not derived classes.

#### Reinit
```cpp
void FThinkerIterator::Reinit()
```

Resets the iterator to the beginning.

## Implementation Details

### Thinker Execution Flow
The thinker system follows a specific execution flow to ensure consistent behavior:

1. All established thinkers are ticked in order of stat number
2. Fresh thinkers are ticked and moved to the established list
3. Step 2 is repeated until no new thinkers are created
4. Dynamic lights and particle effects are updated

This ensures that newly created thinkers don't get processed in the same tick they're created, which could lead to inconsistent behavior.

### Safe Thinker Destruction
The thinker system takes special care when destroying thinkers to avoid issues with the linked list structure:

1. All thinkers to be destroyed are first copied to a separate array
2. The linked list is dismantled
3. Each thinker is destroyed individually, catching any exceptions that might occur
4. If any exceptions occur, the thinker is forcibly deleted to prevent memory leaks

### Performance Profiling
The thinker system includes built-in performance profiling capabilities that can be activated with the `profilethinkers` console command. This collects timing information for each thinker class and displays it sorted by various criteria:

- Class name (ascending or descending)
- Number of calls (ascending or descending)
- Average time per call (ascending or descending)
- Total time (ascending or descending)

### Dynamic Light Management
The thinker system integrates with GZDoom's dynamic lighting system. After ticking all thinkers, it:

1. Updates any actors that need their dynamic lights recreated
2. Ticks all dynamic lights in the level
3. Runs particle effects on actors that have them

### Client-Side Thinkers
The thinker system supports both networked and client-side thinkers for multiplayer games. Client-side thinkers are processed independently of the networked game state, allowing for effects and other non-gameplay elements to be handled locally.

## Connections with Other Modules
- Used by `AActor` and all its derivatives for regular updates
- Interfaces with the garbage collection system for memory management
- Connects to the serialization system for save/load functionality
- Used by the level system to manage all dynamic objects in a level
- Integrates with the dynamic lighting system for visual effects
- Supports the particle effect system for visual effects
- Provides performance profiling capabilities for debugging and optimization
