# d_main.cpp / d_main.h

**Призначення:**
- Головна точка входу рушія GZDoom.
- Містить функції запуску (`D_DoomMain`), ініціалізації (`D_InitGame`), головного циклу (`D_DoomLoop`), обробки подій (`D_ProcessEvents`).
- Відповідає за життєвий цикл рушія: старт, ініціалізацію, головний цикл, завершення.

---

## Основні функції
- `void D_DoomMain();` — старт рушія, парсинг параметрів командного рядка, ініціалізація ресурсів, запуск головного циклу.
- `void D_InitGame();` — ініціалізація ігрового стану, гравців, рівня, підсистем (input, sound, rendering, scripting).
- `void D_DoomLoop();` — головний цикл: обробка подій, оновлення світу, рендеринг, обробка мережі, виклик responder-ланцюга.
- `void D_ProcessEvents();` — обробка черги подій (input, системні події), виклик responder-функцій (HUD, меню, консоль, ігрова логіка).
- `void D_Quit();` — завершення роботи рушія, очищення ресурсів.
- `void D_ErrorCleanup();` — аварійне завершення, очищення при помилках.
- `void D_Display();` — рендеринг кадру (викликається з циклу).
- `void D_DoAdvanceDemo();` — автоматичний перехід між демо/екранами.

## Глобальні змінні
- `bool demorecording, demoplayback, netgame, multiplayer, paused, ...` — стан демо, мережі, паузи, тощо.
- `gamestate_t gamestate` — поточний стан гри (GS_LEVEL, GS_TITLELEVEL, GS_INTERMISSION, ...).
- `int startmap, startskill, ...` — параметри старту.
- `FString startmapname, ...` — імена карт, ресурсів.

## Інтерфейс та взаємодія
- Всі основні підсистеми рушія (input, rendering, sound, scripting, network, menu, HUD, console) ініціалізуються та координуються через D_DoomMain/D_InitGame/D_DoomLoop.
- Всі responder-функції (HUD, меню, консоль, ігрова логіка) викликаються з D_ProcessEvents.
- Всі події (event_t) надходять у головний цикл через D_ProcessEvents.

## Місця використання
- **Головний цикл рушія:** старт, ініціалізація, обробка input, оновлення світу, рендеринг, завершення.
- **Модулі:** d_event.cpp, g_game.cpp, g_level.cpp, menu.cpp, st_stuff.cpp, events.cpp, c_console.cpp, am_map.cpp, scripting, sound, rendering, network, HUD, statusbar, cutscenes, ZScript.
- **Всі responder-функції:** викликаються з D_ProcessEvents.

---

**Оновлено:** 2025-05-24
