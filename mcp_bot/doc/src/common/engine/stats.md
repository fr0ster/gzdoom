# stats.cpp

## Призначення файлу
Файл `stats.cpp` містить реалізацію класу `FStat`, який відповідає за збір та відображення статистичних даних про продуктивність гри.

## Короткий опис
Цей файл реалізує функціональність, оголошену в `stats.h`, для системи статистики продуктивності. Він включає методи для реєстрації, активації/деактивації та відображення статистичних даних, а також консольну команду для керування статистикою.

## Структура файлу
Файл містить:
1. Реалізацію методів класу `FStat`
2. Консольну команду `stat` для керування статистикою

## Основні сутності

### Реалізація класу FStat
```cpp
FStat *FStat::FirstStat;

FStat::FStat(const char *name)
{
    m_Name = name;
    m_Active = false;
    m_Next = FirstStat;
    FirstStat = this;
}

FStat::~FStat()
{
    FStat **prev = &FirstStat;

    while (*prev && *prev != this)
        prev = &((*prev)->m_Next)->m_Next;

    if (*prev == this)
        *prev = m_Next;
}

FStat *FStat::FindStat(const char *name)
{
    FStat *stat = FirstStat;

    while (stat && stricmp(name, stat->m_Name))
        stat = stat->m_Next;

    return stat;
}

void FStat::ToggleStat(const char *name)
{
    FStat *stat = FindStat(name);
    if (stat)
        stat->ToggleStat();
    else
        Printf("Unknown stat: %s\n", name);
}

void FStat::EnableStat(const char* name, bool on)
{
    FStat* stat = FindStat(name);
    if (stat)
        stat->m_Active = on;
    else
        Printf("Unknown stat: %s\n", name);
}

void FStat::ToggleStat()
{
    m_Active = !m_Active;
}

void FStat::PrintStat(F2DDrawer *drawer)
{
    int textScale = active_con_scale(drawer);

    int fontheight = NewConsoleFont->GetHeight() + 1;
    int y = drawer->GetHeight() / textScale;
    int count = 0;

    for (FStat *stat = FirstStat; stat != NULL; stat = stat->m_Next)
    {
        if (stat->m_Active)
        {
            FString stattext(stat->GetStats());

            if (stattext.Len() > 0)
            {
                y -= fontheight;    // there's at least one line of text
                for (unsigned i = 0; i < stattext.Len()-1; i++)
                {
                    // Count number of linefeeds but ignore terminating ones.
                    if (stattext[i] == '\n') y -= fontheight;
                }
                DrawText(drawer, NewConsoleFont, CR_GREEN, 5 / textScale, y, stattext.GetChars(),
                    DTA_VirtualWidth, twod->GetWidth() / textScale,
                    DTA_VirtualHeight, twod->GetHeight() / textScale,
                    DTA_KeepRatio, true, TAG_DONE);
                count++;
            }
        }
    }
}

void FStat::DumpRegisteredStats()
{
    FStat *stat = FirstStat;

    Printf("Available stats:\n");
    while (stat)
    {
        Printf(" %c%s\n", stat->m_Active ? '*' : ' ', stat->m_Name);
        stat = stat->m_Next;
    }
}
```

#### Призначення
Реалізація класу `FStat` забезпечує функціональність для реєстрації, активації/деактивації та відображення статистичних даних про продуктивність гри.

#### Методи
- **FStat(const char *name)**: Конструктор, який реєструє статистичні дані з вказаною назвою, додаючи їх до зв'язаного списку.
- **~FStat()**: Деструктор, який видаляє статистичні дані зі зв'язаного списку.
- **FindStat(const char *name)**: Знаходить статистичні дані за назвою, виконуючи пошук без урахування регістру.
- **ToggleStat(const char *name)**: Вмикає або вимикає статистичні дані за назвою.
- **EnableStat(const char* name, bool on)**: Встановлює стан активності статистичних даних за назвою.
- **ToggleStat()**: Вмикає або вимикає поточні статистичні дані.
- **PrintStat(F2DDrawer *drawer)**: Відображає всі активні статистичні дані на екрані.
- **DumpRegisteredStats()**: Виводить список всіх зареєстрованих статистичних даних у консоль.

#### Особливості реалізації
- Клас `FStat` використовує зв'язаний список для зберігання всіх зареєстрованих статистичних даних.
- Метод `PrintStat` відображає статистичні дані на екрані, використовуючи `F2DDrawer` та `NewConsoleFont`.
- Метод `DumpRegisteredStats` виводить список всіх зареєстрованих статистичних даних у консоль, позначаючи активні дані зірочкою.

### Консольна команда stat
```cpp
CCMD(stat)
{
    if (argv.argc() != 2)
    {
        Printf("Usage: stat <statistics>\n");
        FStat::DumpRegisteredStats();
    }
    else
    {
        FStat::ToggleStat(argv[1]);
    }
}
```

#### Призначення
Консольна команда `stat` дозволяє вмикати або вимикати статистичні дані через консоль гри.

#### Параметри
- **statistics**: Назва статистичних даних, які потрібно увімкнути або вимкнути.

#### Особливості реалізації
- Якщо команда викликається без параметрів або з неправильною кількістю параметрів, виводиться підказка з використання та список всіх зареєстрованих статистичних даних.
- Якщо команда викликається з правильною кількістю параметрів, вмикаються або вимикаються вказані статистичні дані.

## Зв'язки з іншими модулями
Файл `stats.cpp` пов'язаний з системою вимірювання продуктивності та відображення статистичних даних. Він використовується різними частинами гри для збору та відображення статистичних даних про продуктивність.

Клас `FStat` використовується для реєстрації та відображення статистичних даних, а консольна команда `stat` дозволяє керувати статистикою через консоль гри.

Файл також пов'язаний з системою відображення, оскільки метод `PrintStat` використовує класи `F2DDrawer` та `NewConsoleFont` для відображення статистичних даних на екрані.
