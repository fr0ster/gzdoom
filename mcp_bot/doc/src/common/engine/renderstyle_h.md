# renderstyle.h

## Призначення файлу
Файл `renderstyle.h` визначає константи, типи та структури для специфікації змішування текстур та стилів рендерингу в грі.

## Короткий опис
Цей файл містить визначення різних режимів текстурування, стилів рендерингу, операцій змішування та прапорців, які використовуються для контролю над тим, як текстури та кольори змішуються під час рендерингу. Він забезпечує гнучку систему для створення різних візуальних ефектів, таких як прозорість, адитивне змішування, тіні та інші.

## Структура файлу
```cpp
#pragma once
/*
** r_blend.h
** Constants and types for specifying texture blending.
**
**---------------------------------------------------------------------------
** Copyright 2008 Randy Heit
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**---------------------------------------------------------------------------
**
*/
#include <stdint.h>

// <wingdi.h> also #defines OPAQUE
#ifdef OPAQUE
#undef OPAQUE
#endif

constexpr int OPAQUE = 65536;

enum ETexMode
{
    TM_NORMAL = 0,  // (r, g, b, a)
    TM_STENCIL,     // (1, 1, 1, a)
    TM_OPAQUE,      // (r, g, b, 1)
    TM_INVERSE,     // (1-r, 1-g, 1-b, a)
    TM_ALPHATEXTURE,    // (1, 1, 1, r)
    TM_CLAMPY,      // (r, g, b, (t >= 0.0 && t <= 1.0)? a:0)
    TM_INVERTOPAQUE,    // (1-r, 1-g, 1-b, 1)
    TM_FOGLAYER,    // (renders a fog layer in the shape of the active texture)
    TM_FIXEDCOLORMAP = TM_FOGLAYER, // repurposes the objectcolor uniforms to render a fixed colormap range. (Same constant because they cannot be used in the same context.
};

// Legacy render styles
enum ERenderStyle : int
{
    STYLE_None,             // Do not draw
    STYLE_Normal,           // Normal; just copy the image to the screen
    STYLE_Fuzzy,            // Draw silhouette using "fuzz" effect
    STYLE_SoulTrans,        // Draw translucent with amount in r_transsouls
    STYLE_OptFuzzy,         // Draw as fuzzy or translucent, based on user preference
    STYLE_Stencil,          // Fill image interior with alphacolor
    STYLE_Translucent,      // Draw translucent
    STYLE_Add,              // Draw additive
    STYLE_Shaded,           // Treat patch data as alpha values for alphacolor
    STYLE_TranslucentStencil,
    STYLE_Shadow,
    STYLE_Subtract,         // Actually this is 'reverse subtract' but this is what normal people would expect by 'subtract'.
    STYLE_AddStencil,       // Fill image interior with alphacolor
    STYLE_AddShaded,        // Treat patch data as alpha values for alphacolor
    STYLE_Multiply,         // Multiply source with destination (HW renderer only.)
    STYLE_InverseMultiply,  // Multiply source with inverse of destination (HW renderer only.)
    STYLE_ColorBlend,       // Use color intensity as transparency factor
    STYLE_Source,           // No blending (only used internally)
    STYLE_ColorAdd,         // Use color intensity as transparency factor and blend additively.

    STYLE_Count
};

// Flexible render styles (most possible combinations are supported in software)
enum ERenderOp
{
    STYLEOP_None,           // Do not draw
    STYLEOP_Add,            // Add source to destination
    STYLEOP_Sub,            // Subtract source from destination
    STYLEOP_RevSub,         // Subtract destination from source
    STYLEOP_Fuzz,           // Draw fuzzy on top of destination - ignores alpha and color
    STYLEOP_FuzzOrAdd,      // Draw fuzzy or add, based on user preference
    STYLEOP_FuzzOrSub,      // Draw fuzzy or subtract, based on user preference
    STYLEOP_FuzzOrRevSub,   // Draw fuzzy or reverse subtract, based on user preference

    // special styles
    STYLEOP_Shadow,         
};

enum ERenderAlpha
{
    STYLEALPHA_Zero,        // Blend factor is 0.0
    STYLEALPHA_One,         // Blend factor is 1.0
    STYLEALPHA_Src,         // Blend factor is alpha
    STYLEALPHA_InvSrc,      // Blend factor is 1.0 - alpha
    STYLEALPHA_SrcCol,      // Blend factor is color (HWR only)
    STYLEALPHA_InvSrcCol,   // Blend factor is 1.0 - color (HWR only)
    STYLEALPHA_DstCol,      // Blend factor is dest. color (HWR only)
    STYLEALPHA_InvDstCol,   // Blend factor is 1.0 - dest. color (HWR only)
    STYLEALPHA_Dst,         // Blend factor is dest. alpha
    STYLEALPHA_InvDst,      // Blend factor is 1.0 - dest. alpha
    STYLEALPHA_MAX
};

enum ERenderFlags
{
    // Use value of transsouls as alpha.
    STYLEF_TransSoulsAlpha = 1,

    // Force alpha to 1. Not the same as STYLEALPHA_One, since that also
    // ignores alpha from the texture.
    STYLEF_Alpha1 = 2,

    // Use red component from grayscale/RGB texture as alpha. If the texture
    // is paletted, the palette is ignored and it is treated as grayscale.
    // This should generally be combined with STYLEF_ColorIsFixed, since that's
    // all the software renderer supports, but hardware acceleration can do
    // them separately should you want to do that for some reason.
    STYLEF_RedIsAlpha = 4,

    // Ignore texture for RGB output. Color comes from fillcolor for actors
    // or DTA_FillColor for DrawTexture().
    STYLEF_ColorIsFixed = 8,

    // Invert source color, either the texture color or the fixed color.
    STYLEF_InvertSource = 16,

    // Invert overlay color. This is the fade for actors and DTA_ColorOverlay
    // for DrawTexture().
    STYLEF_InvertOverlay = 32,

    // Actors only: Ignore sector fade and fade to black. To fade to white,
    // combine this with STYLEF_InvertOverlay.
    STYLEF_FadeToBlack = 64,
};

union FRenderStyle
{
    struct
    {
        uint8_t BlendOp;    // Of ERenderOp type
        uint8_t SrcAlpha;   // Of ERenderAlpha type
        uint8_t DestAlpha;  // Of ERenderAlpha type
        uint8_t Flags;
    };
    uint32_t AsDWORD;

    inline FRenderStyle &operator= (ERenderStyle legacy);
    bool operator==(const FRenderStyle &o) const { return AsDWORD == o.AsDWORD; }
    bool operator!=(const FRenderStyle &o) const { return AsDWORD != o.AsDWORD; }
    void CheckFuzz();
    bool IsVisible(double alpha) const throw();
private:
    // Code that compares an actor's render style with a legacy render
    // style value should be updated.
    operator ERenderStyle() = delete;
    operator int() const = delete;
};

extern FRenderStyle LegacyRenderStyles[STYLE_Count];

inline FRenderStyle DefaultRenderStyle()
{
    return LegacyRenderStyles[STYLE_Normal];
}

inline FRenderStyle &FRenderStyle::operator= (ERenderStyle legacy)
{
    if (legacy < STYLE_None || legacy >= STYLE_Count)
    {
        legacy = STYLE_None;
    }
    *this = LegacyRenderStyles[legacy];
    return *this;
}
```

## Основні сутності

### OPAQUE
Константа, що визначає повну непрозорість.

#### Призначення
Використовується для позначення повної непрозорості (альфа = 1.0) в системі рендерингу.

#### Значення
65536 (представляє 1.0 у форматі з фіксованою точкою).

### ETexMode
Перелічення, що визначає режими текстурування.

#### Призначення
Визначає різні способи інтерпретації та застосування текстурних даних під час рендерингу.

#### Значення
- **TM_NORMAL**: Нормальний режим (r, g, b, a).
- **TM_STENCIL**: Режим трафарету (1, 1, 1, a).
- **TM_OPAQUE**: Непрозорий режим (r, g, b, 1).
- **TM_INVERSE**: Інвертований режим (1-r, 1-g, 1-b, a).
- **TM_ALPHATEXTURE**: Режим альфа-текстури (1, 1, 1, r).
- **TM_CLAMPY**: Режим з обмеженням по Y (r, g, b, (t >= 0.0 && t <= 1.0)? a:0).
- **TM_INVERTOPAQUE**: Інвертований непрозорий режим (1-r, 1-g, 1-b, 1).
- **TM_FOGLAYER**: Режим шару туману (рендерить шар туману у формі активної текстури).
- **TM_FIXEDCOLORMAP**: Режим фіксованої кольорової карти (перепризначає уніформи objectcolor для рендерингу фіксованого діапазону кольорової карти).

### ERenderStyle
Перелічення, що визначає стилі рендерингу (застарілі).

#### Призначення
Визначає різні стилі рендерингу, які використовуються для створення різних візуальних ефектів.

#### Значення
- **STYLE_None**: Не рендерити.
- **STYLE_Normal**: Нормальний стиль; просто копіює зображення на екран.
- **STYLE_Fuzzy**: Рендерить силует, використовуючи ефект "fuzz".
- **STYLE_SoulTrans**: Рендерить напівпрозоро з кількістю, визначеною в r_transsouls.
- **STYLE_OptFuzzy**: Рендерить як fuzzy або напівпрозоро, залежно від уподобань користувача.
- **STYLE_Stencil**: Заповнює внутрішню частину зображення кольором альфа.
- **STYLE_Translucent**: Рендерить напівпрозоро.
- **STYLE_Add**: Рендерить адитивно.
- **STYLE_Shaded**: Трактує дані патчу як значення альфа для кольору альфа.
- **STYLE_TranslucentStencil**: Напівпрозорий трафарет.
- **STYLE_Shadow**: Тінь.
- **STYLE_Subtract**: Насправді це "зворотне віднімання", але це те, що звичайні люди очікують від "віднімання".
- **STYLE_AddStencil**: Заповнює внутрішню частину зображення кольором альфа.
- **STYLE_AddShaded**: Трактує дані патчу як значення альфа для кольору альфа.
- **STYLE_Multiply**: Множить джерело на призначення (тільки для апаратного рендерера).
- **STYLE_InverseMultiply**: Множить джерело на інверсію призначення (тільки для апаратного рендерера).
- **STYLE_ColorBlend**: Використовує інтенсивність кольору як фактор прозорості.
- **STYLE_Source**: Без змішування (використовується тільки внутрішньо).
- **STYLE_ColorAdd**: Використовує інтенсивність кольору як фактор прозорості та змішує адитивно.
- **STYLE_Count**: Кількість стилів.

### ERenderOp
Перелічення, що визначає операції рендерингу (гнучкі стилі рендерингу).

#### Призначення
Визначає різні операції змішування, які використовуються для створення гнучких стилів рендерингу.

#### Значення
- **STYLEOP_None**: Не рендерити.
- **STYLEOP_Add**: Додати джерело до призначення.
- **STYLEOP_Sub**: Відняти джерело від призначення.
- **STYLEOP_RevSub**: Відняти призначення від джерела.
- **STYLEOP_Fuzz**: Рендерить fuzzy поверх призначення - ігнорує альфа та колір.
- **STYLEOP_FuzzOrAdd**: Рендерить fuzzy або додає, залежно від уподобань користувача.
- **STYLEOP_FuzzOrSub**: Рендерить fuzzy або віднімає, залежно від уподобань користувача.
- **STYLEOP_FuzzOrRevSub**: Рендерить fuzzy або зворотньо віднімає, залежно від уподобань користувача.
- **STYLEOP_Shadow**: Спеціальний стиль для тіней.

### ERenderAlpha
Перелічення, що визначає фактори альфа-змішування.

#### Призначення
Визначає різні фактори альфа-змішування, які використовуються для контролю над тим, як джерело та призначення змішуються.

#### Значення
- **STYLEALPHA_Zero**: Фактор змішування дорівнює 0.0.
- **STYLEALPHA_One**: Фактор змішування дорівнює 1.0.
- **STYLEALPHA_Src**: Фактор змішування дорівнює альфа.
- **STYLEALPHA_InvSrc**: Фактор змішування дорівнює 1.0 - альфа.
- **STYLEALPHA_SrcCol**: Фактор змішування дорівнює кольору (тільки для апаратного рендерера).
- **STYLEALPHA_InvSrcCol**: Фактор змішування дорівнює 1.0 - колір (тільки для апаратного рендерера).
- **STYLEALPHA_DstCol**: Фактор змішування дорівнює кольору призначення (тільки для апаратного рендерера).
- **STYLEALPHA_InvDstCol**: Фактор змішування дорівнює 1.0 - колір призначення (тільки для апаратного рендерера).
- **STYLEALPHA_Dst**: Фактор змішування дорівнює альфа призначення.
- **STYLEALPHA_InvDst**: Фактор змішування дорівнює 1.0 - альфа призначення.
- **STYLEALPHA_MAX**: Максимальне значення.

### ERenderFlags
Перелічення, що визначає прапорці рендерингу.

#### Призначення
Визначає різні прапорці, які використовуються для контролю над тим, як текстури та кольори змішуються під час рендерингу.

#### Значення
- **STYLEF_TransSoulsAlpha**: Використовувати значення transsouls як альфа.
- **STYLEF_Alpha1**: Примусово встановити альфа в 1. Не те саме, що STYLEALPHA_One, оскільки це також ігнорує альфа з текстури.
- **STYLEF_RedIsAlpha**: Використовувати червоний компонент з текстури у відтінках сірого/RGB як альфа. Якщо текстура має палітру, палітра ігнорується, і вона трактується як відтінки сірого.
- **STYLEF_ColorIsFixed**: Ігнорувати текстуру для виводу RGB. Колір береться з fillcolor для акторів або DTA_FillColor для DrawTexture().
- **STYLEF_InvertSource**: Інвертувати колір джерела, або колір текстури, або фіксований колір.
- **STYLEF_InvertOverlay**: Інвертувати колір накладання. Це затухання для акторів та DTA_ColorOverlay для DrawTexture().
- **STYLEF_FadeToBlack**: Тільки для акторів: Ігнорувати затухання сектора та затухати до чорного. Щоб затухати до білого, комбінуйте це з STYLEF_InvertOverlay.

### FRenderStyle
Об'єднання, що визначає стиль рендерингу.

#### Призначення
Визначає гнучкий стиль рендерингу, який комбінує операцію змішування, фактори альфа-змішування для джерела та призначення, а також прапорці.

#### Поля
- **BlendOp**: Операція змішування (тип ERenderOp).
- **SrcAlpha**: Фактор альфа-змішування для джерела (тип ERenderAlpha).
- **DestAlpha**: Фактор альфа-змішування для призначення (тип ERenderAlpha).
- **Flags**: Прапорці.
- **AsDWORD**: Доступ до всіх полів як до 32-бітного цілого числа.

#### Методи
- **operator=**: Оператор присвоєння для застарілих стилів рендерингу.
- **operator==**: Оператор порівняння на рівність.
- **operator!=**: Оператор порівняння на нерівність.
- **CheckFuzz**: Перевіряє та коригує налаштування для fuzzy-рендерингу.
- **IsVisible**: Перевіряє, чи буде об'єкт видимим з даним значенням альфа.

### LegacyRenderStyles
Масив стилів рендерингу, що відповідають застарілим стилям.

#### Призначення
Зберігає стилі рендерингу, які відповідають застарілим стилям рендерингу.

#### Тип
Масив FRenderStyle розміром STYLE_Count.

### DefaultRenderStyle
Функція, що повертає стиль рендерингу за замовчуванням.

#### Призначення
Повертає стиль рендерингу за замовчуванням, який відповідає STYLE_Normal.

#### Повертає
Об'єкт FRenderStyle, що відповідає STYLE_Normal.

## Зв'язки з іншими модулями
Файл `renderstyle.h` тісно пов'язаний з системою рендерингу гри. Він визначає стилі рендерингу, які використовуються для рендерингу акторів, спрайтів, текстур та інших графічних елементів. Стилі рендерингу використовуються для створення різних візуальних ефектів, таких як прозорість, адитивне змішування, тіні та інші.

Стилі рендерингу використовуються в таких модулях:
- Система рендерингу: для визначення того, як рендерити різні об'єкти.
- Система акторів: для визначення того, як рендерити акторів.
- Система спрайтів: для визначення того, як рендерити спрайти.
- Система текстур: для визначення того, як рендерити текстури.
- Система ефектів: для створення різних візуальних ефектів.

Файл також пов'язаний з файлом `r_blend.h`, який визначає константи та типи для специфікації змішування текстур.
