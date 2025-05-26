# bbannouncer.cpp

**Призначення:**
- Реалізує Bloodbath Announcer — систему озвучення і текстових повідомлень у стилі гри Blood для deathmatch/multiplayer подій (вбивства, telefrag, spree, multikill, старт гри).

## Основні структури
- `struct SoundAndString` — зв'язка текстового повідомлення та ідентифікатора звуку.

## Основні функції
- `bool AnnounceGameStart();` — оголошення старту гри (звук/текст).
- `bool AnnounceKill(AActor *killer, AActor *killee);` — оголошення вбивства (звук/текст, врахування статі, самогубство, killer/killee).
- `bool AnnounceTelefrag(AActor *killer, AActor *killee);` — оголошення telefrag (звук/текст).
- `bool AnnounceSpree(AActor *who);` — оголошення spree (серія вбивств).
- `bool AnnounceSpreeLoss(AActor *who);` — оголошення втрати spree.
- `bool AnnounceMultikill(AActor *who);` — оголошення multikill.
- Всі функції повертають true, якщо було згенеровано текстове повідомлення.

## Глобальні/статичні дані
- Масиви ідентифікаторів звуків для різних подій (BeginSounds, WorldKillSounds, SuicideSounds, KillSounds, GoodJobSounds, TooBadSounds, TelefragSounds).
- `CVAR (Bool, cl_bbannounce, false, CVAR_ARCHIVE)` — вмикає/вимикає озвучення.
- `static int LastAnnounceTime` — антиспам для звуків.
- `static FCRandom pr_bbannounce` — генератор випадкових чисел для вибору звуку.

## Інтерфейс
- Інтеграція з HUD, Printf, GStrings, CheckLocalView, звуковою підсистемою (S_Sound).
- Підтримка різних статей гравців, локалізація тексту, персоналізація повідомлень.

## Місця використання
- Викликається з deathmatch/multiplayer логіки для інформування гравців про важливі події.
- Інтеграція з announcer.h, HUD, звуковою підсистемою, логікою deathmatch.

---

**Оновлено:** 2025-05-25
