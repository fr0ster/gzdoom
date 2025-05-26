# v_2ddrawer.h

**Призначення:**

Заголовочний файл для універсального пристрій-незалежного 2D-драйвера рендерингу у GZDoom. Описує основні класи, структури, інтерфейси для роботи з 2D-графікою, трансформаціями, буферами, полігонами, командами рендерингу.

## Основні класи та структури

### F2DDrawer
- **Призначення:** Головний клас для накопичення та виконання команд 2D-рендерингу (текстури, полігони, лінії, пікселі, стінсили, overlay, скейлінг, кольорові ефекти).
- **Інтерфейс:**
  - Додавання текстур, полігонів, ліній, пікселів: `AddTexture`, `AddShape`, `AddPoly`, `AddFlatFill`, `AddColorOnlyQuad`, `AddLine`, `AddThickLine`, `AddPixel`.
  - Стінсили: `AddEnableStencil`, `AddSetStencil`, `AddClearStencil`.
  - Управління: `Clear`, `Lock`, `Unlock`, `SetScreenFade`, `SetSize`, `Begin`, `End`, `OnFrameDone`, `SetClipRect`, `ClearClipRect`, `SetOffset`, `SetTransform`, `ClearTransform`.
- **Використання:**
  - Викликається з різних підсистем для рендерингу HUD, тексту, меню, statusbar, cutscenes, консолі.

### DShape2D, DShape2DTransform
- **Призначення:**
  - `DShape2D` — довільна 2D-форма (вершини, координати, індекси, трансформації).
  - `DShape2DTransform` — матриця трансформації для 2D-форм.
- **Інтерфейс:**
  - `PushVertex`, `PushCoord`, `PushTriangle`, `SetTransform`, `Clear`, `OnDestroy` (DShape2D)
  - `Clear`, `Rotate`, `Scale`, `Translate`, `From2D` (DShape2DTransform)

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

## Місця використання
- `hw_draw2d.cpp`, `v_drawtext.cpp`, `v_draw.cpp`, `shared_sbar.cpp`, `stats.cpp`, `c_console.cpp`, `c_commandbuffer.cpp`, `screenjob.cpp`, `movieplayer.cpp`, `v_framebuffer.cpp`, `vk_descriptorset.cpp`, `vk_renderpass.cpp` та інші.

---

**Оновлено:** 2025-05-24
