# ct_chat.cpp

**Призначення:**
- Реалізує систему чату для гравців у мультиплеєрі (global/team chat, macros, flood/spam protection, substitution, clipboard, інтеграція з HUD, меню, консоллю).

## Основні структури та змінні
- `TArray<uint8_t> ChatQueue` — буфер введення чату.
- `constexpr int QUEUESIZE = 128` — максимальна довжина повідомлення.
- `constexpr int MessageLimit, MessageThrottleTime, SpamCoolDown` — параметри антиспаму.
- `CVAR (Int, net_chatslowmode, ...)` — затримка між повідомленнями.
- `CVAR (String, chatmacro0-9, ...)` — макроси для швидких повідомлень.
- `CVAR (Bool, chat_substitution, ...)` — підстановка змінних у чаті.
- `CVAR (Int, cl_showchat, ...)` — режим відображення чату.
- `int chatmodeon` — режим чату (0 — вимкнено, 1 — global, 2 — team).
- `uint64_t ChatThrottle, ChatCoolDown` — антиспам-таймери.

## Основні функції
- `void CT_Init();` — ініціалізація чату.
- `void CT_Stop();` — вихід з режиму чату.
- `bool CT_Responder(event_t *ev);` — обробка подій (input, clipboard, макроси, вставка, backspace, enter, escape).
- `void CT_PasteChat(const char *clip);` — вставка з буфера обміну.
- `void CT_Drawer();` — рендеринг рядка чату (HUD, меню, statusbar).
- `static void CT_AddChar(int c);` — додавання символу у буфер.
- `static void CT_BackSpace();` — видалення символу.
- `static void CT_ClearChatMessage();` — очищення буфера.
- `static void ShoveChatStr(const char *str, uint8_t who);` — відправка повідомлення (мережа, substitution, flood protection).
- `static bool DoSubstitution(FString &out, const char *in);` — підстановка змінних ($health, $weapon, $armor, $ammo, $ammocount).

## Консольні команди (CCMD)
- `messagemode` — увімкнути глобальний/командний чат.
- `messagemode2` — увімкнути альтернативний режим чату.
- `say <msg>` — відправити повідомлення у чат.
- `say_team <msg>` — відправити повідомлення у командний чат.

## Інтерфейс
- Інтеграція з HUD, меню, statusbar, консоллю, clipboard, flood/spam protection, substitution.
- Підтримка макросів, підстановки змінних, локалізації, різних режимів чату (глобальний/командний).

## Місця використання
- Викликається з responder-ланцюга (input), HUD/statusbar, консолі, мережевого коду, меню.
- Інтеграція з d_event, d_player, g_game, g_input, sbar, v_draw, v_text, gstrings, VM, clipboard.

---

**Оновлено:** 2025-05-25
