# bbannouncer.cpp

## File Purpose
This implementation file provides the functionality for the Blood-style announcer system in GZDoom, known as "The Voice." It implements the interface defined in `announcer.h`, generating text messages and playing voice sounds for significant in-game events such as game starts, kills, telefragging, sprees, and multi-kills. The announcer is modeled after the announcer from the game Blood, adding a distinctive and often humorous commentary to multiplayer matches.

## Key Components

### Sound and Message Data Structures

```cpp
struct SoundAndString
{
    const char *Message;
    const char *Sound;
};
```

A structure that pairs a message string identifier with a sound file name. This is used to associate text messages with voice announcements.

### Sound Collections

```cpp
static const char *BeginSounds[];
static const SoundAndString WorldKillSounds[];
static const SoundAndString SuicideSounds[];
static const SoundAndString KillSounds[];
static const char *GoodJobSounds[];
static const char *TooBadSounds[];
static const char *TelefragSounds[];
```

Arrays of sounds and messages for different types of events:
- `BeginSounds`: Sounds played at the start of a game
- `WorldKillSounds`: Sounds and messages for when a player is killed by the environment
- `SuicideSounds`: Sounds and messages for when a player kills themselves
- `KillSounds`: Sounds and messages for when a player kills another player
- `GoodJobSounds`: Sounds played for good performance (multi-kills)
- `TooBadSounds`: Sounds played when a player loses a killing spree
- `TelefragSounds`: Sounds and messages for telefrag kills

### Global Variables

```cpp
CVAR (Bool, cl_bbannounce, false, CVAR_ARCHIVE)
static int LastAnnounceTime;
static FCRandom pr_bbannounce ("BBAnnounce");
```

- `cl_bbannounce`: A console variable that enables or disables the Blood-style announcer
- `LastAnnounceTime`: Tracks the last time an announcement was made to prevent announcements from playing too close together
- `pr_bbannounce`: A random number generator for selecting random announcements

### Helper Functions

```cpp
void DoVoiceAnnounce(const char *sound)
```

A helper function that plays a voice announcement sound. It ensures that announcements are not played too close together by checking the `LastAnnounceTime`.

### Announcement Functions

```cpp
bool AnnounceGameStart()
bool AnnounceKill(AActor *killer, AActor *killee)
bool AnnounceTelefrag(AActor *killer, AActor *killee)
bool AnnounceSpree(AActor *who)
bool AnnounceSpreeLoss(AActor *who)
bool AnnounceMultikill(AActor *who)
```

Implementations of the functions declared in `announcer.h`. Each function handles a specific type of event:
- `AnnounceGameStart`: Announces the start of a game with a random selection from `BeginSounds`
- `AnnounceKill`: Announces when one actor kills another, with different messages and sounds based on the circumstances (world kill, suicide, or player kill)
- `AnnounceTelefrag`: Announces when one actor telefragged another with a random selection from `TelefragSounds`
- `AnnounceSpree`: Currently returns false (not implemented)
- `AnnounceSpreeLoss`: Announces when an actor's killing spree ends with a random selection from `TooBadSounds`
- `AnnounceMultikill`: Announces when an actor achieves multiple kills in rapid succession with a random selection from `GoodJobSounds`

## Implementation Details

### Announcement Conditions
Announcements are only made if the `cl_bbannounce` console variable is enabled and the game is in deathmatch mode (or multiplayer for telefrag announcements). This allows players to enable or disable the announcer based on their preferences.

### Sound Selection
Sounds are selected randomly from the appropriate arrays using the `pr_bbannounce` random number generator. This adds variety to the announcements and prevents them from becoming repetitive.

### Message Generation
Text messages are retrieved from the game's string table using the `GStrings.GetString` function. The message may include placeholders for player names and pronouns, which are replaced with the appropriate values using the `PronounMessage` function.

### Sound Playback
Sounds are played using the `S_Sound` function, with the `CHAN_VOICE` channel and `ATTN_NONE` attenuation to ensure they are heard clearly regardless of the player's position in the level.

### Timing Control
To prevent announcements from playing too close together and becoming overwhelming, the `DoVoiceAnnounce` function checks if at least 5 seconds have passed since the last announcement before playing a new one.

### Player View Checking
Announcements are only played for players who are involved in the event (either as the killer or the killee) and are viewing the game locally. This ensures that announcements are relevant to the player's experience and are not played unnecessarily for spectators or other players.

## Connections with Other Modules
- Interfaces with the actor system to access information about the actors involved in events
- Uses the game's string table system to retrieve localized message strings
- Connects to the sound system to play announcement sounds
- Interfaces with the player system to check if a player is viewing the game locally
- Uses the game's random number generator for selecting random announcements
- Connects to the console variable system to allow players to enable or disable the announcer
