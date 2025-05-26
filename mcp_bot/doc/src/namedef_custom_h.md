# namedef_custom.h

## File Purpose
This header file defines a comprehensive list of string constants used throughout the GZDoom codebase. It serves as a centralized repository of name definitions that are specific to GZDoom, as opposed to the original Doom engine. These names are used for various game elements, actor properties, damage types, animation states, and other identifiers that need to be consistently referenced across the codebase.

## Key Components

### Game Identifiers

- Game-specific identifiers like **`Doom`**, **`Heretic`**, **`Hexen`**, and **`Strife`**
- Engine identifiers like **`ZDoom`**, **`GZDoom`**, **`Eternity`**

### Actor Properties

- Visual effect properties like **`BobPivot3D`**, **`Ghost`**, **`Reflective`**
- Invisibility types like **`Additive`**, **`Fuzzy`**, **`Stencil`**
- Healing types like **`Mana`**, **`Armor`**
- Armor properties like **`SaveAmount`**, **`SavePercent`**, **`MaxAbsorb`**

### Sound Sequences

- Hexen sound sequence names like **`Platform`**, **`PlatformMetal`**, **`Silence`**
- Environmental sounds like **`Lava`**, **`Water`**, **`Ice`**, **`Earth`**
- Door sounds like **`DoorNormal`**, **`DoorHeavy`**, **`DoorMetal`**

### Special Boss Types

- Boss identifiers like **`Fatso`**, **`Arachnotron`**, **`BaronOfHell`**
- Special boss monsters like **`Cyberdemon`**, **`SpiderMastermind`**, **`Ironlich`**

### Player Classes

- Standard player classes like **`DoomPlayer`**, **`HereticPlayer`**, **`StrifePlayer`**
- Hexen player classes like **`FighterPlayer`**, **`ClericPlayer`**, **`MagePlayer`**
- Special player classes like **`ChexPlayer`**, **`ChickenPlayer`**, **`PigPlayer`**

### Damage Types

- Various damage types like **`Drowning`**, **`Slime`**, **`Telefrag`**, **`Falling`**
- Special damage types like **`BFGSplash`**, **`DrainLife`**, **`InstantDeath`**

### Animation States

- Standard animator names like **`Spawn`**, **`See`**, **`Pain`**, **`Melee`**
- Death animation states like **`Death`**, **`XDeath`**, **`Burn`**, **`Disintegrate`**
- Weapon animation states like **`Select`**, **`Deselect`**, **`Ready`**, **`Fire`**

### UDMF Keywords

- Universal Doom Map Format keywords for map editing
- Properties like **`Alpha`**, **`Health`**, **`Pitch`**, **`Special`**
- Line flags like **`Blocking`**, **`Twosided`**, **`Secret`**
- Sector properties like **`Lightlevel`**, **`Gravity`**, **`SoundSequence`**

## Technical Details

### Implementation Mechanism

The file uses a macro system with the placeholder `xx` to define each name. This allows the actual implementation to be defined elsewhere, making this file a template that can be included multiple times with different definitions of the `xx` macro to achieve different results (such as string table generation, enum definition, etc.).

### Naming Conventions

The names follow various conventions depending on their purpose:
- Actor properties typically use CamelCase
- Damage types and animation states typically use lowercase or PascalCase
- UDMF keywords typically use lowercase

### Organization

The names are loosely organized by category, with related names grouped together. This organization helps with maintenance and makes it easier to find specific names.

## Connections with Other Modules

- Used by the actor system to identify properties and states
- Connected to the damage system for identifying damage types
- Linked to the animation system for state names
- Referenced by the map loading system for UDMF properties
- Used by the scripting system for exposing named constants

## Notable Features

- Comprehensive coverage of GZDoom-specific names
- Support for all game modes (Doom, Heretic, Hexen, Strife)
- Extensive UDMF property support for map editing
- Detailed categorization of damage types
- Complete set of animation state names
