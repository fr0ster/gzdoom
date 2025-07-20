#pragma once

#include "d_player.h"
#include "p_sightinfo.h"

// Рівні логування для AI системи
enum AIDebugLevel
{
    AI_DEBUG_NONE = 0,       // Без логування
    AI_DEBUG_ERROR = 1,      // Тільки помилки
    AI_DEBUG_WARNING = 2,    // Помилки та попередження
    AI_DEBUG_INFO = 3,       // Загальна інформація
    AI_DEBUG_VERBOSE = 4,    // Детальна інформація
    AI_DEBUG_TRACE = 5       // Максимальна деталізація
};

// Конфігурація системи AI
struct AIConfig
{
    float update_interval = 0.1f;     // інтервал оновлення в секундах
    int max_monsters = 10;           // максимальна кількість монстрів
    int max_distance = 1000;         // максимальна відстань для виявлення
    bool debug_info = false;         // чи показувати дебаг інформацію
    bool enabled = true;             // чи включена система AI
    bool use_mcp = true;            // чи використовувати MCP для передачі даних
    int mcp_port = 12345;           // порт для MCP сервера
    FString mcp_address = "localhost"; // адреса MCP сервера
    bool log_to_file = false;        // Чи записувати логи у файл
    FString log_file_path = "";      // Шлях до файлу логів
    
    // Рівень логування
    AIDebugLevel debug_level = AI_DEBUG_INFO; // За замовчуванням - загальна інформація
    
    // Частота виводу логів (кожні N викликів)
    int log_frequency = 100;        // Виводити логи кожні N викликів
};

// Глобальна конфігурація
extern AIConfig g_ai_config;

// Функції для ініціалізації та завершення
void AI_Init();

// Ця функція вже визначена в d_main.cpp
// void AI_Shutdown();

// Функція логування з рівнем деталізації
void AI_Log(AIDebugLevel level, const char* format, ...);

// Функції для отримання даних
FString GetEnvironmentDescription(int player_num);
