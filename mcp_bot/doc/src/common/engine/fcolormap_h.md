# fcolormap.h

## Призначення файлу
Файл `fcolormap.h` визначає структуру `FColormap`, яка використовується для управління кольоровими ефектами, такими як освітлення, затемнення та туман у рендерингу гри.

## Короткий опис
Цей файл містить визначення структури `FColormap`, яка зберігає інформацію про кольорові ефекти, що застосовуються до об'єктів у грі. Структура включає параметри для контролю кольору світла, кольору затемнення, насиченості кольорів, фактору змішування та щільності туману.

## Структура файлу
```cpp
#pragma once

#include <stdint.h>
#include "palentry.h"

// for internal use
struct FColormap
{
    PalEntry        LightColor;     // a is saturation (0 full, 31=b/w, other=custom colormap)
    PalEntry        FadeColor;      // a is fadedensity>>1
    uint8_t         Desaturation;
    uint8_t         BlendFactor;    // This is for handling Legacy-style colormaps which use a different formula to calculate how the color affects lighting.
    uint16_t        FogDensity;

    // Методи для роботи з кольоровими ефектами
    void Clear();
    void MakeWhite();
    void ClearColor();
    void CopyLight(FColormap &from);
    void CopyFog(FColormap &from);
    void Decolorize();
    bool operator == (const FColormap &other);
    bool operator != (const FColormap &other);
};
```

## Основні сутності

### FColormap
Структура для зберігання та управління кольоровими ефектами.

#### Призначення
Надає інтерфейс для управління кольоровими ефектами, такими як освітлення, затемнення та туман, які застосовуються до об'єктів у грі.

#### Поля
- **LightColor**: Колір світла. Альфа-компонент використовується для насиченості (0 - повна насиченість, 31 - чорно-білий, інші значення - користувацька кольорова карта).
- **FadeColor**: Колір затемнення. Альфа-компонент використовується для щільності затемнення (fadedensity>>1).
- **Desaturation**: Рівень десатурації (знебарвлення) кольорів.
- **BlendFactor**: Фактор змішування для обробки Legacy-стилю кольорових карт, які використовують іншу формулу для розрахунку впливу кольору на освітлення.
- **FogDensity**: Щільність туману.

#### Методи
- **Clear()**: Скидає всі параметри до значень за замовчуванням.
- **MakeWhite()**: Встановлює колір світла на білий.
- **ClearColor()**: Скидає колір світла, фактор змішування та десатурацію.
- **CopyLight(FColormap &from)**: Копіює параметри світла з іншого об'єкта FColormap.
- **CopyFog(FColormap &from)**: Копіює параметри туману з іншого об'єкта FColormap.
- **Decolorize()**: Знебарвлює колір світла.
- **operator == (const FColormap &other)**: Порівнює два об'єкти FColormap на рівність.
- **operator != (const FColormap &other)**: Порівнює два об'єкти FColormap на нерівність.

#### Реалізація
Структура FColormap використовує клас PalEntry для представлення кольорів. PalEntry зберігає колір у форматі RGBA і надає методи для роботи з кольорами.

#### Зв'язки з іншими модулями
FColormap використовується системою рендерингу для застосування кольорових ефектів до об'єктів у грі. Вона тісно пов'язана з системою освітлення та туману.
