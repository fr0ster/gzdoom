# p_states.cpp

## File Purpose
This source file implements the state management system in GZDoom. States are fundamental building blocks for actor behavior, defining animations, actions, and transitions between different behaviors. This file provides functionality for defining, manipulating, and resolving state sequences, as well as handling state jumps and labels. It's a core component of the actor behavior system, enabling the complex state-driven logic that powers game entities.

## Key Components

### Global Variables and Structures

- **`StateLabels`**: A global storage for symbolic state labels used by DECORATE functions.
- **`dehExtStates`**: A map of Dehacked extended states, allowing for state modifications from Dehacked patches.

### State Utility Functions

- **`GetSpriteTexture`**: Script function that retrieves sprite texture information from a state.
- **`StaticFindStateOwner`**: Finds the actor class that owns a specific state.
- **`StaticGetStateName`**: Gets a string representation of a state's name.

### State Label Management

- **`FStateLabels`**: Class for managing hierarchical state labels.
  - `FindLabel`: Finds a label in the state label list.
  - `Destroy`: Cleans up the state label hierarchy.

- **`FStateDefinitions`**: Class for defining and manipulating state sequences.
  - Functions for adding, finding, and resolving state labels.
  - Methods for creating state jumps and transitions.
  - Tools for building state sequences from definitions.

### State Resolution Functions

- **`MakeStateNameList`**: Creates a list of names from a dot-separated string.
- **`FindState`**: Finds a state that matches a sequence of names.
- **`FindStateByString`**: Finds a state associated with a string name.
- **`ResolveGotoLabel`**: Resolves string references to actual state pointers.
- **`VerifyJumpTarget`**: Validates that a state jump target is valid.

### State Installation Functions

- **`InstallStates`**: Creates an actor's state list from definitions.
- **`FinishStates`**: Finalizes state definitions and resolves all references.
- **`FixStatePointers`**: Adjusts state pointers after allocation.
- **`ResolveGotoLabels`**: Resolves all goto labels in a state sequence.

## Technical Details

### State Structure

- States contain information about sprites, frame numbers, duration, actions, and next states.
- States are owned by actor classes and are referenced by index within the class's state array.
- Special flags control state behavior (slow, fast, fullbright, etc.).

### State Label System

- Labels provide symbolic names for states or sequences of states.
- Labels can be hierarchical, allowing for nested state groups.
- Labels are resolved to actual state pointers during actor initialization.

### State Transitions

- States can transition to other states via next state pointers.
- Transitions can be specified by direct pointers or symbolic labels.
- Special transitions include stop, wait, loop, and goto.

### State Definition Process

1. States are defined with frames, durations, and actions.
2. Labels are attached to specific states in the sequence.
3. Transitions between states are defined (next, stop, loop, goto).
4. The state sequence is finalized, allocating memory for the actual states.
5. All symbolic references are resolved to actual state pointers.

### Dehacked Support

- Special handling for Dehacked-modified states.
- Storage for extended states added by Dehacked patches.

## Connections with Other Modules

- Interfaces with the actor system for state ownership and behavior.
- Connected to the sprite system for visual representation.
- Interacts with the scripting system for action functions.
- Used by the game logic to control actor behavior.
- Supports the DECORATE and ZScript language features.

## Notable Features

- Support for hierarchical state labels.
- Flexible state transition system.
- Integration with the scripting system.
- Support for state modifications via Dehacked.
- Robust error checking for state references.
- Debugging tools for state inspection.
