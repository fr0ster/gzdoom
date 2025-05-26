# announcer.h

**Призначення:**
- Оголошення ігрових подій (kill, spree, multikill, telefrag, старт гри) у вигляді текстових повідомлень або звуків для гравців у мультиплеєрі.

## Основні функції
- `bool AnnounceGameStart();` — оголошення старту гри.
- `bool AnnounceKill(AActor *killer, AActor *killee);` — оголошення вбивства.
- `bool AnnounceTelefrag(AActor *killer, AActor *killee);` — оголошення telefrag.
- `bool AnnounceSpree(AActor *who);` — оголошення серії вбивств (spree).
- `bool AnnounceSpreeLoss(AActor *who);` — оголошення втрати spree.
- `bool AnnounceMultikill(AActor *who);` — оголошення multikill.

**Інтерфейс:**
- Всі функції повертають true, якщо було згенеровано текстове повідомлення.
- Параметри: вказівники на акторів (гравців/монстрів), які беруть участь у події.

## Місця використання
- Викликаються з ігрової логіки (deathmatch, multiplayer) для інформування гравців про важливі події.
- Інтеграція з HUD, звуковою підсистемою, логікою deathmatch.

---

**Оновлено:** 2025-05-25
