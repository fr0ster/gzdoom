# i_interface.cpp

## Призначення файлу
Файл `i_interface.cpp` містить реалізацію глобальних змінних та функцій, які використовуються для взаємодії між різними частинами ігрового рушія.

## Короткий опис
Цей файл визначає глобальні змінні, які використовуються для керування станом гри, налаштуваннями інтерфейсу та іншими аспектами ігрового рушія. Він також містить перевірку архітектури системи та реалізацію деяких консольних змінних (CVAR).

## Структура файлу
Файл містить:
1. Перевірку архітектури системи (static_assert)
2. Глобальні змінні для керування станом гри
3. Визначення консольних змінних (CVAR)
4. Реалізацію обробника зміни мови

## Основні сутності

### Перевірка архітектури системи
```cpp
static_assert(sizeof(void*) == 8,
    "Only LP64/LLP64 builds are officially supported. "
    "Please do not attempt to build for other platforms; "
    "even if the program succeeds in a MAP01 smoke test, "
    "there are e.g. known visual artifacts "
    "<https://forum.zdoom.org/viewtopic.php?f=7&t=75673> "
    "that lead to a bad user experience.");
```

#### Призначення
Ця перевірка забезпечує, що програма компілюється тільки для 64-бітних архітектур (LP64/LLP64), які офіційно підтримуються. Вона запобігає компіляції для інших платформ, які можуть мати проблеми з візуальними артефактами та іншими проблемами.

### Глобальні змінні
```cpp
FStartupScreen* StartWindow;
SystemCallbacks sysCallbacks;
FString endoomName;
bool batchrun;
float menuBlurAmount;

bool AppActive = true;
int chatmodeon;
gamestate_t gamestate = GS_STARTUP;
bool ToggleFullscreen;
int paused;
bool pauseext;

FStartupInfo GameStartupInfo;
```

#### Призначення
Ці глобальні змінні використовуються для керування різними аспектами ігрового рушія:

- **StartWindow**: Вказівник на об'єкт екрану запуску.
- **sysCallbacks**: Структура з функціями зворотного виклику для системних подій.
- **endoomName**: Ім'я ENDOOM екрану.
- **batchrun**: Прапорець, який вказує, чи запущена гра в пакетному режимі.
- **menuBlurAmount**: Кількість розмиття для меню.
- **AppActive**: Прапорець, який вказує, чи активне вікно додатку.
- **chatmodeon**: Режим чату.
- **gamestate**: Поточний стан гри (GS_STARTUP, GS_LEVEL, GS_INTERMISSION, тощо).
- **ToggleFullscreen**: Прапорець для перемикання повноекранного режиму.
- **paused**: Лічильник паузи.
- **pauseext**: Прапорець зовнішньої паузи.
- **GameStartupInfo**: Інформація про запуск гри.

### Консольні змінні (CVAR)
```cpp
CVAR(Bool, queryiwad, QUERYIWADDEFAULT, CVAR_ARCHIVE | CVAR_GLOBALCONFIG);
CVAR(String, defaultiwad, "", CVAR_ARCHIVE | CVAR_GLOBALCONFIG);
CVAR(Bool, vid_fps, false, 0)

EXTERN_CVAR(Bool, ui_generic)

CUSTOM_CVAR(String, language, "auto", CVAR_ARCHIVE | CVAR_NOINITCALL | CVAR_GLOBALCONFIG)
{
    GStrings.UpdateLanguage(self);
    UpdateGenericUI(ui_generic);
    if (sysCallbacks.LanguageChanged) sysCallbacks.LanguageChanged(self);
}
```

#### Призначення
Ці консольні змінні використовуються для налаштування різних аспектів гри:

- **queryiwad**: Визначає, чи запитувати користувача про вибір IWAD при запуску.
- **defaultiwad**: Визначає IWAD за замовчуванням.
- **vid_fps**: Визначає, чи відображати лічильник FPS.
- **ui_generic**: Зовнішня змінна, яка визначає, чи використовувати загальний інтерфейс користувача.
- **language**: Визначає мову гри. Це користувацька змінна з обробником, який викликається при зміні значення.

#### Обробник зміни мови
```cpp
CUSTOM_CVAR(String, language, "auto", CVAR_ARCHIVE | CVAR_NOINITCALL | CVAR_GLOBALCONFIG)
{
    GStrings.UpdateLanguage(self);
    UpdateGenericUI(ui_generic);
    if (sysCallbacks.LanguageChanged) sysCallbacks.LanguageChanged(self);
}
```

##### Призначення
Цей обробник викликається при зміні значення змінної `language`. Він оновлює мову рядків гри, оновлює загальний інтерфейс користувача та викликає функцію зворотного виклику `LanguageChanged`, якщо вона визначена.

## Зв'язки з іншими модулями
Файл `i_interface.cpp` пов'язаний з багатьма іншими модулями гри:

- **i_interface.h**: Заголовний файл, який містить оголошення структур та функцій, реалізованих в цьому файлі.
- **st_start.h**: Заголовний файл для екрану запуску.
- **gamestate.h**: Заголовний файл, який містить визначення станів гри.
- **startupinfo.h**: Заголовний файл, який містить інформацію про запуск гри.
- **c_cvars.h**: Заголовний файл для системи консольних змінних.
- **gstrings.h**: Заголовний файл для системи рядків гри.
- **version.h**: Заголовний файл, який містить інформацію про версію гри.

Цей файл є центральним для взаємодії між різними частинами ігрового рушія, оскільки він визначає глобальні змінні та консольні змінні, які використовуються в багатьох інших модулях.
