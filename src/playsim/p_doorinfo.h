#pragma once

#include "d_player.h"
#include "p_local.h"
// Видалено включення a_doors.h, оскільки ми не використовуємо класи дверей

// Структура для зберігання інформації про двері
struct DoorInfo
{
    line_t* line;         // Лінія, що представляє двері
    sector_t* sector;     // Сектор, до якого належать двері
    bool isVisible;       // Чи видно двері гравцю
    bool isPassable;      // Чи можна пройти через двері
    int status;           // Статус дверей (відкриті, закриті, відкриваються, закриваються)
    double distance;      // Відстань від гравця до дверей
    int keyType;          // Тип ключа, необхідний для відкриття дверей (0 - не потрібен ключ)
    DVector2 position;    // Позиція дверей у світі
};

// Статуси дверей
enum DoorStatus
{
    DOOR_CLOSED = 0,
    DOOR_OPENED = 1,
    DOOR_OPENING = 2,
    DOOR_CLOSING = 3,
    DOOR_WAITING = 4,
    DOOR_LOCKED = 5,    // Двері заблоковані ключем
    DOOR_UNKNOWN = -1
};

// Функція для визначення статусу дверей
int GetDoorStatus(line_t* line, sector_t* sector, player_t* player = nullptr);

// Функція для отримання списку видимих дверей
TArray<DoorInfo> GetVisibleDoors(player_t* player);

// Функція для визначення, чи є лінія дверима
bool IsDoor(line_t* line);

// Функція для визначення статусу дверей
int GetDoorStatus(line_t* line, sector_t* sector);

// Функція для визначення пріоритету статусу дверей
int GetDoorStatusPriority(int doorStatus);

// Функція для визначення, чи можна пройти через двері
bool IsDoorPassable(line_t* line, sector_t* sector);

// Функції для роботи з thinker-ами дверей видалені, оскільки ми використовуємо лише властивості line_t та sector_t

// Глобальні змінні для зберігання останнього статусу дверей
extern int g_lastDoorStatus;
extern line_t* g_lastDoorLine;
extern sector_t* g_lastDoorSector;

// Функція для отримання рядка статусу дверей
FString GetDoorStatusString(int doorStatus, line_t* line);

// Функція для визначення дверей перед гравцем
DoorInfo* GetDoorInFront(player_t* player, double maxDistance = 200.0);

// Функція для отримання типу ключа для дверей
int GetKeyTypeForDoor(line_t* line);

// Функція для отримання назви типу ключа за його номером
FString GetKeyTypeName(int keyType);

// Функція для формування рядка статусу дверей з урахуванням типу ключа
FString GetDoorStatusString(int doorStatus, line_t* line);

// Функція для логування інформації про двері
void LogDoorInfo(player_t* player);

// Глобальні змінні для зберігання останнього статусу дверей
extern int g_lastDoorStatus;
extern line_t* g_lastDoorLine;
extern sector_t* g_lastDoorSector;
