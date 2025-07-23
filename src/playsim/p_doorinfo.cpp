#include "p_doorinfo.h"
#include "ai_config.h"
#include "p_lnspec.h"
#include "p_local.h"
#include "p_maputl.h"
#include "gamedata/a_keys.h"
#include "p_blockmap.h"
#include "g_levellocals.h"
#include "actorinlines.h"
#include "p_linetracedata.h"

// Функція для визначення, чи є лінія дверима
bool IsDoor(line_t* line)
{
    if (!line) return false;
    
    // Перевірка на основі спеціальних ефектів лінії
    // Двері зазвичай мають спеціальні ефекти для відкриття/закриття
    if (line->special == Door_Open || 
        line->special == Door_Close || 
        line->special == Door_Raise ||
        line->special == Door_LockedRaise ||
        line->special == Door_Animated ||
        line->special == Door_WaitRaise ||
        line->special == Door_WaitClose)
    {
        return true;
    }
    
    // Перевірка на основі текстур
    // Якщо лінія має різні текстури з обох боків і має backside
    if (line->sidedef[0] && line->sidedef[1])
    {
        // Якщо є верхня текстура, це може бути дверима
        if (line->sidedef[0]->GetTexture(side_t::top).isValid() ||
            line->sidedef[1]->GetTexture(side_t::top).isValid())
        {
            return true;
        }
    }
    
    // Перевірка на основі геометрії секторів
    if (line->frontsector && line->backsector)
    {
        // Перевіряємо висоту проходу
        double frontFloor = line->frontsector->floorplane.ZatPoint(line->v1->fPos());
        double frontCeil = line->frontsector->ceilingplane.ZatPoint(line->v1->fPos());
        double backFloor = line->backsector->floorplane.ZatPoint(line->v1->fPos());
        double backCeil = line->backsector->ceilingplane.ZatPoint(line->v1->fPos());
        
        // Якщо стеля відрізняються або підлоги відрізняються, це може бути дверима
        if (fabs(frontCeil - backCeil) > 1.0 || fabs(frontFloor - backFloor) > 1.0)
        {
            return true;
        }
    }
    
    return false;
}

// Функція для перевірки наявності активних дверей у секторі
bool HasActiveDoor(sector_t* sector)
{
    if (!sector) return false;
    
    // Перевіряємо всі лінії сектора на наявність дверей
    for (auto line : sector->Lines)
    {
        if (IsDoor(line))
        {
            return true;
        }
    }
    
    return false;
}



// Функція для отримання типу ключа для дверей
int GetKeyTypeForDoor(line_t* line)
{
    if (!line) return 0;
    
    // Перевіряємо різні умови для заблокованих дверей
    if (line->special == Door_LockedRaise)
        return line->args[3]; // Номер ключа зберігається в args[3] для Door_LockedRaise
    else if (line->special == Generic_Door && line->args[4] > 0)
        return line->args[4]; // Номер ключа зберігається в args[4] для Generic_Door
    else if (line->locknumber > 0)
        return line->locknumber;
    
    return 0; // Не потрібен ключ
}

// Функція для отримання назви типу ключа за його номером
FString GetKeyTypeName(int keyType)
{
    // Використовуємо функцію P_GetMapColorForLock для визначення кольору ключа
    if (keyType <= 0) return "";
    
    int keyColor = P_GetMapColorForLock(keyType);
    
    // Визначаємо назву ключа за його кольором
    switch (keyColor)
    {
        case 0xFF0000: return "Red Key";
        case 0x00FF00: return "Green Key";
        case 0x0000FF: return "Blue Key";
        case 0xFFFF00: return "Yellow Key";
        case 0xFF00FF: return "Purple Key";
        case 0x00FFFF: return "Cyan Key";
        case 0xFFFFFF: return "White Key";
        default: return FStringf("Key %d", keyType);
    }
}

// Функція для формування рядка статусу дверей з урахуванням типу ключа
FString GetDoorStatusString(int doorStatus, line_t* line)
{
    switch (doorStatus)
    {
        case DOOR_OPENED:
            return "Open";
        case DOOR_CLOSED:
            return "Closed";
        case DOOR_OPENING:
            return "Opening";
        case DOOR_CLOSING:
            return "Closing";
        case DOOR_WAITING:
            return "Waiting";
        case DOOR_LOCKED:
            {
                // Отримуємо тип ключа для заблокованих дверей
                int keyType = GetKeyTypeForDoor(line);
                FString keyName = GetKeyTypeName(keyType);
                if (keyName.IsNotEmpty())
                    return FStringf("Locked (%s)", keyName.GetChars());
                else
                    return "Locked";
            }
        case DOOR_UNKNOWN:
        default:
            return "Unknown";
    }
}

// Функція для визначення статусу дверей
int GetDoorStatus(line_t* line, sector_t* sector, player_t* player)
{
    if (!line || !sector) return DOOR_UNKNOWN;
    
    // Діагностика для відлагодження
    Printf("DEBUG GetDoorStatus: line=%p, flags=%d, special=%d, locknumber=%d, args=[%d,%d,%d,%d,%d]\n", 
           line, line->flags, line->special, line->locknumber, 
           line->args[0], line->args[1], line->args[2], line->args[3], line->args[4]);
    
    // Перевіряємо, чи двері потребують ключа
    bool needsKey = false;
    int lockNumber = 0;
    
    // Перевіряємо різні умови для заблокованих дверей
    if (line->special == Door_LockedRaise)
    {
        needsKey = true;
        lockNumber = line->args[3]; // Номер ключа зберігається в args[3] для Door_LockedRaise
        Printf("DEBUG Door_LockedRaise: lockNumber=%d\n", lockNumber);
    }
    else if (line->special == Generic_Door && line->args[4] > 0)
    {
        needsKey = true;
        lockNumber = line->args[4]; // Номер ключа зберігається в args[4] для Generic_Door
        Printf("DEBUG Generic_Door: lockNumber=%d\n", lockNumber);
    }
    else if (line->locknumber > 0)
    {
        needsKey = true;
        lockNumber = line->locknumber;
        Printf("DEBUG locknumber: lockNumber=%d\n", lockNumber);
    }
    // Додаткові перевірки для інших типів дверей з ключем
    // Можемо додати тут інші типи дверей з ключем, якщо вони будуть виявлені
    
    // Якщо двері потребують ключа і гравець переданий, перевіряємо наявність ключа
    if (needsKey)
    {
        // Якщо гравець не переданий або не має необхідного ключа, двері заблоковані
        if (!player || !P_CheckKeys(player->mo, lockNumber, false, true))
        {
            Printf("DEBUG Door is LOCKED, key=%d\n", lockNumber);
            return DOOR_LOCKED;
        }
        else
        {
            Printf("DEBUG Player has key=%d\n", lockNumber);
        }
    }
    
    // Перевіряємо наявність thinker-а для дверей у секторі
    // Це більш надійний спосіб визначення статусу дверей, ніж просто перевірка висоти проходу
    bool hasThinker = false;
    int thinkerStatus = -1;
    
    // Перевіряємо активні thinker-и для цього сектора
    TThinkerIterator<DDoor> it(sector->Level);
    DDoor *door;
    while ((door = it.Next()))
    {
        if (door->GetSector() == sector)
        {
            hasThinker = true;
            thinkerStatus = door->m_Direction; // Використовуємо публічне поле m_Direction замість неіснуючого методу GetDirection
            break;
        }
    }
    
    // Якщо знайдено активний thinker для дверей, визначаємо статус на основі його стану
    if (hasThinker)
    {
        switch (thinkerStatus)
        {
            case 1:  // Двері відкриваються (UP)
                return DOOR_OPENING;
            case -1: // Двері закриваються (DOWN)
                return DOOR_CLOSING;
            case 0:  // Двері чекають (WAITING)
                return DOOR_WAITING;
            default:
                // Невідомий статус thinker-а, продовжуємо перевірки
                break;
        }
    }
    
    // Визначаємо статус дверей на основі прапорців лінії та геометрії
    
    // Перевіряємо висоту проходу між секторами
    if (line->backsector && line->frontsector)
    {
        // Перевіряємо висоту проходу
        double frontFloor = line->frontsector->floorplane.ZatPoint(line->v1->fPos());
        double frontCeil = line->frontsector->ceilingplane.ZatPoint(line->v1->fPos());
        double backFloor = line->backsector->floorplane.ZatPoint(line->v1->fPos());
        double backCeil = line->backsector->ceilingplane.ZatPoint(line->v1->fPos());
        
        double lowestCeil = min(frontCeil, backCeil);
        double highestFloor = max(frontFloor, backFloor);
        double openingHeight = lowestCeil - highestFloor;
        
        // Діагностичний вивід
        Printf("DEBUG Door geometry: opening height=%.2f, ML_BLOCKING=%d\n", 
               openingHeight, (line->flags & ML_BLOCKING) ? 1 : 0);
        
        // Якщо лінія має прапорець ML_BLOCKING, двері завжди закриті
        if (line->flags & ML_BLOCKING)
        {
            return DOOR_CLOSED;
        }
        
        // Якщо відстань достатня для проходу (більше 56 одиниць)
        if (openingHeight >= 56)
        {
            return DOOR_OPENED;
        }
        else
        {
            // Якщо висота проходу недостатня, двері закриті
            return DOOR_CLOSED;
        }
    }
    
    // Якщо немає баксектора, це не двері або вони закриті
    return DOOR_CLOSED;
}

// Функція для визначення, чи можна пройти через двері
bool IsDoorPassable(line_t* line, sector_t* sector)
{
    if (!line || !sector) return false;
    
    // Якщо лінія блокуюча, прохід неможливий
    if (line->flags & ML_BLOCKING)
    {
        return false;
    }
    
    // Перевіряємо статус дверей
    int status = GetDoorStatus(line, sector, nullptr);
    if (status == DOOR_OPENED || status == DOOR_OPENING)
    {
        return true;
    }
    
    // Додаткова перевірка для дверей без thinker-а
    if (line->backsector)
    {
        // Перевіряємо, чи достатньо місця для проходу
        double frontFloor = line->frontsector->floorplane.ZatPoint(line->v1->fPos());
        double frontCeil = line->frontsector->ceilingplane.ZatPoint(line->v1->fPos());
        double backFloor = line->backsector->floorplane.ZatPoint(line->v1->fPos());
        double backCeil = line->backsector->ceilingplane.ZatPoint(line->v1->fPos());
        
        double lowestCeil = min(frontCeil, backCeil);
        double highestFloor = max(frontFloor, backFloor);
        
        if (lowestCeil - highestFloor >= 56) // Мінімальна висота для проходу
        {
            return true;
        }
    }
    
    return false;
}

// Функція для перевірки видимості лінії для гравця
bool IsLineVisibleToPlayer(player_t* player, line_t* line)
{
    if (!player || !player->mo || !line) return false;
    
    // Отримуємо позицію гравця
    DVector3 playerPos = player->mo->Pos();
    
    // Отримуємо позиції вершин лінії
    DVector2 v1Pos = line->v1->fPos();
    DVector2 v2Pos = line->v2->fPos();
    
    // Перевіряємо видимість обох вершин лінії
    // Використовуємо P_CheckSight для перевірки видимості
    AActor* dummyActor1 = Spawn(player->mo->Level, "Unknown", DVector3(v1Pos, line->frontsector->floorplane.ZatPoint(v1Pos) + 32), NO_REPLACE);
    AActor* dummyActor2 = Spawn(player->mo->Level, "Unknown", DVector3(v2Pos, line->frontsector->floorplane.ZatPoint(v2Pos) + 32), NO_REPLACE);
    
    bool v1Visible = P_CheckSight(player->mo, dummyActor1, SF_IGNOREVISIBILITY);
    bool v2Visible = P_CheckSight(player->mo, dummyActor2, SF_IGNOREVISIBILITY);
    
    // Видаляємо тимчасові актори
    dummyActor1->Destroy();
    dummyActor2->Destroy();
    
    // Якщо хоча б одна вершина видима, вважаємо лінію видимою
    return v1Visible || v2Visible;
}

// Функція для отримання списку видимих дверей
TArray<DoorInfo> GetVisibleDoors(player_t* player)
{
    TArray<DoorInfo> visibleDoors;
    
    if (!player || !player->mo || !player->mo->Level) return visibleDoors;
    
    // Отримуємо позицію гравця
    DVector3 playerPos = player->mo->Pos();
    
    // Проходимо по всіх лініях рівня
    auto &lines = player->mo->Level->lines;
    for (unsigned int i = 0; i < lines.Size(); i++)
    {
        line_t* line = &lines[i];
        
        // Перевіряємо, чи є лінія дверима
        if (IsDoor(line))
        {
            // Визначаємо сектор дверей (зазвичай це frontsector)
            sector_t* doorSector = line->frontsector;
            
            // Якщо є backsector і він має відмінні властивості, використовуємо його
            if (line->backsector && HasActiveDoor(line->backsector))
            {
                doorSector = line->backsector;
            }
            
            // Перевіряємо видимість дверей
            bool isVisible = IsLineVisibleToPlayer(player, line);
            
            if (isVisible)
            {
                // Створюємо інформацію про двері
                DoorInfo info;
                info.line = line;
                info.sector = doorSector;
                info.isVisible = true;
                info.isPassable = IsDoorPassable(line, doorSector);
                info.status = GetDoorStatus(line, doorSector, player);
                
                // Обчислюємо відстань до дверей
                DVector2 doorCenter = (line->v1->fPos() + line->v2->fPos()) * 0.5;
                info.distance = (doorCenter - DVector2(playerPos.X, playerPos.Y)).Length();
                
                // Додаємо інформацію до списку
                visibleDoors.Push(info);
            }
        }
    }
    
    // Сортуємо двері за відстанню (найближчі спочатку)
    for (unsigned int i = 0; i < visibleDoors.Size(); i++)
    {
        for (unsigned int j = i + 1; j < visibleDoors.Size(); j++)
        {
            if (visibleDoors[j].distance < visibleDoors[i].distance)
            {
                // Міняємо місцями
                DoorInfo temp = visibleDoors[i];
                visibleDoors[i] = visibleDoors[j];
                visibleDoors[j] = temp;
            }
        }
    }
    
    return visibleDoors;
}

// Функція для визначення дверей перед гравцем
DoorInfo* GetDoorInFront(player_t* player, double maxDistance)
{
    if (!player || !player->mo) return nullptr;
    
    // Отримуємо позицію і напрямок гравця
    DVector3 playerPos = player->mo->Pos();
    DAngle playerAngle = player->mo->Angles.Yaw;
    
    // Вектор напрямку погляду
    DVector2 lookDir = playerAngle.ToVector();
    
    // Отримуємо список видимих дверей
    TArray<DoorInfo> visibleDoors = GetVisibleDoors(player);
    
    // Статичний об'єкт для зберігання результату
    static DoorInfo doorResult;
    DoorInfo* bestDoor = nullptr;
    double bestScore = -1.0;
    
    // Перевіряємо кожні двері
    for (unsigned int i = 0; i < visibleDoors.Size(); i++)
    {
        const DoorInfo& door = visibleDoors[i];
        
        // Пропускаємо двері, які занадто далеко
        if (door.distance > maxDistance) continue;
        
        // Обчислюємо центр дверей
        DVector2 doorCenter = (door.line->v1->fPos() + door.line->v2->fPos()) * 0.5;
        
        // Напрямок від гравця до дверей
        DVector2 toDoor = doorCenter - DVector2(playerPos.X, playerPos.Y);
        toDoor.MakeUnit();
        
        // Обчислюємо кут між напрямком погляду і напрямком до дверей
        double dotProduct = lookDir | toDoor; // скалярний добуток
        
        // Оцінка базується на відстані та куті
        // Двері перед гравцем мають високий добуток (> 0.7) і малу відстань
        double score = dotProduct - (door.distance / maxDistance * 0.3);
        
        // Якщо двері не перед гравцем, ігноруємо їх
        if (dotProduct < 0.7) continue;
        
        // Знаходимо найкращі двері перед гравцем
        if (score > bestScore)
        {
            bestScore = score;
            doorResult = door;
            bestDoor = &doorResult;
        }
    }
    
    return bestDoor;
}

// Функція для логування інформації про двері та об'єкти перед гравцем
void LogDoorInfo(player_t* player)
{
    if (!player || !player->mo)
        return;
    
    // Отримуємо список видимих дверей
    TArray<DoorInfo> visibleDoors = GetVisibleDoors(player);
    
    // Перевіряємо що знаходиться перед гравцем
    // Використовуємо трасування для точного визначення дверей у прицілі
    DoorInfo* frontDoor = nullptr;
    
    // Отримуємо позицію і напрямок гравця
    DVector3 playerPos = player->mo->Pos();
    DAngle playerAngle = player->mo->Angles.Yaw;
    DVector2 lookDir = playerAngle.ToVector();
    
    // Виконуємо трасування променя вперед для виявлення стіни
    FLineTraceData trace;
    double maxDistance = 1024.0;
    
    // Трасування променя від гравця вперед з вузьким кутом
    P_LineTrace(player->mo, 
               player->mo->Angles.Yaw, // передаємо сам об'єкт DAngle без перетворень
               maxDistance, 
               DAngle::fromDeg(0.0), // pitch також має бути DAngle
               TRF_ALLACTORS | TRF_NOSKY | TRF_ABSPOSITION, // додаємо TRF_ABSPOSITION для точнішого визначення
               0.0, // offsetz
               0.0, // offsetforward
               0.0, // offsetside
               &trace);
    
    // Визначаємо що перед гравцем
    const char* objectType = "Nothing";
    const char* statusStr = "";
    bool isPassable = true;
    double distance = maxDistance;
    DVector2 position(0, 0);
    
    // Спочатку перевіряємо тип об'єкта, в який потрапив промінь
    if (trace.HitType == TRACE_HitActor && trace.HitActor)
    {
        // Якщо промінь потрапив у актора (монстра), виводимо інформацію про нього
        const char* rawTypeName = trace.HitActor->GetClass()->TypeName.GetChars();
        objectType = rawTypeName;
        isPassable = false;
        distance = trace.Distance;
        position = DVector2(trace.HitLocation.X, trace.HitLocation.Y);
        
        // Діагностичний вивід для визначення типу актора
        // Printf("DEBUG: Actor class=%s, flags3=%d, flags=%d\n", 
        //        rawTypeName, 
        //        trace.HitActor->flags3, 
        //        trace.HitActor->flags);
        
        // Визначаємо тип об'єкта більш точно
        if (trace.HitActor->flags3 & MF3_ISMONSTER)
        {
            // Це монстр
            objectType = "Monster";
            if (trace.HitActor->health <= 0)
            {
                statusStr = "Dead";
            }
            else
            {
                statusStr = "Alive";
            }
        }
        else if (trace.HitActor->flags & MF_SPECIAL)
        {
            // Це предмет, який можна підібрати
            objectType = "Pickup";
            statusStr = rawTypeName;
        }
        else
        {
            // Декорація або інший об'єкт
            objectType = "Decoration";
            statusStr = rawTypeName;
        }
    }
    else if (trace.HitType == TRACE_HitWall)
    {
        // Перевіряємо чи це двері безпосередньо з результатів трасування
        if (trace.HitLine && IsDoor(trace.HitLine))
        {
            // Перевіряємо, чи двері знаходяться перед гравцем, а не позаду
            DVector2 lineCenter = (trace.HitLine->v1->fPos() + trace.HitLine->v2->fPos()) * 0.5;
            DVector2 playerToLine = lineCenter - player->mo->Pos().XY();
            DVector2 playerLookDir = player->mo->Angles.Yaw.ToVector();
            
            // Обчислюємо скалярний добуток для визначення напрямку
            double dotProduct = playerToLine.X * playerLookDir.X + playerToLine.Y * playerLookDir.Y;
            
            // Якщо скалярний добуток додатний, то двері перед гравцем
            if (dotProduct > 0)
            {
                // Це двері у прицілі і вони перед гравцем
                objectType = "Door";
                distance = trace.Distance;
                position = trace.HitLocation.XY();
                
                // Визначаємо сектор дверей
                sector_t* doorSector = trace.HitLine->frontsector;
                if (trace.HitLine->backsector && 
                    (trace.HitLine->frontsector->floorplane.ZatPoint(position) > 
                     trace.HitLine->backsector->floorplane.ZatPoint(position)))
                {
                    doorSector = trace.HitLine->backsector;
                }
                
                // Перевіряємо статус дверей з урахуванням гравця
                int doorStatus = GetDoorStatus(trace.HitLine, doorSector, player);
                
                // Діагностика статусу дверей
                Printf("DEBUG Door in crosshair: status=%d, special=%d, locknumber=%d\n", 
                       doorStatus, trace.HitLine->special, trace.HitLine->locknumber);
                
                // Перевіряємо прохідність дверей
                isPassable = IsDoorPassable(trace.HitLine, doorSector);
                
                // Використовуємо функцію GetDoorStatusString для формування рядка статусу дверей
                FString statusString = GetDoorStatusString(doorStatus, trace.HitLine);
                statusStr = statusString.GetChars();
                
                // Діагностика статусу дверей у рядку
                Printf("DEBUG Door status string: '%s'\n", statusStr);
            }
            else
            {
                // Двері позаду гравця, ігноруємо і вважаємо стіною
                objectType = "Wall";
            }
        }
        else
        {
            // Це стіна
            objectType = "Wall";
            isPassable = false;
            distance = trace.Distance;
            position = DVector2(trace.HitLocation.X, trace.HitLocation.Y);
        }
    }
    else if (trace.HitType == TRACE_HitFloor || trace.HitType == TRACE_HitCeiling)
    {
        objectType = "Floor/Ceiling";
        isPassable = false;
        distance = trace.Distance;
        position = DVector2(trace.HitLocation.X, trace.HitLocation.Y);
    }
    else
    {
        objectType = "Passage";
        isPassable = true;
        distance = maxDistance;
        position = DVector2(playerPos.X + lookDir.X * maxDistance, playerPos.Y + lookDir.Y * maxDistance);
    }
    
    // Виводимо інформацію про об'єкт перед гравцем
    if (strcmp(objectType, "Door") == 0 || strlen(statusStr) > 0)
    {
        AI_Log(AI_DEBUG_INFO, "[OBJECT IN FRONT] Type=%s, Status=%s, Passable=%s, Distance=%.2f, Position=(%.2f, %.2f)",
               objectType, statusStr, isPassable ? "Yes" : "No", distance, position.X, position.Y);
    }
    else
    {
        AI_Log(AI_DEBUG_INFO, "[OBJECT IN FRONT] Type=%s, Passable=%s, Distance=%.2f, Position=(%.2f, %.2f)",
               objectType, isPassable ? "Yes" : "No", distance, position.X, position.Y);
    }
    
    // Логуємо інформацію про двері лише якщо включено детальне логування
    if (g_ai_config.debug_info)
    {
        for (unsigned int i = 0; i < visibleDoors.Size(); i++)
        {
            const DoorInfo& door = visibleDoors[i];
            const char* statusStr = "Unknown";
            
            // Перетворюємо статус на рядок
            switch (door.status)
            {
                case DOOR_CLOSED:
                    statusStr = "Closed";
                    break;
                case DOOR_OPENED:
                    statusStr = "Opened";
                    break;
                case DOOR_OPENING:
                    statusStr = "Opening";
                    break;
                case DOOR_CLOSING:
                    statusStr = "Closing";
                    break;
                case DOOR_WAITING:
                    statusStr = "Waiting";
                    break;
                case DOOR_LOCKED:
                    statusStr = "Locked";
                    break;
            }
            
            // Логуємо інформацію про двері
            AI_Log(AI_DEBUG_INFO, "Door %d: Status=%s, Passable=%s, Distance=%.2f",
                i, statusStr, door.isPassable ? "Yes" : "No", door.distance);
        }
    }
}
