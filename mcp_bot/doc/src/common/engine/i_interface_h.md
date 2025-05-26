# i_interface.h

## Призначення файлу
Файл `i_interface.h` визначає інтерфейс між основним ядром гри та платформо-специфічними або модульними компонентами через систему зворотних викликів (callbacks).

## Короткий опис
Цей файл містить визначення структури `SystemCallbacks`, яка забезпечує механізм зворотних викликів для взаємодії між різними підсистемами гри. Також файл містить декларації глобальних змінних та функцій, які використовуються для керування інтерфейсом користувача та іншими аспектами гри.

## Структура файлу
```cpp
#pragma once

#include "zstring.h"
#include "intrect.h"
#include "name.h"

struct event_t;
class FRenderState;
class FGameTexture;
class FTextureID;
enum EUpscaleFlags : int;
class FConfigFile;
struct FTranslationID;

struct SystemCallbacks
{
    bool (*G_Responder)(event_t* ev);
    bool (*WantGuiCapture)();
    bool (*WantLeftButton)();
    bool (*NetGame)();
    bool (*WantNativeMouse)();
    bool (*CaptureModeInGame)();
    void (*CrashInfo)(char* buffer, size_t bufflen, const char* lfstr);
    void (*PlayStartupSound)(const char* name);
    bool (*IsSpecialUI)();
    bool (*DisableTextureFilter)();
    void (*OnScreenSizeChanged)();
    IntRect(*GetSceneRect)();
    FString(*GetLocationDescription)();
    void (*MenuDim)();
    FString(*GetPlayerName)(int i);
    bool (*DispatchEvent)(event_t* ev);
    bool (*CheckGame)(const char* nm);
    void (*MenuClosed)();
    bool (*CheckMenudefOption)(const char* opt);
    void (*ConsoleToggled)(int state);
    bool (*PreBindTexture)(FRenderState* state, FGameTexture*& tex, EUpscaleFlags& flags, int& scaleflags, int& clampmode, int& translation, int& overrideshader);
    void (*FontCharCreated)(FGameTexture* base, FGameTexture* untranslated);
    void (*ToggleFullConsole)();
    void (*StartCutscene)(bool blockui);
    void (*SetTransition)(int type);
    bool (*CheckCheatmode)(bool printmsg, bool sponly);
    void (*HudScaleChanged)();
    bool (*SetSpecialMenu)(FName& menu, int param);
    void (*OnMenuOpen)(bool makesound);
    void (*LanguageChanged)(const char*);
    bool (*OkForLocalization)(FTextureID, const char*);
    FConfigFile* (*GetConfig)();
    bool (*WantEscape)();
    FTranslationID(*RemapTranslation)(FTranslationID trans);
};

extern SystemCallbacks sysCallbacks;

struct WadStuff
{
    FString Path;
    FString Name;
};

extern FString endoomName;
extern bool batchrun;
extern float menuBlurAmount;
extern bool generic_ui;
extern bool special_i;
extern int paused;
extern bool pauseext;

void UpdateGenericUI(bool cvar);
```

## Основні сутності

### SystemCallbacks
Структура, що містить вказівники на функції зворотного виклику для взаємодії між різними підсистемами гри.

#### Призначення
Забезпечує механізм для комунікації між ядром гри та різними модулями, дозволяючи модулям реагувати на події та запити від ядра.

#### Поля
- **G_Responder**: Обробляє події введення. Це обов'язковий зворотний виклик, без якого система не працюватиме.
- **WantGuiCapture**: Перевіряє, чи GUI повинен захоплювати введення.
- **WantLeftButton**: Перевіряє, чи GUI потребує ліву кнопку миші.
- **NetGame**: Перевіряє, чи гра є мережевою.
- **WantNativeMouse**: Перевіряє, чи потрібно використовувати нативний курсор миші.
- **CaptureModeInGame**: Перевіряє, чи режим захоплення активний під час гри.
- **CrashInfo**: Заповнює буфер інформацією про аварійне завершення.
- **PlayStartupSound**: Відтворює звук запуску.
- **IsSpecialUI**: Перевіряє, чи активний спеціальний інтерфейс користувача.
- **DisableTextureFilter**: Перевіряє, чи потрібно вимкнути фільтрацію текстур.
- **OnScreenSizeChanged**: Викликається при зміні розміру екрану.
- **GetSceneRect**: Повертає прямокутник сцени.
- **GetLocationDescription**: Повертає опис поточного місцезнаходження.
- **MenuDim**: Затемнює екран під час відображення меню.
- **GetPlayerName**: Повертає ім'я гравця за індексом.
- **DispatchEvent**: Розподіляє подію до відповідного обробника.
- **CheckGame**: Перевіряє, чи гра відповідає заданому імені.
- **MenuClosed**: Викликається при закритті меню.
- **CheckMenudefOption**: Перевіряє, чи опція меню доступна.
- **ConsoleToggled**: Викликається при перемиканні консолі.
- **PreBindTexture**: Попередня обробка текстури перед прив'язкою.
- **FontCharCreated**: Викликається при створенні символу шрифту.
- **ToggleFullConsole**: Перемикає повноекранну консоль.
- **StartCutscene**: Запускає відеоролик.
- **SetTransition**: Встановлює тип переходу між рівнями.
- **CheckCheatmode**: Перевіряє, чи активний режим чітів.
- **HudScaleChanged**: Викликається при зміні масштабу HUD.
- **SetSpecialMenu**: Встановлює спеціальне меню.
- **OnMenuOpen**: Викликається при відкритті меню.
- **LanguageChanged**: Викликається при зміні мови.
- **OkForLocalization**: Перевіряє, чи текстура підходить для локалізації.
- **GetConfig**: Повертає об'єкт конфігурації.
- **WantEscape**: Перевіряє, чи потрібно обробляти клавішу Escape.
- **RemapTranslation**: Перевизначає ідентифікатор перекладу.

#### Зв'язки з іншими модулями
Використовується різними підсистемами гри для взаємодії з ядром та іншими модулями.

### WadStuff
Структура для зберігання інформації про WAD-файл.

#### Призначення
Зберігає шлях та ім'я WAD-файлу.

#### Поля
- **Path**: Шлях до WAD-файлу.
- **Name**: Ім'я WAD-файлу.

### Глобальні змінні

#### sysCallbacks
Глобальний екземпляр структури `SystemCallbacks`.

##### Призначення
Зберігає вказівники на функції зворотного виклику, які використовуються для взаємодії між різними підсистемами гри.

#### endoomName
Ім'я ENDOOM-екрану.

##### Призначення
Зберігає ім'я ENDOOM-екрану, який відображається при виході з гри.

#### batchrun
Прапорець пакетного запуску.

##### Призначення
Вказує, чи гра запущена в пакетному режимі.

#### menuBlurAmount
Кількість розмиття меню.

##### Призначення
Визначає ступінь розмиття фону при відображенні меню.

#### generic_ui
Прапорець загального інтерфейсу користувача.

##### Призначення
Вказує, чи використовується загальний інтерфейс користувача.

#### special_i
Прапорець спеціального інтерфейсу.

##### Призначення
Вказує, чи активний спеціальний інтерфейс.

#### paused
Прапорець паузи.

##### Призначення
Вказує, чи гра на паузі.

#### pauseext
Прапорець зовнішньої паузи.

##### Призначення
Вказує, чи гра на паузі через зовнішні фактори.

### UpdateGenericUI
Функція для оновлення загального інтерфейсу користувача.

#### Призначення
Оновлює стан загального інтерфейсу користувача на основі значення змінної.

#### Параметри
- **cvar**: Значення змінної, яке визначає, чи потрібно використовувати загальний інтерфейс користувача.

## Зв'язки з іншими модулями
Файл `i_interface.h` є центральним для взаємодії між різними підсистемами гри. Він забезпечує механізм зворотних викликів, який дозволяє модулям реагувати на події та запити від ядра гри. Цей файл тісно пов'язаний з системою обробки подій, рендерингу, інтерфейсу користувача та іншими ключовими підсистемами гри.
