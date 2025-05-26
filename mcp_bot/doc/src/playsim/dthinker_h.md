# dthinker.h

## File Purpose
This header file defines the `DThinker` class, which serves as the base class for almost anything in a level that needs to be updated regularly (i.e., "think"). It implements a sophisticated thinker management system with linked lists organized by priority levels (stat numbers), allowing for efficient processing of game objects. This system is fundamental to GZDoom's game loop, as it provides the mechanism for updating actors, effects, and other dynamic elements in the game world.

## Key Components

### DThinker Class
```cpp
class DThinker : public DObject
{
    DECLARE_CLASS (DThinker, DObject)
public:
    static const int DEFAULT_STAT = STAT_DEFAULT;
    void OnDestroy () override;
    virtual ~DThinker ();
    virtual void Tick ();
    void CallTick();
    virtual void PostBeginPlay ();
    virtual void CallPostBeginPlay();
    virtual void PostSerialize();
    void CallPostSerialize();
    void Serialize(FSerializer &arc) override;
    size_t PropagateMark();
    
    void ChangeStatNum (int statnum);

private:
    void Remove();

    DThinker *NextThinker = nullptr, *PrevThinker = nullptr;

public:
    FLevelLocals *Level;
};
```

The base class for all objects that need to be updated regularly. Key methods include:
- `Tick()`: Called every game tick to update the thinker
- `PostBeginPlay()`: Called just before the first tick
- `PostSerialize()`: Called after the thinker is deserialized
- `ChangeStatNum()`: Changes the thinker's priority level

### FThinkerList
```cpp
struct FThinkerList
{
    void AddTail(DThinker *thinker);
    DThinker *GetHead() const;
    DThinker *GetTail() const;
    bool IsEmpty() const;
    void DestroyThinkers();
    bool DoDestroyThinkers();
    int TickThinkers(FThinkerList *dest);
    int ProfileThinkers(FThinkerList *dest);
    void SaveList(FSerializer &arc);

private:
    DThinker *Sentinel = nullptr;
};
```

A doubly linked ring list of thinkers. This structure manages a collection of thinkers with the same priority level (stat number). Key methods include:
- `AddTail()`: Adds a thinker to the end of the list
- `GetHead()`: Returns the first thinker in the list
- `GetTail()`: Returns the last thinker in the list
- `TickThinkers()`: Updates all thinkers in the list
- `DestroyThinkers()`: Destroys all thinkers in the list

### FThinkerCollection
```cpp
struct FThinkerCollection
{
    void DestroyThinkersInList(int statnum);
    void RunThinkers(FLevelLocals *Level);
    void RunClientsideThinkers(FLevelLocals* Level);
    void DestroyAllThinkers(bool fullgc = true);
    void SerializeThinkers(FSerializer &arc, bool keepPlayers);
    void MarkRoots();
    DThinker *FirstThinker(int statnum);
    void Link(DThinker *thinker, int statnum);

private:
    FThinkerList Thinkers[MAX_STATNUM + 2];
    FThinkerList FreshThinkers[MAX_STATNUM + 1];
};
```

Manages multiple `FThinkerList` instances, organized by priority level (stat number). Each priority level has two lists: one for established thinkers and one for newly created thinkers. Key methods include:
- `RunThinkers()`: Updates all thinkers in all lists
- `DestroyAllThinkers()`: Destroys all thinkers in all lists
- `SerializeThinkers()`: Saves or loads all thinkers
- `Link()`: Adds a thinker to the appropriate list based on its stat number

### FThinkerIterator
```cpp
class FThinkerIterator
{
protected:
    const PClass *m_ParentType;
private:
    FLevelLocals *Level;
    FThinkerCollection* m_ThinkerPool;
    DThinker *m_CurrThinker;
    uint8_t m_Stat;
    bool m_SearchStats;
    bool m_SearchingFresh;

public:
    FThinkerIterator (FLevelLocals *Level, const PClass *type, int statnum=MAX_STATNUM+1, bool clientside = false);
    FThinkerIterator (FLevelLocals *Level, const PClass *type, int statnum, DThinker *prev, bool clientside = false);
    DThinker *Next (bool exact = false);
    void Reinit ();
};
```

An iterator for traversing thinkers of a specific type. Key methods include:
- `Next()`: Returns the next thinker of the specified type
- `Reinit()`: Resets the iterator to the beginning

### TThinkerIterator
```cpp
template <class T> class TThinkerIterator : public FThinkerIterator
{
public:
    TThinkerIterator (FLevelLocals *Level, int statnum=MAX_STATNUM+1, bool clientside = false);
    TThinkerIterator (FLevelLocals *Level, int statnum, DThinker *prev, bool clientside = false);
    TThinkerIterator (FLevelLocals *Level, const PClass *subclass, int statnum=MAX_STATNUM+1, bool clientside = false);
    TThinkerIterator (FLevelLocals *Level, FName subclass, int statnum=MAX_STATNUM+1, bool clientside = false);
    TThinkerIterator (FLevelLocals *Level, FName subclass, int statnum, DThinker *prev, bool clientside = false);
    T *Next (bool exact = false);
};
```

A templated version of `FThinkerIterator` that returns thinkers of a specific class. This provides type safety and convenience when iterating over specific types of thinkers.

## Implementation Details

### Thinker Priority System
Thinkers are organized into priority levels (stat numbers) defined in `statnums.h`. This allows for controlling the order in which different types of thinkers are processed. For example, actors might be processed before effects, or vice versa.

### Fresh Thinkers
Newly created thinkers are initially placed in a separate "fresh" list. This ensures that new thinkers don't get processed in the same tick they're created, which could lead to inconsistent behavior. After their first tick, they're moved to the regular thinker list.

### Sentinel Nodes
Each thinker list uses a sentinel node to simplify list management. The sentinel is a special thinker that marks the beginning/end of the circular list, making operations like insertion and removal more straightforward.

### Garbage Collection
The thinker system integrates with GZDoom's garbage collector. The `PropagateMark()` method ensures that thinkers in the linked lists are properly marked during garbage collection, preventing them from being collected prematurely.

### Serialization
Thinkers can be serialized (saved and loaded) using the `SerializeThinkers()` method. This is essential for save game functionality.

## Connections with Other Modules
- Used by `AActor` and all its derivatives for regular updates
- Interfaces with the garbage collection system for memory management
- Connects to the serialization system for save/load functionality
- Used by the level system to manage all dynamic objects in a level
- Supports both networked and client-side thinkers for multiplayer games
