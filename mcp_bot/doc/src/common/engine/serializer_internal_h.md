# serializer_internal.h

## Призначення файлу
Файл `serializer_internal.h` містить внутрішні структури та функції для системи серіалізації, які використовуються класом `FSerializer` для роботи з форматом JSON.

## Короткий опис
Цей файл визначає допоміжні структури та функції для серіалізації та десеріалізації даних у форматі JSON з використанням бібліотеки RapidJSON. Він містить обгортки для роботи з RapidJSON, які приховують деталі реалізації від глобальних заголовків.

## Структура файлу
Файл містить:
1. Функції для конвертації між Unicode та звичайними рядками
2. Структуру `FJSONObject` для роботи з об'єктами JSON
3. Структуру `FWriter` для запису даних у форматі JSON
4. Структуру `FReader` для читання даних з формату JSON
5. Шаблонні функції для серіалізації вказівників

## Основні сутності

### Функції конвертації рядків
```cpp
const char* UnicodeToString(const char* cc);
const char* StringToUnicode(const char* cc, int size = -1);
```

#### Призначення
Ці функції виконують конвертацію між Unicode та звичайними рядками, що необхідно для правильної обробки текстових даних при серіалізації.

### Структура FJSONObject
```cpp
struct FJSONObject
{
    rapidjson::Value* mObject;
    rapidjson::Value::MemberIterator mIterator;
    int mIndex;

    FJSONObject(rapidjson::Value* v);
};
```

#### Призначення
Структура `FJSONObject` є обгорткою для об'єктів JSON з бібліотеки RapidJSON. Вона спрощує роботу з об'єктами та масивами JSON.

#### Поля
- **mObject**: Вказівник на об'єкт JSON.
- **mIterator**: Ітератор для обходу членів об'єкта JSON.
- **mIndex**: Індекс для обходу елементів масиву JSON.

#### Методи
- **FJSONObject(rapidjson::Value* v)**: Конструктор, який ініціалізує об'єкт JSON.

### Структура FWriter
```cpp
struct FWriter
{
    typedef rapidjson::Writer<rapidjson::StringBuffer, rapidjson::UTF8<> > Writer;
    typedef rapidjson::PrettyWriter<rapidjson::StringBuffer, rapidjson::UTF8<> > PrettyWriter;

    Writer *mWriter1;
    PrettyWriter *mWriter2;
    TArray<bool> mInObject;
    rapidjson::StringBuffer mOutString;
    TArray<DObject *> mDObjects;
    TMap<DObject *, int> mObjectMap;

    FWriter(bool pretty);
    ~FWriter();

    bool inObject() const;
    void StartObject();
    void EndObject();
    void StartArray();
    void EndArray();
    void Key(const char *k);
    void Null();
    void StringU(const char *k, bool encode);
    void String(const char *k);
    void String(const char *k, int size);
    void Bool(bool k);
    void Int(int32_t k);
    void Int64(int64_t k);
    void Uint(uint32_t k);
    void Uint64(int64_t k);
    void Double(double k);
};
```

#### Призначення
Структура `FWriter` є обгорткою для запису даних у форматі JSON з використанням бібліотеки RapidJSON. Вона підтримує як звичайний, так і "красивий" (з відступами) формат JSON.

#### Поля
- **mWriter1**: Вказівник на звичайний JSON-writer.
- **mWriter2**: Вказівник на "красивий" JSON-writer.
- **mInObject**: Стек для відстеження, чи знаходимося ми всередині об'єкта.
- **mOutString**: Буфер для вихідного рядка JSON.
- **mDObjects**: Масив об'єктів DObject для відстеження серіалізованих об'єктів.
- **mObjectMap**: Карта для швидкого пошуку об'єктів DObject.

#### Методи
- **FWriter(bool pretty)**: Конструктор, який створює відповідний writer в залежності від параметра pretty.
- **~FWriter()**: Деструктор, який звільняє ресурси.
- **inObject() const**: Перевіряє, чи знаходимося ми всередині об'єкта.
- **StartObject()**: Починає новий об'єкт JSON.
- **EndObject()**: Закінчує поточний об'єкт JSON.
- **StartArray()**: Починає новий масив JSON.
- **EndArray()**: Закінчує поточний масив JSON.
- **Key(const char *k)**: Записує ключ JSON.
- **Null()**: Записує значення null.
- **StringU(const char *k, bool encode)**: Записує рядок з можливістю кодування.
- **String(const char *k)**: Записує рядок.
- **String(const char *k, int size)**: Записує рядок з вказаною довжиною.
- **Bool(bool k)**: Записує логічне значення.
- **Int(int32_t k)**: Записує 32-бітне ціле число.
- **Int64(int64_t k)**: Записує 64-бітне ціле число.
- **Uint(uint32_t k)**: Записує 32-бітне беззнакове ціле число.
- **Uint64(int64_t k)**: Записує 64-бітне беззнакове ціле число.
- **Double(double k)**: Записує число з плаваючою точкою.

### Структура FReader
```cpp
struct FReader
{
    TArray<FJSONObject> mObjects;
    rapidjson::Document mDoc;
    TArray<DObject *> mDObjects;
    rapidjson::Value *mKeyValue = nullptr;
    bool mObjectsRead = false;

    FReader(const char *buffer, size_t length);
    rapidjson::Value *FindKey(const char *key);
};
```

#### Призначення
Структура `FReader` є обгорткою для читання даних з формату JSON з використанням бібліотеки RapidJSON.

#### Поля
- **mObjects**: Стек об'єктів JSON для відстеження вкладеності.
- **mDoc**: Документ JSON, який містить всі дані.
- **mDObjects**: Масив об'єктів DObject для відстеження десеріалізованих об'єктів.
- **mKeyValue**: Вказівник на поточне значення ключа.
- **mObjectsRead**: Прапорець, який вказує, чи були прочитані об'єкти.

#### Методи
- **FReader(const char *buffer, size_t length)**: Конструктор, який ініціалізує документ JSON з буфера.
- **FindKey(const char *key)**: Знаходить значення за ключем в поточному об'єкті або масиві.

### Шаблонні функції для серіалізації вказівників
```cpp
template<class T>
FSerializer &SerializePointer(FSerializer &arc, const char *key, T *&value, T **defval, T *base, const int64_t count);

template<class T>
FSerializer &SerializePointer(FSerializer &arc, const char *key, T *&value, T **defval, TArray<T> &array);
```

#### Призначення
Ці шаблонні функції серіалізують вказівники на об'єкти, зберігаючи їх як індекси в масиві або відносні зміщення від базового вказівника.

#### Параметри
- **arc**: Посилання на об'єкт `FSerializer`, який виконує серіалізацію.
- **key**: Ключ, під яким об'єкт буде серіалізований.
- **value**: Посилання на вказівник, який потрібно серіалізувати.
- **defval**: Вказівник на значення за замовчуванням.
- **base**: Базовий вказівник для обчислення відносного зміщення.
- **count**: Кількість елементів у масиві.
- **array**: Масив, з якого береться базовий вказівник та кількість елементів.

#### Особливості реалізації
Функції серіалізують вказівники як індекси в масиві, перевіряючи, чи знаходиться індекс в допустимих межах. Якщо індекс виходить за межі масиву, виводиться повідомлення про помилку, і вказівник встановлюється в nullptr.

## Зв'язки з іншими модулями
Файл `serializer_internal.h` тісно пов'язаний з системою серіалізації гри, зокрема з файлом `serializer.h`, який визначає основні функції та класи для серіалізації об'єктів. Він також використовує бібліотеку RapidJSON для роботи з форматом JSON.

Цей файл є внутрішнім для системи серіалізації і не повинен використовуватися безпосередньо іншими модулями гри. Замість цього, інші модулі повинні використовувати інтерфейс, наданий класом `FSerializer`.
