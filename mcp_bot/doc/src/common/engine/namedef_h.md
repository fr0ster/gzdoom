# namedef.h

## Призначення файлу
Файл `namedef.h` визначає набір стандартних імен (ідентифікаторів), які використовуються в системі імен гри для забезпечення єдиного простору імен та швидкого доступу до часто використовуваних ідентифікаторів.

## Короткий опис
Цей файл містить визначення стандартних імен, які використовуються в різних частинах гри. Імена визначаються за допомогою макросів `xx` та `xy`, які розширюються в інших файлах для створення відповідних структур даних. Файл організований за категоріями імен, такими як базові типи, стилі рендерингу, спеціальні імена для компілятора, канали звуку, імена меню тощо.

## Структура файлу
Файл складається з набору макросів `xx` та `xy`, які визначають стандартні імена. Макрос `xx` використовується для визначення імен, які співпадають з їхніми рядковими представленнями, а макрос `xy` - для визначення імен з іншими рядковими представленнями.

```cpp
// common names

// 'None' must always be the first name.
xx(None)
xx(Null)
xx(_)

// ... (багато інших визначень імен)
```

## Основні категорії імен

### Базові імена
- **None**: Спеціальне ім'я, яке завжди повинно бути першим у списку.
- **Null**: Представляє нульове значення.
- **_**: Спеціальний символ підкреслення.

### Імена класів
- **Super**: Базовий клас.
- **Object**: Базовий об'єкт.
- **Actor**: Клас для акторів у грі.
- **Class**: Представлення класу.
- **Thinker**: Базовий клас для об'єктів, що мають логіку оновлення.
- **VisualThinker**: Клас для об'єктів, що мають візуальне представлення та логіку оновлення.
- **Crosshairs**: Клас для прицілів.

### Стилі рендерингу
- **Normal**: Звичайний стиль рендерингу.
- **SoulTrans**: Стиль рендерингу для душ.
- **OptFuzzy**: Оптимізований нечіткий стиль рендерингу.
- **Add**: Адитивний стиль рендерингу.
- **Shaded**: Затінений стиль рендерингу.
- **AddShaded**: Адитивний затінений стиль рендерингу.
- **TranslucentStencil**: Напівпрозорий стиль рендерингу з використанням трафарету.
- **Shadow**: Стиль рендерингу для тіней.
- **Subtract**: Субтрактивний стиль рендерингу.
- **Subtractive**: Альтернативний субтрактивний стиль рендерингу.
- **FillColor**: Стиль рендерингу для заповнення кольором.
- **ColorBlend**: Стиль рендерингу для змішування кольорів.
- **ColorAdd**: Стиль рендерингу для додавання кольорів.
- **Multiply**: Стиль рендерингу для множення кольорів.

### Спеціальні імена для компілятора
- **Name**: Ім'я.
- **Clamp**: Функція обмеження значення.
- **Abs**: Функція абсолютного значення.
- **Random**, **FRandom**, **Random2**, **RandomPick**, **FRandomPick**, **SetRandomSeed**: Функції для роботи з випадковими числами.
- **CRandom**, **CFRandom**, **CRandom2**, **CRandomPick**, **CFRandomPick**, **CSetRandomSeed**: Функції для роботи з випадковими числами (контекстні версії).
- **BuiltinRandomSeed**, **BuiltinNew**, **GetClass**, **GetParentClass**, **GetClassName**, **IsAbstract**, **GetDefaultByType**: Вбудовані функції для роботи з класами.
- **Floor**, **Exp**, **Log**, **Log10**, **Ceil**, **ACos**, **ASin**, **ATan**, **Cos**, **Sin**, **Tan**, **CosH**, **SinH**, **TanH**, **Round**, **ATan2**, **VectorAngle**, **Sqrt**: Математичні функції.
- **New**: Функція створення нового об'єкта.
- **Static**, **Staticconst**: Модифікатори статичних змінних.

### Канали звуку
- **Auto**: Автоматичний канал звуку.
- **Weapon**: Канал звуку для зброї.
- **Voice**: Канал звуку для голосу.
- **Item**: Канал звуку для предметів.
- **Body**: Канал звуку для тіла.
- **SoundSlot5**, **SoundSlot6**, **SoundSlot7**: Додаткові канали звуку.

### Імена меню
- **menu_cursor**, **menu_choose**, **menu_backup**, **menu_clear**, **menu_dismiss**, **menu_change**, **menu_advance**: Звуки для меню.
- **Mainmenu**, **Episodemenu**, **Skillmenu**, **Startgame**, **StartgameConfirm**, **StartgameConfirmed**, **Loadgamemenu**, **Savegamemenu**, **Optionsmenu**, **OptionsmenuSimple**, **OptionsmenuFull**, **Quitmenu**, **Savemenu**, **EndGameMenu**, **HelpMenu**, **SoundMenu**, **ConfirmPlayerReset**, **JoystickOptions**: Імена меню.
- **OptionMenuItemSubmenu**, **OptionMenuItemCommand**, **OptionMenuItemControlBase**, **OptionMenuItemOptionBase**, **OptionMenuSliderBase**, **OptionMenuFieldBase**, **OptionMenuItemColorPicker**, **OptionMenuItemStaticText**, **OptionMenuItemStaticTextSwitchable**: Типи елементів меню.

### Базові типи
- **Default**: Значення за замовчуванням.
- **sByte**, **Byte**, **Short**, **uShort**, **Int**, **uInt**, **Bool**, **uint8**, **int8**, **uint16**, **int16**, **Float**, **Float32**, **Float64**, **Double**, **String**, **Vector**, **Map**, **MapIterator**, **Array**, **Function**, **Include**, **Sound**, **State**, **Fixed**, **Vector2**, **Vector3**, **Vector4**, **Quat**, **FVector2**, **FVector3**, **FVector4**, **FQuat**: Базові типи даних.
- **let**: Ключове слово для оголошення змінних.
- **BlockThingsIterator**, **BlockLinesIterator**, **ActorIterator**, **ThinkerIterator**: Ітератори для різних типів об'єктів.

### Константи для чисел з плаваючою точкою
- **Min**, **Max**, **Min_Normal**, **Min_Denormal**, **Epsilon**, **Equal_Epsilon**, **NaN**, **Infinity**, **Dig**, **Min_Exp**, **Max_Exp**, **Mant_Dig**, **Min_10_Exp**, **Max_10_Exp**: Константи для чисел з плаваючою точкою.

### Імпліцитні параметри функцій
- **self**: Вказівник на поточний об'єкт.
- **invoker**: Вказівник на об'єкт, що викликав функцію.
- **stateinfo**: Інформація про стан.

### Методи та властивості
- **DamageFunction**, **Length**, **LengthSquared**, **Sum**, **Unit**, **Angle**, **PlusZ**, **ToVector**, **Size**, **Push**, **Insert**, **InsertNew**, **Remove**, **Get**, **GetIfExists**, **GetValue**, **GetKey**, **SetValue**, **CheckKey**, **CheckValue**, **Value**, **Copy**, **Move**, **Voidptr**, **StateLabel**, **SpriteID**, **TextureID**, **TranslationID**, **Overlay**, **IsValid**, **IsNull**, **IsEmpty**, **IsFixed**, **IsKeep**, **Exists**, **SetInvalid**, **SetNull**, **SetEmpty**, **SetFixed**, **SetKeep**, **Key**, **Index**, **Find**, **Call**: Методи та властивості різних класів.

### Канали кольору
- **a**, **r**, **g**, **b**: Канали кольору (альфа, червоний, зелений, синій).

### Компоненти векторів
- **X**, **Y**, **Z**, **W**: Компоненти векторів.
- **XY**, **XYZ**: Групи компонентів векторів.

### Типи для рефлексії
- **Prototype**, **Void**, **Label**, **Pointer**, **Enum**, **StaticArray**, **DynArray**, **Struct**, **ReflectType**, **MessageBoxMenu**: Типи для системи рефлексії.

### Режими видимості
- **Both**, **Physical**, **Visual**: Режими видимості об'єктів.

### Застарілі CVAR-и
- **snd_waterlp**, **snd_output**, **snd_output_format**, **snd_speakermode**, **snd_resampler**, **AlwaysRun**: Застарілі CVAR-и, які використовуються в коді меню.

### Інші імена
- **Color**: Колір.
- **Mididevices**, **Aldevices**, **Alresamplers**: Пристрої та ресемплери для звуку.
- **BuiltinRandom**, **BuiltinRandom2**, **BuiltinFRandom**, **BuiltinNameToClass**, **BuiltinClassCast**, **BuiltinFunctionPtrCast**, **BuiltinFindTranslation**, **HandleDeprecatedFlags**, **CheckDeprecatedFlags**: Функції для сумісності з Decorate.
- **ScreenJobRunner**, **Action**: Інші спеціальні імена.

## Зв'язки з іншими модулями
Файл `namedef.h` використовується системою імен гри для визначення стандартних імен, які використовуються в різних частинах гри. Він тісно пов'язаний з файлом `name.h`, який визначає клас `FName` для роботи з іменами, та з файлом `namedef_custom.h`, який містить додаткові визначення імен, специфічні для конкретного проекту.

Система імен використовується багатьма підсистемами гри, включаючи систему скриптів, систему рендерингу, систему звуку, систему меню тощо. Вона забезпечує єдиний простір імен та швидкий доступ до часто використовуваних ідентифікаторів.
