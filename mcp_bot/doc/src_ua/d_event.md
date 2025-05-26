# d_event.h / d_event.cpp

**Призначення:**
- Описує структури, типи та інтерфейси для обробки всіх подій у рушії: input (клавіатура, миша, джойстик), системні, мережеві, UI, внутрішні ігрові дії.
- Є центральною точкою для передачі подій у головний цикл, обробки input, взаємодії з іншими модулями (HUD, меню, консоль, ігрова логіка).

---

## Основні структури та типи

### struct event_t
- **Призначення:** універсальна структура події (input, системна, мережа, UI).
- **Поля:**
  - `uint8_t type` — тип події (див. EGenericEvent)
  - `uint8_t subtype` — підтип (для EV_GUI_Event: EGUIEvent)
  - `int16_t data1, data2, data3` — додаткові дані (коди клавіш, кнопок, модифікатори)
  - `float x, y` — координати/зміщення миші/джойстика
- **Використання:** передається у всі responder-функції рушія, використовується для обробки input, UI, мережевих подій.

### enum EGenericEvent
- **Типи подій:**
  - `EV_None` — відсутня
  - `EV_KeyDown`, `EV_KeyUp` — натискання/відпускання клавіші
  - `EV_Mouse` — рух/кнопки миші
  - `EV_GUI_Event` — подія UI (див. EGUIEvent)
  - `EV_DeviceChange` — зміна пристрою вводу

### enum EGUIEvent
- **Типи UI-подій:**
  - `EV_GUI_None`, `EV_GUI_KeyDown`, `EV_GUI_KeyRepeat`, `EV_GUI_KeyUp`, `EV_GUI_Char` — клавіатурні події
  - `EV_GUI_MouseMove`, `EV_GUI_LButtonDown`, `EV_GUI_LButtonUp`, ... — мишачі події (див. d_gui.h)

### enum buttoncode_t
- **Бітові коди дій гравця:**
  - `BT_ATTACK`, `BT_USE`, `BT_JUMP`, `BT_CROUCH`, `BT_TURN180`, `BT_ALTATTACK`, `BT_RELOAD`, `BT_ZOOM`, ...
  - Додаткові: `BT_SPEED`, `BT_STRAFE`, `BT_MOVERIGHT`, `BT_MOVELEFT`, `BT_BACK`, `BT_FORWARD`, `BT_RIGHT`, `BT_LEFT`, `BT_LOOKUP`, `BT_LOOKDOWN`, `BT_MOVEUP`, `BT_MOVEDOWN`, `BT_SHOWSCORES`, `BT_USER1`-`BT_USER4`, `BT_RUN`.
- **Використання:** для кодування стану кнопок у input-подіях.

### enum gameaction_t
- **Типи ігрових дій:**
  - `ga_nothing`, `ga_loadlevel`, `ga_newgame`, `ga_recordgame`, `ga_loadgame`, `ga_savegame`, `ga_playdemo`, `ga_completed`, `ga_slideshow`, `ga_worlddone`, `ga_screenshot`, `ga_togglemap`, `ga_fullconsole`, `ga_resumeconversation`, `ga_intro`, `ga_intermission`, `ga_titleloop`, `ga_mapwarp` та інші.
- **Глобальна змінна:** `gameaction` — поточна дія рушія.

### struct FUiEvent
- **Призначення:** обгортка для UI-подій (GUI) для ZScript.
- **Поля:**
  - `EGUIEvent Type`, `FString KeyString`, `int KeyChar`, `int MouseX`, `int MouseY`, `bool IsShift`, `IsCtrl`, `IsAlt`
- **Конструктор:** `FUiEvent(const event_t *ev)` — ініціалізує з event_t.

### struct FInputEvent
- **Призначення:** обгортка для input-подій (клавіатура, миша) для ZScript.
- **Поля:**
  - `EGenericEvent Type`, `int KeyScan`, `FString KeyString`, `int KeyChar`, `int MouseX`, `int MouseY`
- **Конструктор:** `FInputEvent(const event_t *ev)`

---

## Глобальні змінні
- `event_t events[MAXEVENTS]` — кільцева черга подій
- `int eventhead, eventtail` — індекси черги
- `extern gameaction_t gameaction` — поточна дія рушія

## Основні функції
- `void D_PostEvent(event_t* ev)` — додати подію у чергу
- `void D_ProcessEvents(void)` — обробити всі події з черги (головний цикл)
- `void D_RemoveNextCharEvent()` — видалити наступну char-подію (для меню)
- `void PostMouseMove(int x, int y)` — створити подію руху миші
- `void D_Render(std::function<void()> action, bool interpolate)` — рендеринг з урахуванням input

---

## Місця використання
- **Головний цикл рушія:** обробка input, UI, системних подій, передача у HUD, меню, консоль, ігрову логіку.
- **Модулі:** `st_stuff.cpp` (ST_Responder), `g_game.cpp`, `menu.cpp`, `c_console.cpp`, `am_map.cpp`, `events.cpp`, `d_gui.h`, `i_interface.h`, `d_eventbase.h`, ZScript-інтерфейс.
- **Всі responder-функції:** приймають event_t* як аргумент для обробки input/UI.

---

**Оновлено:** 2025-05-24
