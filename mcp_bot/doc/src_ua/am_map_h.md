# am_map.h

**Призначення:**
- Оголошення інтерфейсів та базових класів для автомапи (автоматичної карти рівня).

---

## Опис об'єктів файлу

### Класи
- **DAutomapBase**
  - **Інтерфейс:**
    - `class DAutomapBase : public DObject { ... }`
    - Віртуальні методи:
      - `virtual bool Responder(event_t* ev, bool last) = 0;`
      - `virtual void Ticker(void) = 0;`
      - `virtual void Drawer(int bottom) = 0;`
      - `virtual void NewResolution() = 0;`
      - `virtual void LevelInit() = 0;`
      - `virtual void UpdateShowAllLines() = 0;`
      - `virtual void GoBig() = 0;`
      - `virtual void ResetFollowLocation() = 0;`
      - `virtual int addMark() = 0;`
      - `virtual bool clearMarks() = 0;`
      - `virtual DVector2 GetPosition() = 0;`
      - `virtual void startDisplay() = 0;`
  - **Призначення:** Абстрактний базовий клас для автомапи. Визначає інтерфейс для реалізації автомапи (див. DAutomap у am_map.cpp).
  - **Де використовується:** Наслідується класом DAutomap, використовується у всіх функціях автомапи, створюється через AM_Create.

### Функції
- **AM_StaticInit()**
  - **Інтерфейс:** `void AM_StaticInit();`
  - **Призначення:** Ініціалізує глобальні дані автомапи (стрілки, ключі, маркери).
  - **Де використовується:** При старті рушія.

- **AM_ClearColorsets()**
  - **Інтерфейс:** `void AM_ClearColorsets();`
  - **Призначення:** Скидає кольорові набори автомапи.
  - **Де використовується:** Перезапуск рівня, зміна налаштувань.

- **AM_Create(FLevelLocals *Level)**
  - **Інтерфейс:** `DAutomapBase *AM_Create(FLevelLocals *Level);`
  - **Призначення:** Створює екземпляр автомапи для рівня.
  - **Де використовується:** При завантаженні рівня.

- **AM_Stop()**
  - **Інтерфейс:** `void AM_Stop();`
  - **Призначення:** Вимикає автомапу.
  - **Де використовується:** Вихід з карти.

- **AM_ToggleMap()**
  - **Інтерфейс:** `void AM_ToggleMap();`
  - **Призначення:** Вмикає/вимикає автомапу.
  - **Де використовується:** Клавіша TAB, консольна команда togglemap.

---

**Роль:**
- Визначає інтерфейс для реалізації автомапи, забезпечує базові функції для інтеграції з рушієм, рендерингом, HUD, подіями та навігацією по карті.
