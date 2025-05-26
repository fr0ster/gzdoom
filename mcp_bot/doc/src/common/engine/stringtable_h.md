# stringtable.h

## Призначення файлу
Файл `stringtable.h` визначає клас `FStringTable`, який управляє списком локалізованих рядків, що зберігаються у wad-файлі, та пов'язані з ним структури.

## Короткий опис
Цей файл містить визначення класу `FStringTable`, який забезпечує систему локалізації для гри. Він дозволяє завантажувати, зберігати та отримувати доступ до локалізованих рядків для різних мов. Також файл визначає допоміжні структури та класи, такі як `TableElement`, `StringMap` та `StringMacro`, які використовуються для організації та управління локалізованими рядками.

## Структура файлу
```cpp
#ifndef __STRINGTABLE_H__
#define __STRINGTABLE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include <stdlib.h>
#include <vector>
#include "basics.h"
#include "zstring.h"
#include "tarray.h"
#include "name.h"

struct TableElement
{
    int filenum;
    FString strings[4];
};

// This public interface is for Dehacked
class StringMap : public TMap<FName, TableElement>
{
public:
    const char *MatchString(const char *string) const;
};

struct StringMacro
{
    FString Replacements[4];
};

class FStringTable
{
public:
    enum : uint32_t
    {
        default_table = MAKE_ID('*', '*', 0, 0),
        global_table = MAKE_ID('*', 0, 0, 0),
        override_table = MAKE_ID('*', '*', '*', 0)
    };

    using LangMap = TMap<uint32_t, StringMap>;
    using StringMacroMap = TMap<FName, StringMacro>;

    // Методи для роботи з локалізованими рядками
    void LoadStrings(FileSys::FileSystem& fileSystem, const char *language);
    void UpdateLanguage(const char* language);
    StringMap GetDefaultStrings();
    void SetOverrideStrings(StringMap & map);
    const char *GetLanguageString(const char *name, uint32_t langtable, int gender = -1) const;
    bool MatchDefaultString(const char *name, const char *content) const;
    const char *CheckString(const char *name, uint32_t *langtable = nullptr, int gender = -1) const;
    const char* GetString(const char* name) const;
    const char* GetString(const FString& name) const;
    bool exists(const char *name);
    void InsertString(int filenum, int langid, FName label, const FString& string);
    void SetDefaultGender(int gender);

private:
    // Приватні поля та методи
    FString activeLanguage;
    StringMacroMap allMacros;
    LangMap allStrings;
    TArray<std::pair<uint32_t, StringMap*>> currentLanguageSet;
    int defaultgender = 0;

    void LoadLanguage(int lumpnum, const char* buffer, size_t size);
    TArray<TArray<FString>> parseCSV(const char* buffer, size_t size);
    bool ParseLanguageCSV(int filenum, const char* buffer, size_t size);
    bool readMacros(const char* buffer, size_t size);
    void DeleteString(int langid, FName label);
    void DeleteForLabel(int filenum, FName label);
    static size_t ProcessEscapes(char *str);

public:
    static FString MakeMacro(const char *str);
    static FString MakeMacro(const char *str, size_t len);
    const char* localize(const char* str);
};

#endif //__STRINGTABLE_H__
```

## Основні сутності

### TableElement
Структура, що зберігає елемент таблиці рядків.

#### Призначення
Зберігає інформацію про локалізований рядок, включаючи номер файлу та варіанти рядка для різних гендерів.

#### Поля
- **filenum**: Номер файлу, з якого був завантажений рядок.
- **strings**: Масив рядків для різних гендерів (до 4 варіантів).

### StringMap
Клас, що представляє карту рядків, індексовану за іменами.

#### Призначення
Забезпечує зберігання та пошук локалізованих рядків за їх іменами.

#### Методи
- **MatchString**: Знаходить рядок, який відповідає заданому рядку.

### StringMacro
Структура, що зберігає макрос для заміни в рядках.

#### Призначення
Зберігає варіанти заміни для макросу в локалізованих рядках.

#### Поля
- **Replacements**: Масив рядків заміни для різних гендерів.

### FStringTable
Клас, що управляє таблицею локалізованих рядків.

#### Призначення
Забезпечує завантаження, зберігання та доступ до локалізованих рядків для різних мов.

#### Константи
- **default_table**: Ідентифікатор таблиці за замовчуванням.
- **global_table**: Ідентифікатор глобальної таблиці.
- **override_table**: Ідентифікатор таблиці перевизначень.

#### Типи
- **LangMap**: Карта, що зіставляє ідентифікатори мов з таблицями рядків.
- **StringMacroMap**: Карта, що зіставляє імена макросів з їх замінами.

#### Методи
- **LoadStrings**: Завантажує рядки з файлової системи для вказаної мови.
- **UpdateLanguage**: Оновлює активну мову.
- **GetDefaultStrings**: Отримує таблицю рядків за замовчуванням.
- **SetOverrideStrings**: Встановлює таблицю перевизначень рядків.
- **GetLanguageString**: Отримує локалізований рядок для вказаної мови та гендеру.
- **MatchDefaultString**: Перевіряє, чи відповідає рядок за замовчуванням заданому вмісту.
- **CheckString**: Перевіряє наявність рядка та повертає його, якщо він існує.
- **GetString**: Отримує локалізований рядок за його ім'ям.
- **exists**: Перевіряє, чи існує рядок з вказаним ім'ям.
- **InsertString**: Вставляє новий рядок у таблицю.
- **SetDefaultGender**: Встановлює гендер за замовчуванням.
- **MakeMacro**: Створює макрос з рядка.
- **localize**: Локалізує рядок, якщо він починається з символу '$'.

#### Приватні поля
- **activeLanguage**: Активна мова.
- **allMacros**: Всі макроси.
- **allStrings**: Всі рядки для всіх мов.
- **currentLanguageSet**: Поточний набір мов.
- **defaultgender**: Гендер за замовчуванням.

#### Приватні методи
- **LoadLanguage**: Завантажує мову з lump.
- **parseCSV**: Розбирає CSV-файл.
- **ParseLanguageCSV**: Розбирає CSV-файл з локалізацією.
- **readMacros**: Читає макроси з файлу.
- **DeleteString**: Видаляє рядок для вказаної мови та мітки.
- **DeleteForLabel**: Видаляє всі рядки для вказаної мітки.
- **ProcessEscapes**: Обробляє escape-послідовності в рядку.

#### Реалізація
Клас `FStringTable` використовує карти для зберігання рядків, індексованих за ідентифікаторами мов та іменами рядків. Він підтримує завантаження рядків з файлів, локалізацію рядків для різних мов та гендерів, а також систему макросів для заміни частин рядків.

#### Зв'язки з іншими модулями
`FStringTable` використовується класом `GStrings` для забезпечення локалізації в грі. Він тісно пов'язаний з системою файлів для завантаження локалізованих рядків та з системою відображення тексту для показу локалізованих повідомлень користувачеві.
