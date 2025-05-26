# st_start.h

## Призначення файлу
Файл `st_start.h` визначає інтерфейс для екрану запуску гри, який відображається під час завантаження.

## Короткий опис
Цей файл містить абстрактний клас `FStartupScreen` та його базову реалізацію `FBasicStartupScreen`, які відповідають за відображення прогресу завантаження гри та мережевих повідомлень. Інтерфейс екрану запуску базується на суміші підходів з ігор Heretic та Hexen, а конкретна реалізація залежить від системи.

## Структура файлу
Файл містить:
1. Абстрактний клас `FStartupScreen`, який визначає інтерфейс для екрану запуску
2. Клас `FBasicStartupScreen`, який є базовою реалізацією `FStartupScreen`
3. Глобальну змінну `StartWindow` та функцію `DeleteStartupScreen` для управління екраном запуску

## Основні сутності

### Клас FStartupScreen
```cpp
class FStartupScreen
{
public:
    static FStartupScreen *CreateInstance(int max_progress);

    FStartupScreen(int max_progress);
    virtual ~FStartupScreen() = default;

    virtual void Progress();
    virtual void AppendStatusLine(const char* status);
    virtual void LoadingStatus(const char* message, int colors);

    virtual void NetInit(const char* message, bool host);
    virtual void NetMessage(const char* message);
    virtual void NetConnect(int client, const char* name, unsigned flags, int status);
    virtual void NetUpdate(int client, int status);
    virtual void NetDisconnect(int client);
    virtual void NetProgress(int cur, int limit);
    virtual void NetDone();
    virtual void NetClose();
    virtual bool ShouldStartNet();
    virtual int GetNetKickClient();
    virtual int GetNetBanClient();
    virtual bool NetLoop(bool (*loopCallback)(void *), void *data);

protected:
    int MaxPos, CurPos, NotchPos;
};
```

#### Призначення
Клас `FStartupScreen` є абстрактним базовим класом, який визначає інтерфейс для екрану запуску гри. Він надає методи для відображення прогресу завантаження та мережевих повідомлень.

#### Поля
- **MaxPos**: Максимальне значення прогресу.
- **CurPos**: Поточне значення прогресу.
- **NotchPos**: Позиція мітки прогресу.

#### Методи
- **CreateInstance(int max_progress)**: Статичний метод, який створює екземпляр екрану запуску з вказаним максимальним значенням прогресу.
- **FStartupScreen(int max_progress)**: Конструктор, який ініціалізує екран запуску з вказаним максимальним значенням прогресу.
- **~FStartupScreen()**: Віртуальний деструктор.
- **Progress()**: Оновлює індикатор прогресу.
- **AppendStatusLine(const char* status)**: Додає рядок статусу до екрану запуску.
- **LoadingStatus(const char* message, int colors)**: Відображає повідомлення про завантаження з вказаними кольорами.
- **NetInit(const char* message, bool host)**: Ініціалізує мережевий екран з вказаним повідомленням та прапорцем хоста.
- **NetMessage(const char* message)**: Відображає мережеве повідомлення.
- **NetConnect(int client, const char* name, unsigned flags, int status)**: Обробляє підключення клієнта.
- **NetUpdate(int client, int status)**: Оновлює статус клієнта.
- **NetDisconnect(int client)**: Обробляє відключення клієнта.
- **NetProgress(int cur, int limit)**: Оновлює індикатор мережевого прогресу.
- **NetDone()**: Завершує мережеву операцію.
- **NetClose()**: Закриває мережевий екран.
- **ShouldStartNet()**: Перевіряє, чи слід запускати мережеву гру.
- **GetNetKickClient()**: Повертає ідентифікатор клієнта для виключення з гри.
- **GetNetBanClient()**: Повертає ідентифікатор клієнта для блокування.
- **NetLoop(bool (*loopCallback)(void *), void *data)**: Виконує цикл мережевої обробки з вказаним зворотним викликом.

### Клас FBasicStartupScreen
```cpp
class FBasicStartupScreen : public FStartupScreen
{
public:
    FBasicStartupScreen(int max_progress);
    ~FBasicStartupScreen();

    void Progress() override;

    void NetInit(const char* message, bool host) override;
    void NetMessage(const char* message) override;
    void NetConnect(int client, const char* name, unsigned flags, int status) override;
    void NetUpdate(int client, int status) override;
    void NetDisconnect(int client) override;
    void NetProgress(int cur, int limit) override;
    void NetDone() override;
    void NetClose() override;
    bool ShouldStartNet() override;
    int GetNetKickClient() override;
    int GetNetBanClient() override;
    bool NetLoop(bool (*loopCallback)(void*), void* data) override;

protected:
    int NetMaxPos, NetCurPos;
};
```

#### Призначення
Клас `FBasicStartupScreen` є базовою реалізацією інтерфейсу `FStartupScreen`. Він надає конкретну реалізацію методів для відображення прогресу завантаження та мережевих повідомлень.

#### Поля
- **NetMaxPos**: Максимальне значення мережевого прогресу.
- **NetCurPos**: Поточне значення мережевого прогресу.

#### Методи
- **FBasicStartupScreen(int max_progress)**: Конструктор, який ініціалізує базовий екран запуску з вказаним максимальним значенням прогресу.
- **~FBasicStartupScreen()**: Деструктор.
- **Progress()**: Оновлює індикатор прогресу.
- **NetInit(const char* message, bool host)**: Ініціалізує мережевий екран з вказаним повідомленням та прапорцем хоста.
- **NetMessage(const char* message)**: Відображає мережеве повідомлення.
- **NetConnect(int client, const char* name, unsigned flags, int status)**: Обробляє підключення клієнта.
- **NetUpdate(int client, int status)**: Оновлює статус клієнта.
- **NetDisconnect(int client)**: Обробляє відключення клієнта.
- **NetProgress(int cur, int limit)**: Оновлює індикатор мережевого прогресу.
- **NetDone()**: Завершує мережеву операцію.
- **NetClose()**: Закриває мережевий екран.
- **ShouldStartNet()**: Перевіряє, чи слід запускати мережеву гру.
- **GetNetKickClient()**: Повертає ідентифікатор клієнта для виключення з гри.
- **GetNetBanClient()**: Повертає ідентифікатор клієнта для блокування.
- **NetLoop(bool (*loopCallback)(void*), void* data)**: Виконує цикл мережевої обробки з вказаним зворотним викликом.

### Глобальні змінні та функції
```cpp
extern FStartupScreen *StartWindow;

inline void DeleteStartupScreen()
{
    if (StartWindow != nullptr)
    {
        delete StartWindow;
        StartWindow = nullptr;
    }
}
```

#### Призначення
- **StartWindow**: Глобальна змінна, яка містить вказівник на поточний екран запуску.
- **DeleteStartupScreen()**: Функція, яка видаляє екран запуску перед завершенням роботи програми.

## Зв'язки з іншими модулями
Файл `st_start.h` пов'язаний з системою завантаження гри та мережевою підсистемою. Він використовується для відображення прогресу завантаження гри та мережевих повідомлень. Конкретна реалізація екрану запуску залежить від системи і може бути різною для різних платформ.

Цей файл є частиною інтерфейсу для екрану запуску, який базується на суміші підходів з ігор Heretic та Hexen. Він надає абстрактний інтерфейс, який може бути реалізований для різних платформ, забезпечуючи єдиний спосіб відображення прогресу завантаження та мережевих повідомлень.
