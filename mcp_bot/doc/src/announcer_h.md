# announcer.h

## File Purpose
This header file defines the interface for the announcer system in GZDoom. The announcer system is responsible for generating text messages that announce significant in-game events, such as game starts, kills, sprees, and multi-kills. These announcements enhance the multiplayer experience by providing feedback on player performance and game events.

## Key Components

### Announcement Functions

```cpp
bool AnnounceGameStart();
bool AnnounceKill(AActor *killer, AActor *killee);
bool AnnounceTelefrag(AActor *killer, AActor *killee);
bool AnnounceSpree(AActor *who);
bool AnnounceSpreeLoss(AActor *who);
bool AnnounceMultikill(AActor *who);
```

The header defines six functions for announcing different types of events:

- `AnnounceGameStart`: Announces the start of a game
- `AnnounceKill`: Announces when one actor kills another
- `AnnounceTelefrag`: Announces when one actor telefragged another (killed by teleporting into their space)
- `AnnounceSpree`: Announces when an actor achieves a killing spree (multiple kills without dying)
- `AnnounceSpreeLoss`: Announces when an actor's killing spree ends (they die after achieving a spree)
- `AnnounceMultikill`: Announces when an actor achieves multiple kills in rapid succession

Each function returns a boolean value indicating whether a text message was generated. This allows the calling code to know if an announcement was made and potentially take additional actions based on that information.

## Implementation Details

### Function Parameters
The announcement functions take `AActor` pointers as parameters to identify the actors involved in the event:
- `killer`: The actor that performed the kill
- `killee`: The actor that was killed
- `who`: The actor that achieved a spree or multi-kill

These parameters allow the announcer system to generate personalized messages that include the names of the actors involved.

### Return Values
All announcement functions return a boolean value:
- `true`: A text message was generated
- `false`: No text message was generated

This allows the calling code to know if an announcement was made, which might be useful for synchronizing with other game events or avoiding duplicate announcements.

### Message Generation
While not detailed in the header, the implementation of these functions would typically:
1. Check if announcements are enabled in the game settings
2. Determine if the specific event meets the criteria for an announcement
3. Generate an appropriate message based on the event and actors involved
4. Display the message to players
5. Return `true` if a message was displayed, `false` otherwise

## Connections with Other Modules
- Interfaces with the actor system to access information about the actors involved in events
- Used by the game logic to announce significant events
- May connect to the chat system to display messages to players
- May interface with the sound system to play announcement sounds
- Could be used by the statistics tracking system to record player achievements
