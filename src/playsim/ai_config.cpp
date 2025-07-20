#include "ai_config.h"
#include "d_player.h"

// Глобальна конфігурація AI
AIConfig g_ai_config;

// Функція логування з рівнем деталізації
void AI_Log(AIDebugLevel level, const char* format, ...)
{
    // Перевіряємо чи потрібно виводити лог з цим рівнем
    if (!g_ai_config.debug_info || level > g_ai_config.debug_level)
        return;
    
    // Формуємо префікс залежно від рівня логування
    const char* prefix = "";
    int print_level = PRINT_HIGH;
    
    switch (level)
    {
        case AI_DEBUG_ERROR:
            prefix = "[AI ERROR] ";
            print_level = PRINT_HIGH;
            break;
        case AI_DEBUG_WARNING:
            prefix = "[AI WARNING] ";
            print_level = PRINT_HIGH;
            break;
        case AI_DEBUG_INFO:
            prefix = "[AI INFO] ";
            print_level = PRINT_MEDIUM;
            break;
        case AI_DEBUG_VERBOSE:
            prefix = "[AI VERBOSE] ";
            print_level = PRINT_MEDIUM;
            break;
        case AI_DEBUG_TRACE:
            prefix = "[AI TRACE] ";
            print_level = PRINT_LOW;
            break;
        default:
            break;
    }
    
    // Формуємо повне повідомлення з префіксом
    FString full_message;
    full_message.Format("%s%s", prefix, format);
    
    // Використовуємо va_list для передачі аргументів
    va_list args;
    va_start(args, format);
    VPrintf(print_level, full_message.GetChars(), args);
    va_end(args);
}

// Ініціалізація системи AI
void AI_Init()
{
    // Встановлюємо базові параметри
    g_ai_config.enabled = true;
    g_ai_config.debug_info = true;
    g_ai_config.update_interval = 0.1f;
    g_ai_config.max_monsters = 10;
    g_ai_config.max_distance = 1000;
    g_ai_config.debug_level = AI_DEBUG_INFO; // За замовчуванням виводимо інформаційні повідомлення
    g_ai_config.log_frequency = 100; // Виводити логи кожні 100 викликів
    
    // Виводимо інформацію про конфігурацію
    AI_Log(AI_DEBUG_INFO, "=== Initializing AI system... ===\n");
    AI_Log(AI_DEBUG_INFO, "AI Configuration:\n");
    AI_Log(AI_DEBUG_INFO, "  - Enabled: %s\n", g_ai_config.enabled ? "Yes" : "No");
    AI_Log(AI_DEBUG_INFO, "  - Debug: %s\n", g_ai_config.debug_info ? "Yes" : "No");
    AI_Log(AI_DEBUG_INFO, "  - Debug level: %d\n", g_ai_config.debug_level);
    AI_Log(AI_DEBUG_INFO, "  - Log frequency: %d calls\n", g_ai_config.log_frequency);
    AI_Log(AI_DEBUG_INFO, "  - Update interval: %.2f seconds\n", g_ai_config.update_interval);
    AI_Log(AI_DEBUG_INFO, "  - Max monsters: %d\n", g_ai_config.max_monsters);
    AI_Log(AI_DEBUG_INFO, "  - Max distance: %d\n", g_ai_config.max_distance);
    
    AI_Log(AI_DEBUG_INFO, "=== AI system initialized successfully ===\n");
}

// Завершення роботи системи AI вже визначено в d_main.cpp
// void AI_Shutdown()
// {
//     Printf(PRINT_HIGH, "AI_Shutdown called\n");
//     
//     g_ai_config.enabled = false;
// }

// Отримання опису навколишнього середовища
FString GetEnvironmentDescription(int player_num)
{
    if (player_num < 0 || player_num >= MAXPLAYERS || !players[player_num].mo)
        return "Invalid player";
    
    return "Player environment info";
}
