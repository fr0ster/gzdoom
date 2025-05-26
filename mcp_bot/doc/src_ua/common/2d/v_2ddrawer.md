# v_2ddrawer.h / v_2ddrawer.cpp

**Призначення:**

Модуль `v_2ddrawer` реалізує незалежний від пристрою 2D-драйвер для рендерингу примітивів, текстур, полігонів, ліній, пікселів, а також підтримує трансформації, стеки команд, стінсили, скейлінг, кольорові ефекти та інше. Використовується для рендерингу HUD, тексту, інтерфейсних елементів, 2D-ефектів у GZDoom.

## Основні класи та структури

### F2DDrawer
- **Призначення:** Головний клас для накопичення та виконання команд 2D-рендерингу.
- **Інтерфейс:**
  - `AddTexture`, `AddShape`, `AddPoly`, `AddFlatFill`, `AddColorOnlyQuad`, `AddLine`, `AddThickLine`, `AddPixel`, `AddEnableStencil`, `AddSetStencil`, `AddClearStencil`, `Clear`, `Lock`, `Unlock`, `SetScreenFade`, `SetSize`, `Begin`, `End`, `OnFrameDone`, `SetClipRect`, `ClearClipRect`, `SetOffset`, `SetTransform`, `ClearTransform` та інші.
- **Використання:**
  - Викликається з різних підсистем для рендерингу 2D-графіки (HUD, текст, меню, cutscenes, statusbar, консоль).
  - Приклади використання: `Draw2D(F2DDrawer*, ...)`, `DrawChar(F2DDrawer*, ...)`, `DrawText(F2DDrawer*, ...)`, `V_DrawFrame(F2DDrawer*, ...)`, `FStat::PrintStat(F2DDrawer*)`.

### DShape2D, DShape2DTransform
- **Призначення:**
  - `DShape2D` — описує довільну 2D-форму (вершини, координати, індекси, трансформації).
  - `DShape2DTransform` — матриця трансформації для 2D-форм.
- **Інтерфейс:**
  - `PushVertex`, `PushCoord`, `PushTriangle`, `SetTransform`, `Clear`, `OnDestroy` (DShape2D)
  - `Clear`, `Rotate`, `Scale`, `Translate`, `From2D` (DShape2DTransform)
- **Використання:**
  - Для складних полігональних ефектів, кастомних форм, анімацій.

### F2DVertexBuffer, DShape2DBufferInfo
- **Призначення:**
  - `F2DVertexBuffer` — GPU-буфер для вершин/індексів 2D-рендерингу.
  - `DShape2DBufferInfo` — менеджер буферів для форм.

### Допоміжні структури
- `F2DPolygons`, `F2DDrawer::RenderCommand`, `F2DDrawer::TwoDVertex` — для зберігання полігонів, команд, вершин.

## Глобальні змінні
- `F2DDrawer* twod` — глобальний інстанс для 2D-рендерингу.

## CVARs
- `classic_scaling_factor`, `classic_scaling_pixelaspect`, `transsouls` — впливають на скейлінг та прозорість.

## Основні функції
- `AddTexture`, `AddShape`, `AddPoly`, `AddFlatFill`, `AddColorOnlyQuad`, `AddLine`, `AddThickLine`, `AddPixel`, `AddEnableStencil`, `AddSetStencil`, `AddClearStencil`, `Clear`, `OnFrameDone` — додають різні типи команд у стек рендерингу.
- `SetStyle`, `SetColorOverlay` — налаштування стилю рендерингу, кольорових ефектів.
- `GetClassicFlatScalarWidth/Height` — класичний скейлінг для flat-текстур.

## Місця використання
- **Рендеринг:**
  - `hw_draw2d.cpp` (Draw2D)
  - `v_drawtext.cpp` (DrawChar, DrawText)
  - `v_draw.cpp` (VirtualToRealCoords, GetUIScale)
  - `shared_sbar.cpp` (V_DrawFrame)
  - `stats.cpp` (FStat::PrintStat)
  - `c_console.cpp`, `c_commandbuffer.cpp`, `screenjob.cpp`, `movieplayer.cpp`, `v_framebuffer.cpp`, `vk_descriptorset.cpp`, `vk_renderpass.cpp` — для різних 2D-операцій.

## Призначення та архітектура
- **Архітектура:**
  - F2DDrawer накопичує команди (RenderCommand) у масиві, які потім виконуються GPU/CPU.
  - Підтримує трансформації, стінсили, скейлінг, кольорові ефекти, overlay, індексовані палітри, різні blend-стилі.
  - Підтримка Canvas-текстур (FCanvas).
- **Призначення:**
  - Єдиний універсальний API для 2D-рендерингу у GZDoom, що дозволяє легко додавати нові ефекти, UI, текст, HUD, меню, cutscenes, statusbar тощо.

---

**Оновлено:** 2025-05-24

