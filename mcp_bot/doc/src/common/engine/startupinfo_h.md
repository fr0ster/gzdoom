# startupinfo.h

## Призначення файлу
Файл `startupinfo.h` визначає структуру `FStartupInfo`, яка містить інформацію про налаштування запуску гри, включаючи візуальні елементи, музику та інші параметри.

## Короткий опис
Цей файл містить структуру `FStartupInfo`, яка зберігає різноманітні параметри запуску гри, такі як назва, кольори інтерфейсу, музика, ідентифікатори для інтеграції з Discord та Steam, а також налаштування для різних типів ігор (Doom, Heretic, Hexen, Strife). Також файл оголошує глобальну змінну `GameStartupInfo`, яка містить поточні налаштування запуску гри.

## Структура файлу
```cpp
#pragma once

#include <stdint.h>
#include "zstring.h"

struct FStartupInfo
{
    FString Name;
    uint32_t FgColor;           // Foreground color for title banner
    uint32_t BkColor;           // Background color for title banner
    FString Song;
    FString con;
    FString def;
    FString DiscordAppId = nullptr;
    FString SteamAppId = nullptr;
    int Type;
    int LoadLights = -1;
    int LoadBrightmaps = -1;
    int LoadWidescreen = -1;
    enum
    {
        DefaultStartup,
        DoomStartup,
        HereticStartup,
        HexenStartup,
        StrifeStartup,
    };
};


extern FStartupInfo GameStartupInfo;
```

## Основні сутності

### Структура FStartupInfo
```cpp
struct FStartupInfo
{
    FString Name;
    uint32_t FgColor;           // Foreground color for title banner
    uint32_t BkColor;           // Background color for title banner
    FString Song;
    FString con;
    FString def;
    FString DiscordAppId = nullptr;
    FString SteamAppId = nullptr;
    int Type;
    int LoadLights = -1;
    int LoadBrightmaps = -1;
    int LoadWidescreen = -1;
    enum
    {
        DefaultStartup,
        DoomStartup,
        HereticStartup,
        HexenStartup,
        StrifeStartup,
    };
};
```

#### Призначення
Структура `FStartupInfo` містить інформацію про налаштування запуску гри, включаючи візуальні елементи, музику та інші параметри.

#### Поля
- **Name**: Назва гри або модифікації.
- **FgColor**: Колір переднього плану для банера заголовка.
- **BkColor**: Колір фону для банера заголовка.
- **Song**: Музика, яка відтворюється під час запуску.
- **con**: Шлях до файлу консольних команд.
- **def**: Шлях до файлу налаштувань за замовчуванням.
- **DiscordAppId**: Ідентифікатор додатка Discord для інтеграції з Discord Rich Presence.
- **SteamAppId**: Ідентифікатор додатка Steam для інтеграції зі Steam.
- **Type**: Тип запуску гри (DefaultStartup, DoomStartup, HereticStartup, HexenStartup, StrifeStartup).
- **LoadLights**: Прапорець для завантаження світлових ефектів (-1 - використовувати налаштування за замовчуванням).
- **LoadBrightmaps**: Прапорець для завантаження яскравих карт (-1 - використовувати налаштування за замовчуванням).
- **LoadWidescreen**: Прапорець для завантаження широкоекранних текстур (-1 - використовувати налаштування за замовчуванням).

#### Перелік типів запуску
- **DefaultStartup**: Запуск за замовчуванням.
- **DoomStartup**: Запуск у стилі Doom.
- **HereticStartup**: Запуск у стилі Heretic.
- **HexenStartup**: Запуск у стилі Hexen.
- **StrifeStartup**: Запуск у стилі Strife.

### Глобальна змінна GameStartupInfo
```cpp
extern FStartupInfo GameStartupInfo;
```

#### Призначення
Глобальна змінна `GameStartupInfo` містить поточні налаштування запуску гри. Вона використовується різними частинами гри для отримання інформації про поточний режим запуску та налаштування.

## Зв'язки з іншими модулями
Файл `startupinfo.h` пов'язаний з системою запуску гри та інтерфейсом користувача. Він використовується для налаштування візуальних елементів, музики та інших параметрів запуску гри. Структура `FStartupInfo` використовується різними частинами гри для отримання інформації про поточний режим запуску та налаштування.

Цей файл також пов'язаний з інтеграцією з зовнішніми сервісами, такими як Discord та Steam, через відповідні ідентифікатори додатків. Він також впливає на завантаження додаткових ресурсів, таких як світлові ефекти, яскраві карти та широкоекранні текстури.
