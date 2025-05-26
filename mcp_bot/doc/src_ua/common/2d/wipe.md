# wipe.cpp — Документація

**Файл:** `src/common/2d/wipe.cpp`

## Призначення

Реалізація ефектів екранних переходів (screen wipes) у GZDoom. Забезпечує плавні переходи між ігровими станами (наприклад, між рівнями, меню, інтермісіями) за допомогою різних візуальних ефектів: Melt, Burn, Crossfade (Fade).

## Основні класи та структури

### Wiper (базовий клас)
- **Призначення:** Абстрактний інтерфейс для всіх wipe-ефектів.
- **Поля:**
  - `FGameTexture* startScreen, *endScreen` — текстури початкового та кінцевого стану екрану.
- **Методи:**
  - `virtual ~Wiper()` — деструктор, очищає текстури.
  - `virtual bool Run(int ticks) = 0` — виконує крок анімації wipe.
  - `virtual bool RunInterpolated(double ticks)` — інтерпольований крок (за замовчуванням true).
  - `virtual bool Interpolatable()` — чи підтримує інтерполяцію (false).
  - `virtual void SetTextures(FGameTexture*, FGameTexture*)` — встановлює текстури.
  - `static Wiper* Create(int type)` — фабричний метод для створення wipe за типом.
- **Використання:** Базовий клас для всіх wipe-ефектів. Використовується у функції `PerformWipe`.

### Wiper_Crossfade (Fade)
- **Призначення:** Ефект плавного перетікання (fade/crossfade) між екранами.
- **Поля:**
  - `float Clock` — лічильник часу анімації.
- **Методи:**
  - `bool Run(int ticks)` — малює обидва екрани з альфа-змішуванням.
  - `bool RunInterpolated(double ticks)` — інтерпольований fade.
  - `bool Interpolatable()` — повертає true.
- **Використання:** Вибирається як wipe_Fade у `Wiper::Create`.

### Wiper_Melt
- **Призначення:** Ефект "розплавлення" (melt) — вертикальні смуги старого екрану сповзають вниз, відкриваючи новий.
- **Поля:**
  - `double y[WIDTH]` — масив позицій для кожної смуги.
- **Методи:**
  - `bool Run(int ticks)` — крок анімації melt.
  - `bool RunInterpolated(double ticks)` — інтерпольований melt.
  - `bool Interpolatable()` — повертає true.
- **Використання:** Вибирається як wipe_Melt у `Wiper::Create`.

### Wiper_Burn
- **Призначення:** Ефект "вигоряння" (burn) — екран зникає у вигляді палаючого вогню.
- **Поля:**
  - `uint8_t BurnArray[WIDTH * (HEIGHT + 5)]` — буфер для ефекту вогню.
  - `FBurnTexture *BurnTexture` — текстура для burn.
  - `int Density, BurnTime` — параметри анімації.
- **Методи:**
  - `~Wiper_Burn()` — очищення ресурсів.
  - `bool Run(int ticks)` — крок burn.
  - `void SetTextures(FGameTexture*, FGameTexture*)` — ініціалізація текстур.
- **Використання:** Вибирається як wipe_Burn у `Wiper::Create`.

### FBurnTexture
- **Призначення:** Текстура для burn-ефекту, зберігає буфер RGBA.
- **Поля:**
  - `TArray<uint32_t> WorkBuffer` — буфер пікселів.
- **Методи:**
  - `GetBgraBitmap`, `GetBuffer` — доступ до буфера.
- **Використання:** Внутрішньо у Wiper_Burn.

## Глобальні функції

### wipe_CalcBurn
- **Призначення:** Алгоритм генерації "вогню" для burn-ефекту.
- **Інтерфейс:** `int wipe_CalcBurn(uint8_t *burnarray, int width, int height, int density)`
- **Використання:** Викликається у Wiper_Burn::Run для оновлення burn-буфера.

### PerformWipe
- **Призначення:** Головна функція виконання wipe-ефекту між двома зображеннями.
- **Інтерфейс:** `void PerformWipe(FTexture* startimg, FTexture* endimg, int wipe_type, bool stopsound, std::function<void()> overlaydrawer)`
- **Опис:**
  - Створює відповідний Wiper через `Wiper::Create`.
  - Викликає Run/RunInterpolated у циклі до завершення wipe.
  - Малює оверлеї, оновлює екран, керує паузою звуку та часом.
- **Використання:** Викликається у D_Display (d_main.cpp) при зміні стану гри.

## Глобальні змінні, CVARs, консольні команди
- **CVAR:** `cl_capfps` — впливає на режим інтерполяції wipe.
- **Використання:** Визначає, чи використовувати RunInterpolated чи Run.

## Інші деталі
- **wipe.h** — містить enum типів wipe (wipe_None, wipe_Melt, wipe_Burn, wipe_Fade) та оголошення PerformWipe.
- **Використання у коді:**
  - D_Display (d_main.cpp): визначає, коли і який wipe виконувати, викликає PerformWipe.
  - Інтермісії, cutscenes, меню — через PerformWipe для плавних переходів.
  - Всі wipe-ефекти використовують DrawTexture, twod, screen для малювання.

## Де використовується
- **D_Display (d_main.cpp):** основний виклик PerformWipe при зміні стану гри.
- **Інтермісії, меню, cutscenes:** для плавних переходів.
- **wipe.h:** оголошення інтерфейсу.
- **Використання wipe_type/wipetype (CVAR, MAPINFO):** вибір типу wipe.

## Коротко про алгоритми
- **Melt:** масив y[] визначає, наскільки "сповзла" кожна вертикальна смуга; старий екран малюється поверх нового у відповідних областях.
- **Burn:** burnarray моделює "вогонь"; burntexture малюється поверх нового екрану, поступово відкриваючи його.
- **Crossfade:** просте альфа-змішування двох текстур.

## Висновок
Файл `wipe.cpp` — ключовий для візуальних переходів у GZDoom, містить розширювану архітектуру для різних типів wipe-ефектів, використовується у всіх основних переходах між станами гри.
