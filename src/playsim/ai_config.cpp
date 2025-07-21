#include "ai_config.h"
#include "d_player.h"
#include "common/filesystem/include/fs_files.h"
#include "m_misc.h"
#include "cmdlib.h"

// Глобальна конфігурація AI
AIConfig g_ai_config;

// Статична змінна для файлу логу
static FileWriter* g_ai_log_file = nullptr;

// Функція для отримання шляху до файлу логу
FString GetAILogFilePath()
{
    // Якщо шлях вже вказаний в конфігурації, використовуємо його
    if (!g_ai_config.log_file_path.IsEmpty())
        return g_ai_config.log_file_path;
    
    // Інакше використовуємо стандартний шлях до логів
    FString log_dir;
#ifdef _WIN32
    log_dir = M_GetAppDataPath(true);
    log_dir += "/GZDoom/logs/";
#else
    log_dir = "$HOME/.config/gzdoom/logs/";
    log_dir = ExpandEnvVars(log_dir.GetChars());
#endif
    
    // Створюємо директорію, якщо вона не існує
    CreatePath(log_dir.GetChars());
    
    // Формуємо ім'я файлу з датою та часом
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", timeinfo);
    
    FString log_file = log_dir + "ai_vision_" + timestamp + ".log";
    return log_file;
}

// Функція для відкриття файлу логу
bool OpenAILogFile()
{
    if (g_ai_log_file != nullptr)
        return true; // Файл вже відкритий
    
    if (!g_ai_config.log_to_file)
        return false; // Логування у файл вимкнено
    
    FString log_path = GetAILogFilePath();
    g_ai_log_file = FileWriter::Open(log_path.GetChars());
    
    if (g_ai_log_file != nullptr)
    {
        // Записуємо заголовок логу
        time_t now = time(nullptr);
        struct tm* timeinfo = localtime(&now);
        char timestamp[32];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
        
        g_ai_log_file->Printf("=== GZDoom AI Vision Log ===\n");
        g_ai_log_file->Printf("Started: %s\n\n", timestamp);
        return true;
    }
    
    return false;
}

// Функція для закриття файлу логу
void CloseAILogFile()
{
    if (g_ai_log_file != nullptr)
    {
        // Записуємо завершення логу
        time_t now = time(nullptr);
        struct tm* timeinfo = localtime(&now);
        char timestamp[32];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
        
        g_ai_log_file->Printf("\n=== Log Closed ===\n");
        g_ai_log_file->Printf("Ended: %s\n", timestamp);
        
        g_ai_log_file->Close();
        delete g_ai_log_file;
        g_ai_log_file = nullptr;
    }
}

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
    
    // Виводимо в консоль
    VPrintf(print_level, full_message.GetChars(), args);
    
    // Якщо увімкнено логування у файл, перевіряємо, чи файл відкритий
    if (g_ai_config.log_to_file)
    {
        // Перевіряємо, чи файл логу відкритий, якщо ні - спробуємо відкрити
        if (g_ai_log_file == nullptr)
        {
            OpenAILogFile();
        }
        
        // Перевіряємо знову після спроби відкриття
        if (g_ai_log_file != nullptr)
        {
            // Отримуємо поточний час для логу
            time_t now = time(nullptr);
            struct tm* timeinfo = localtime(&now);
            char timestamp[32];
            strftime(timestamp, sizeof(timestamp), "%H:%M:%S", timeinfo);
            
            // Записуємо у файл з часовою міткою
            g_ai_log_file->Printf("[%s] ", timestamp);
            
            // Використовуємо va_list знову, оскільки vprintf споживає його
            va_list args_copy;
            va_copy(args_copy, args);
            
            // Форматуємо повідомлення для запису у файл за допомогою vsnprintf
            char buffer[4096]; // Достатньо великий буфер для повідомлень
            vsnprintf(buffer, sizeof(buffer), full_message.GetChars(), args_copy);
            g_ai_log_file->Printf("%s", buffer);
            
            va_end(args_copy);
        }
        else
        {
            // Якщо не вдалося відкрити файл, вимикаємо логування у файл
            g_ai_config.log_to_file = false;
            Printf(PRINT_HIGH, "AI Vision: Failed to open log file, file logging disabled\n");
        }
    }
    
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
    
    // Вимикаємо логування у файл для діагностики
    g_ai_config.log_to_file = false;
    
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
    AI_Log(AI_DEBUG_INFO, "  - Log to file: %s\n", g_ai_config.log_to_file ? "Yes" : "No");
    
    AI_Log(AI_DEBUG_INFO, "=== AI system initialized successfully ===\n");
    Printf(PRINT_HIGH, "AI system initialized with debug output enabled.\n");
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
