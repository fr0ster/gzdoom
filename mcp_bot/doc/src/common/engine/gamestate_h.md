# gamestate.h

## Призначення файлу
Файл `gamestate.h` визначає перелік (enum) `gamestate_t`, який представляє різні стани гри, та глобальну змінну `gamestate`, яка зберігає поточний стан гри.

## Короткий опис
Цей файл містить визначення перерахування `gamestate_t`, яке використовується для відстеження поточного стану гри: чи гравець активно грає на рівні, дивиться екран інтермісії, фінальну анімацію, демо, знаходиться в консолі тощо. Також файл оголошує глобальну змінну `gamestate`, яка зберігає поточний стан гри.

## Структура файлу
```cpp
#pragma once

// The current state of the game: whether we are
// playing, gazing at the intermission screen,
// the game final animation, or a demo. 
enum gamestate_t : int
{
    GS_LEVEL,
    GS_INTERMISSION,
    GS_FINALE,
    GS_DEMOSCREEN,
    GS_FULLCONSOLE,     // [RH] Fullscreen console
    GS_HIDECONSOLE,     // [RH] The menu just did something that should hide fs console
    GS_STARTUP,         // [RH] Console is fullscreen, and game is just starting
    GS_TITLELEVEL,      // [RH] A combination of GS_LEVEL and GS_DEMOSCREEN
    GS_INTRO,
    GS_CUTSCENE,

    GS_MENUSCREEN = GS_DEMOSCREEN,

    GS_FORCEWIPE = -1,
    GS_FORCEWIPEFADE = -2,
    GS_FORCEWIPEBURN = -3,
    GS_FORCEWIPEMELT = -4
};


extern  gamestate_t     gamestate;
```

## Основні сутності

### gamestate_t
Перелік (enum), що визначає можливі стани гри.

#### Призначення
Використовується для відстеження та контролю поточного стану гри, що дозволяє різним частинам коду визначати, як вони повинні поводитися в залежності від того, що відбувається в грі.

#### Значення
- **GS_LEVEL**: Гравець активно грає на рівні.
- **GS_INTERMISSION**: Відображається екран інтермісії між рівнями.
- **GS_FINALE**: Відображається фінальна анімація або екран.
- **GS_DEMOSCREEN**: Відображається демонстраційний екран.
- **GS_FULLCONSOLE**: Відображається повноекранна консоль.
- **GS_HIDECONSOLE**: Меню щойно виконало дію, яка повинна приховати повноекранну консоль.
- **GS_STARTUP**: Консоль відображається в повноекранному режимі, і гра тільки запускається.
- **GS_TITLELEVEL**: Комбінація GS_LEVEL та GS_DEMOSCREEN, використовується для титульних рівнів.
- **GS_INTRO**: Відображається вступна послідовність.
- **GS_CUTSCENE**: Відображається кат-сцена.
- **GS_MENUSCREEN**: Синонім для GS_DEMOSCREEN, використовується для екранів меню.
- **GS_FORCEWIPE**, **GS_FORCEWIPEFADE**, **GS_FORCEWIPEBURN**, **GS_FORCEWIPEMELT**: Спеціальні значення для примусового витирання екрану різними ефектами.

#### Зв'язки з іншими модулями
Використовується багатьма модулями для визначення поведінки в залежності від поточного стану гри.

### gamestate
Глобальна змінна, що зберігає поточний стан гри.

#### Призначення
Надає доступ до поточного стану гри з будь-якої частини коду.

#### Зв'язки з іншими модулями
Використовується багатьма модулями для перевірки поточного стану гри та прийняття рішень на основі цього стану.
