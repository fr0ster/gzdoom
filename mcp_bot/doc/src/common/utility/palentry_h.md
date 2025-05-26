# palentry.h

## Призначення файлу
Файл `palentry.h` визначає структуру `PalEntry`, яка використовується для представлення кольорів у форматі RGBA в грі.

## Короткий опис
Цей файл містить визначення структури `PalEntry`, яка представляє колір у форматі RGBA (червоний, зелений, синій, альфа-канал). Структура надає різні методи для роботи з кольорами, такі як модуляція, десатурація, перевірка на чорний/білий колір тощо. Також файл містить допоміжні функції та макроси для роботи з кольорами.

## Структура файлу
```cpp
#pragma once

#include <algorithm>
#include <stdint.h>

// Beware of windows.h :(
#ifdef max
#undef min
#undef max
#endif

struct PalEntry
{
    // Конструктори та оператори
    PalEntry() = default;
    PalEntry(const PalEntry&) = default;
    constexpr PalEntry(uint32_t argb);
    operator uint32_t() const;
    constexpr PalEntry(uint8_t ir, uint8_t ig, uint8_t ib);
    constexpr PalEntry(uint8_t ia, uint8_t ir, uint8_t ig, uint8_t ib);
    
    // Методи для роботи з кольорами
    void SetRGB(PalEntry other);
    PalEntry Modulate(PalEntry other) const;
    constexpr int Luminance() const;
    constexpr int Amplitude() const;
    constexpr void Decolorize();
    constexpr bool isBlack() const;
    constexpr bool isWhite() const;
    PalEntry &operator=(const PalEntry &other) = default;
    constexpr PalEntry &operator=(uint32_t other);
    constexpr PalEntry InverseColor() const;
    
    // Поля для зберігання компонентів кольору
    union
    {
        struct
        {
#ifdef __BIG_ENDIAN__
            uint8_t a, r, g, b;
#else
            uint8_t b, g, r, a;
#endif
        };
        uint32_t d;
    };
};

// Допоміжні функції та макроси
constexpr inline int Luminance(int r, int g, int b);
#define APART(c)            (((c)>>24)&0xff)
#define RPART(c)            (((c)>>16)&0xff)
#define GPART(c)            (((c)>>8)&0xff)
#define BPART(c)            ((c)&0xff) 
#define MAKERGB(r,g,b)      uint32_t(((r)<<16)|((g)<<8)|(b))
#define MAKEARGB(a,r,g,b)   uint32_t(((a)<<24)|((r)<<16)|((g)<<8)|(b))
```

## Основні сутності

### PalEntry
Структура, що представляє колір у форматі RGBA.

#### Призначення
Забезпечує зручний спосіб роботи з кольорами у форматі RGBA, надаючи різні методи для маніпуляцій з кольорами.

#### Поля
- **a**: Альфа-компонент кольору (прозорість).
- **r**: Червоний компонент кольору.
- **g**: Зелений компонент кольору.
- **b**: Синій компонент кольору.
- **d**: Ціле 32-бітне значення, що представляє колір у форматі ARGB або BGRA, залежно від порядку байтів.

#### Методи
- **SetRGB**: Встановлює RGB-компоненти кольору з іншого об'єкта PalEntry.
- **Modulate**: Модулює колір іншим кольором.
- **Luminance**: Обчислює яскравість кольору.
- **Amplitude**: Обчислює амплітуду кольору (максимальне значення серед компонентів RGB).
- **Decolorize**: Знебарвлює колір, перетворюючи його на відтінок сірого.
- **isBlack**: Перевіряє, чи є колір чорним.
- **isWhite**: Перевіряє, чи є колір білим.
- **InverseColor**: Повертає інвертований колір.

#### Особливості реалізації
Структура використовує об'єднання (union) для представлення кольору як у вигляді окремих компонентів, так і у вигляді цілого 32-бітного значення. Порядок компонентів у структурі залежить від порядку байтів системи (__BIG_ENDIAN__ або little endian).

### Допоміжні функції та макроси

#### Luminance
Функція, що обчислює яскравість кольору за його RGB-компонентами.

#### APART, RPART, GPART, BPART
Макроси для отримання окремих компонентів кольору з 32-бітного значення.

#### MAKERGB, MAKEARGB
Макроси для створення 32-бітного значення кольору з окремих компонентів.

## Зв'язки з іншими модулями
Структура `PalEntry` використовується багатьма модулями для роботи з кольорами, включаючи систему рендерингу, палітри, таблиці перетворення кольорів тощо. Вона є основним типом для представлення кольорів у грі.
