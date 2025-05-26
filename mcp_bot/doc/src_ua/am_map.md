# am_map.cpp

**Призначення:**
- Реалізація автомапи (автоматичної карти рівня): відображення, навігація, маркери, кольори, інтеграція з HUD.

---

## Опис об'єктів файлу

### Глобальні константи та змінні
- **AM_NUMMARKPOINTS**
  - **Інтерфейс:** `enum { AM_NUMMARKPOINTS = 10 };`
  - **Призначення:** Кількість маркерів, які можна поставити на мапі.
  - **Де використовується:** Для масиву маркерів у DAutomap.

- **PLAYERRADIUS, M_ZOOMIN, M_ZOOMOUT, ...**
  - **Інтерфейс:** `static const double PLAYERRADIUS = 16.;` та інші.
  - **Призначення:** Геометричні та масштабні константи для автомапи.
  - **Де використовується:** В обчисленнях відображення, масштабування.

- **automapactive**
  - **Інтерфейс:** `bool automapactive;`
  - **Призначення:** Чи активна автомапа.
  - **Де використовується:** В логіці перемикання карти.

- **AMColors, AMMod, AMModOverlay**
  - **Інтерфейс:** `static AMColorset AMColors;` та інші.
  - **Призначення:** Набори кольорів для різних режимів карти.
  - **Де використовується:** Відображення ліній, об'єктів, фону.

- **MapArrow, CheatMapArrow, CheatKey, EasyKey**
  - **Інтерфейс:** `static TArray<mline_t> MapArrow;` та інші.
  - **Призначення:** Векторна графіка для стрілок, ключів на мапі.
  - **Де використовується:** Відображення гравця, підказок.

---

### Структури
- **fpoint_t, fline_t, mpoint_t, mline_t, islope_t**
  - **Інтерфейс:**
    - `struct fpoint_t { int x, y; }`
    - `struct fline_t { fpoint_t a, b; }`
    - `struct mpoint_t { double x, y; }`
    - `struct mline_t { mpoint_t a, b; }`
    - `struct islope_t { double slp, islp; }`
  - **Призначення:** Геометричні типи для роботи з лініями, точками, нахилами на мапі.
  - **Де використовується:** Відображення, обробка ліній, об'єктів, стрілок.

- **AMColor**
  - **Інтерфейс:** `struct AMColor { uint32_t RGB; ... }`
  - **Призначення:** Представлення кольору для елементів автомапи.
  - **Де використовується:** Відображення ліній, фону, об'єктів.

---

### Класи
- **DAutomapBase**
  - **Інтерфейс:** `class DAutomapBase : public DObject { ... }`
  - **Призначення:** Абстрактний базовий клас для автомапи. Містить інтерфейси для Responder, Ticker, Drawer, LevelInit, GoBig, addMark, clearMarks, GetPosition, startDisplay тощо.
  - **Де використовується:** Наслідується класом DAutomap, використовується у всіх функціях автомапи.

- **DAutomap**
  - **Інтерфейс:** `class DAutomap : public DAutomapBase { ... }`
  - **Призначення:** Основна реалізація автомапи. Містить логіку відображення, масштабування, навігації, маркерів, інтеграції з HUD.
  - **Де використовується:** Створюється через AM_Create, використовується primaryLevel->automap.

---

### Основні функції
- **AM_Create(FLevelLocals *Level)**
  - **Інтерфейс:** `DAutomapBase *AM_Create(FLevelLocals *Level);`
  - **Призначення:** Створює екземпляр автомапи для рівня.
  - **Де використовується:** При завантаженні рівня.

- **AM_ToggleMap()**
  - **Інтерфейс:** `void AM_ToggleMap();`
  - **Призначення:** Вмикає/вимикає автомапу.
  - **Де використовується:** Клавіша TAB, консольна команда togglemap.

- **AM_Stop()**
  - **Інтерфейс:** `void AM_Stop();`
  - **Призначення:** Вимикає автомапу.
  - **Де використовується:** Вихід з карти.

- **AM_ClearColorsets()**
  - **Інтерфейс:** `void AM_ClearColorsets();`
  - **Призначення:** Скидає кольорові набори автомапи.
  - **Де використовується:** Перезапуск рівня, зміна налаштувань.

- **AM_StaticInit()**
  - **Інтерфейс:** `void AM_StaticInit();`
  - **Призначення:** Ініціалізує стрілки, ключі, маркери автомапи.
  - **Де використовується:** При старті рушія.

- **CCMD(am_togglefollow), CCMD(am_togglegrid), CCMD(am_toggletexture), CCMD(am_setmark), CCMD(am_clearmarks), CCMD(am_gobig), CCMD(togglemap), CCMD(am_zoom)**
  - **Інтерфейс:** `CCMD(<name>)`
  - **Призначення:** Консольні команди для керування автомапою (режими, маркери, масштаб, перемикання).
  - **Де використовується:** Викликаються з консолі або через клавіатурні скорочення.

---

### Основні методи DAutomap (частково)
- **Responder(event_t* ev, bool last)** — обробка подій.
- **Ticker()** — оновлення стану автомапи.
- **Drawer(int bottom)** — рендеринг автомапи.
- **LevelInit()** — ініціалізація при старті рівня.
- **GoBig()** — перемикання у великий режим.
- **addMark()** — додавання маркера.
- **clearMarks()** — очищення маркерів.
- **GetPosition()** — отримання позиції гравця на мапі.
- **startDisplay()** — запуск відображення автомапи.
- **minOutWindowScale(), maxOutWindowScale(), changeWindowScale(), changeWindowLoc(), ScrollParchment(), saveScaleAndLoc(), restoreScaleAndLoc(), findMinMaxBoundaries(), calcMinMaxMtoF(), ClipRotatedExtents(), drawThings(), drawWalls(), drawPlayers(), drawKeys(), drawMarks(), drawCrosshair(), drawMline(), drawGrid(), drawSubsectors(), drawSeg(), drawPolySeg(), showSS(), drawLineCharacter(), rotate(), rotatePoint(), clearFB(), clipMline()** — допоміжні методи для рендерингу, навігації, масштабування, обробки геометрії.
  - **Де використовується:** Внутрішня логіка автомапи, рендеринг, взаємодія з HUD.

---

### CVARs (конфігураційні змінні)
- **am_textured, am_linealpha, am_linethickness, am_lineantialiasing, am_thingrenderstyles, am_showsubsector, am_showalllines, am_cheat, am_rotate, am_showsecrets, am_showmonsters, am_showitems, am_showtime, am_showtotaltime, am_showlevelname, am_colorset, am_customcolors, am_map_secrets, am_drawmapback, am_showkeys, am_showtriggerlines, am_showthingsprites, am_showkeys_always, am_emptyspacemargin, am_followplayer, am_portaloverlay, am_showgrid, am_zoomdir, am_markfont, am_markcolor, am_backcolor, am_yourcolor, am_wallcolor, am_secretwallcolor, am_specialwallcolor, am_tswallcolor, am_fdwallcolor, am_cdwallcolor, am_efwallcolor, am_thingcolor, am_gridcolor, am_xhaircolor, am_notseencolor, am_lockedcolor, am_intralevelcolor, am_interlevelcolor, am_secretsectorcolor, am_unexploredsecretcolor, am_thingcolor_friend, am_thingcolor_monster, am_thingcolor_ncmonster, am_thingcolor_item, am_thingcolor_citem, am_portalcolor, am_ovyourcolor**
  - **Інтерфейс:** `CVAR(<type>, <name>, <default>, <flags>)`
  - **Призначення:** Керують виглядом, поведінкою, кольорами автомапи.
  - **Де використовується:** Відображення, логіка автомапи, налаштування користувача.

---

**Роль:**
- Автоматична карта рівня: дозволяє гравцю орієнтуватися, ставити маркери, бачити об'єкти, використовує кольори, інтегрується з HUD, підтримує масштабування, навігацію, консольні команди, налаштування через CVARs.
