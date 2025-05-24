# Діаграми викликів основних підсистем GZDoom (з урахуванням LLM)

## 1. Високорівнева діаграма викликів життєвого циклу

```mermaid
sequenceDiagram
    participant OS as OS
    participant MAIN as main
    participant DOOMMAIN as D_DoomMain
    participant INIT as D_InitGame
    participant GAMELOOP as D_DoomLoop
    participant TICKER as G_Ticker
    participant LLM as LLM
    participant RESP as G_Responder
    participant DISP as D_Display

    OS->>MAIN: Запуск програми
    MAIN->>DOOMMAIN: main викликає D_DoomMain
    DOOMMAIN->>INIT: Ініціалізація гри
    INIT->>GAMELOOP: Запуск головного циклу
    GAMELOOP->>TICKER: Оновлення стану світу
    TICKER->>LLM: Збір і передача даних у LLM
    LLM-->>TICKER: (Опціонально) Вплив LLM на стан
    GAMELOOP->>RESP: Обробка подій
    GAMELOOP->>DISP: Рендеринг кадру
    DISP->>GAMELOOP: Наступна ітерація циклу
```

**Опис:**
- ОС або лаунчер запускає програму, яка входить у main.
- main викликає D_DoomMain, що ініціалізує гру через D_InitGame.
- D_DoomLoop запускає нескінченний цикл, у якому послідовно викликаються G_Ticker (логіка), інтеграція з LLM, G_Responder (input), D_Display (рендер).
- LLM може впливати на стан гри (наприклад, змінювати поведінку AI).

---

## 2. Діаграма викликів для визначення видимості гравця та акторів

```mermaid
sequenceDiagram
    participant PLAYER as player_t
    participant CAMERA as AActorCamera
    participant RENDERER as RendererBSP
    participant ACTOROTHER as AActorOther

    PLAYER->>CAMERA: Доступ до позиції/кута
    CAMERA->>RENDERER: Запит на побудову кадру
    RENDERER->>RENDERER: BSP traversal, визначення видимих секторів
    RENDERER->>ACTOROTHER: Перевірка, чи актор у видимому секторі
    RENDERER-->>CAMERA: Повертає список видимих акторів
```

**Опис:**
- Гравець має посилання на свою "камеру" (AActor).
- Камера передає свою позицію та кут огляду рендереру.
- Рендерер проходить BSP-дерево, визначає видимі області та акторів.
- Список видимих акторів можна використати для інтеграції з LLM.

---

## 3. Діаграма викликів для визначення, хто бачить гравця

```mermaid
sequenceDiagram
    participant ACTORAI as AActorAI
    participant PLAYER as player_t
    participant CAMERAAI as AActorCamera
    participant RAYCASTAI as RaycastAI

    ACTORAI->>RAYCASTAI: Перевірка видимості гравця
    RAYCASTAI->>CAMERAAI: Отримання позиції гравця
    RAYCASTAI->>ACTORAI: Отримання позиції/напрямку актора
    RAYCASTAI-->>ACTORAI: true/false (чи бачить гравця)
```

**Опис:**
- Для кожного актора (наприклад, монстра) AI або логіка виконує трасування променя до позиції гравця.
- Якщо немає перешкод і гравець у полі зору — актор "бачить" гравця.
- Цю інформацію можна зібрати для LLM або для поведінки AI.

---

## 4. Діаграма інтеграції з LLM у циклі гри

```mermaid
sequenceDiagram
    participant TICKER as G_Ticker
    participant COLLECTOR as DataCollector
    participant LLM as LLM
    participant GAME as GameLogic

    TICKER->>COLLECTOR: Збір стану світу, гравця, акторів
    COLLECTOR->>LLM: Формування та передача структури (JSON/інше)
    LLM-->>COLLECTOR: Відповідь (рекомендації, дії, підказки)
    COLLECTOR->>GAME: Вплив на ігровий процес (за потреби)
```

**Опис:**
- Після оновлення стану світу Collector формує структуру для LLM.
- LLM повертає відповідь, яка може впливати на гру (наприклад, змінити поведінку AI, дати підказку гравцю).

---

Документ містить основні діаграми викликів для розуміння архітектури GZDoom та точок інтеграції з LLM. Для деталізації окремих підсистем або додаткових діаграм — звертайтесь!
