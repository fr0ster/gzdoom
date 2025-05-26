# stringtable.cpp

## Призначення файлу
Файл `stringtable.cpp` містить реалізацію класу `FStringTable`, який відповідає за завантаження, зберігання та керування локалізованими рядками тексту в грі.

## Короткий опис
Цей файл реалізує систему локалізації тексту, яка дозволяє грі підтримувати кілька мов. Він забезпечує завантаження рядків з файлів LANGUAGE, обробку макросів, підтримку CSV-форматів та доступ до локалізованих рядків під час виконання гри.

## Структура файлу
Файл містить:
1. Реалізацію методів класу `FStringTable`
2. Функції для обробки CSV-файлів
3. Функції для обробки escape-послідовностей
4. Методи для пошуку та отримання локалізованих рядків

## Основні сутності

### Клас FStringTable
```cpp
class FStringTable
{
public:
    void LoadStrings(FileSys::FileSystem& fileSystem, const char *language);
    void UpdateLanguage(const char *language);
    const char *GetString(const char *name) const;
    const char *CheckString(const char *name, uint32_t *langtable, int gender) const;
    const char *GetLanguageString(const char *name, uint32_t langtable, int gender = -1) const;
    bool MatchDefaultString(const char *name, const char *content) const;
    bool exists(const char *name);
    // ...
};
```

#### Призначення
Клас `FStringTable` відповідає за завантаження, зберігання та керування локалізованими рядками тексту в грі. Він підтримує кілька мов, гендерні варіанти тексту та макроси для заміни тексту.

#### Методи
- **LoadStrings(FileSys::FileSystem& fileSystem, const char *language)**: Завантажує локалізовані рядки з файлової системи для вказаної мови.
- **UpdateLanguage(const char *language)**: Оновлює активну мову.
- **GetString(const char *name)**: Повертає локалізований рядок за його назвою або саму назву, якщо рядок не знайдено.
- **CheckString(const char *name, uint32_t *langtable, int gender)**: Шукає рядок за назвою та повертає його значення.
- **GetLanguageString(const char *name, uint32_t langtable, int gender)**: Повертає рядок для конкретної мови без спроби заміни.
- **MatchDefaultString(const char *name, const char *content)**: Перевіряє, чи відповідає рядок за замовчуванням вказаному вмісту.
- **exists(const char *name)**: Перевіряє, чи існує рядок з вказаною назвою в таблицях за замовчуванням.

### Метод LoadStrings
```cpp
void FStringTable::LoadStrings(FileSys::FileSystem& fileSystem, const char *language)
{
    int lastlump, lump;

    allStrings.Clear();
    lastlump = 0;
    while ((lump = fileSystem.FindLump("LMACROS", &lastlump)) != -1)
    {
        auto lumpdata = fileSystem.ReadFile(lump);
        readMacros(lumpdata.string(), lumpdata.size());
    }

    lastlump = 0;
    while ((lump = fileSystem.FindLump("LANGUAGE", &lastlump)) != -1)
    {
        auto lumpdata = fileSystem.ReadFile(lump);
        auto filenum = fileSystem.GetFileContainer(lump);

        if (!ParseLanguageCSV(filenum, lumpdata.string(), lumpdata.size()))
            LoadLanguage(filenum, lumpdata.string(), lumpdata.size());
    }
    UpdateLanguage(language);
    allMacros.Clear();
}
```

#### Призначення
Метод `LoadStrings` завантажує локалізовані рядки та макроси з файлової системи.

#### Особливості реалізації
- Спочатку завантажуються макроси з файлів "LMACROS".
- Потім завантажуються локалізовані рядки з файлів "LANGUAGE".
- Підтримуються два формати файлів: CSV та власний формат LANGUAGE.
- Після завантаження всіх рядків оновлюється активна мова.

### Метод parseCSV
```cpp
TArray<TArray<FString>> FStringTable::parseCSV(const char* buffer, size_t size)
{
    // ...
}
```

#### Призначення
Метод `parseCSV` розбирає CSV-дані та повертає їх у вигляді двовимірного масиву рядків.

#### Особливості реалізації
- Підтримує цитування рядків.
- Обробляє екрановані лапки всередині цитованих рядків.
- Ігнорує символи повернення каретки (CR).
- Обробляє рядки без завершального символу нового рядка.

### Метод readMacros
```cpp
bool FStringTable::readMacros(const char* buffer, size_t size)
{
    auto data = parseCSV(buffer, size);

    allMacros.Clear();
    for (unsigned i = 1; i < data.Size(); i++)
    {
        auto macroname = data[i][0];
        FName name = macroname.GetChars();

        StringMacro macro;

        for (int k = 0; k < 4; k++)
        {
            macro.Replacements[k] = data[i][k+2];
        }
        allMacros.Insert(name, macro);
    }
    return true;
}
```

#### Призначення
Метод `readMacros` зчитує макроси з CSV-даних та зберігає їх у внутрішній структурі.

#### Особливості реалізації
- Очищає існуючі макроси.
- Зчитує назву макросу з першого стовпця.
- Зчитує заміни для різних гендерів з наступних стовпців.
- Зберігає макроси у хеш-таблиці для швидкого доступу.

### Метод ParseLanguageCSV
```cpp
bool FStringTable::ParseLanguageCSV(int filenum, const char* buffer, size_t size)
{
    // ...
}
```

#### Призначення
Метод `ParseLanguageCSV` розбирає CSV-файл з локалізованими рядками.

#### Особливості реалізації
- Перевіряє, чи є файл CSV-файлом з локалізацією.
- Визначає стовпці з ідентифікаторами та фільтрами.
- Визначає стовпці з різними мовами.
- Обробляє фільтри для ігор.
- Додає рядки до відповідних таблиць мов.

### Метод LoadLanguage
```cpp
void FStringTable::LoadLanguage(int lumpnum, const char* buffer, size_t size)
{
    // ...
}
```

#### Призначення
Метод `LoadLanguage` завантажує локалізовані рядки з файлу у власному форматі LANGUAGE.

#### Особливості реалізації
- Обробляє блоки мов, позначені квадратними дужками.
- Обробляє умовні блоки з `$ifgame`.
- Обробляє визначення рядків у форматі `NAME = "Value";`.
- Обробляє escape-послідовності в рядках.
- Додає рядки до відповідних таблиць мов.

### Метод InsertString
```cpp
void FStringTable::InsertString(int filenum, int langid, FName label, const FString &string)
{
    // ...
}
```

#### Призначення
Метод `InsertString` додає локалізований рядок до таблиці рядків.

#### Особливості реалізації
- Обробляє макроси у форматі `@[MACRO]`.
- Зберігає рядок для різних гендерів.
- Зберігає номер файлу для визначення пріоритету.

### Метод UpdateLanguage
```cpp
void FStringTable::UpdateLanguage(const char *language)
{
    // ...
}
```

#### Призначення
Метод `UpdateLanguage` оновлює активну мову та створює список таблиць рядків для пошуку.

#### Особливості реалізації
- Зберігає активну мову.
- Створює ідентифікатор мови з коду мови.
- Додає таблиці рядків до списку пошуку в порядку пріоритету.

### Метод ProcessEscapes
```cpp
size_t FStringTable::ProcessEscapes(char *iptr)
{
    // ...
}
```

#### Призначення
Метод `ProcessEscapes` обробляє escape-послідовності в рядку.

#### Особливості реалізації
- Обробляє стандартні escape-послідовності: `\n`, `\r`, `\t`.
- Обробляє спеціальні escape-послідовності: `\c` для кольору тексту.
- Обробляє шістнадцяткові escape-послідовності: `\xHH`.
- Ігнорує escape-послідовності нового рядка.

### Метод CheckString
```cpp
const char *FStringTable::CheckString(const char *name, uint32_t *langtable, int gender) const
{
    // ...
}
```

#### Призначення
Метод `CheckString` шукає рядок за назвою та повертає його значення.

#### Особливості реалізації
- Перевіряє, чи існує рядок з вказаною назвою.
- Шукає рядок у всіх активних таблицях мов.
- Враховує гендер для вибору правильного варіанту рядка.
- Підтримує рекурсивні посилання на інші рядки через `$$`.

### Глобальний об'єкт GStrings
```cpp
FStringTable GStrings;
```

#### Призначення
Глобальний об'єкт `GStrings` є екземпляром класу `FStringTable`, який використовується для доступу до локалізованих рядків у всій грі.

## Зв'язки з іншими модулями
Файл `stringtable.cpp` пов'язаний з системою локалізації гри та забезпечує доступ до локалізованих рядків для всіх інших модулів. Він використовується для:

- Завантаження локалізованих рядків з файлів
- Зберігання та керування локалізованими рядками
- Надання доступу до локалізованих рядків під час виконання гри
- Підтримки кількох мов та гендерних варіантів тексту

Цей файл тісно пов'язаний з `stringtable.h`, який містить оголошення класу `FStringTable`. Він також використовує функціональність з інших модулів, таких як `cmdlib.h`, `filesystem.h`, `sc_man.h`, `printf.h` та `i_interface.h`.
