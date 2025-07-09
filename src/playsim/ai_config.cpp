#include "ai_config.h"
#include "mcp.h"

// Глобальна конфігурація
AIConfig g_ai_config;

// MCP сервер
static DMCPClient* g_mcp_server = nullptr;

// Ініціалізація системи AI
void AI_Init()
{
    // Завантажуємо конфігурацію з файлу або використовуємо значення за замовчуванням
    if (g_ai_config.use_mcp)
    {
        // Ініціалізуємо MCP сервер
        g_mcp_server = new DMCPClient();
        if (g_mcp_server->Connect(g_ai_config.mcp_address.GetChars(), g_ai_config.mcp_port))
        {
            Printf("AI: Connected to MCP server at %s:%d\n", 
                g_ai_config.mcp_address.GetChars(), g_ai_config.mcp_port);
        }
        else
        {
            Printf("AI: Failed to connect to MCP server\n");
        }
    }
}

// Завершення роботи системи AI
void AI_Shutdown()
{
    if (g_mcp_server)
    {
        delete g_mcp_server;
        g_mcp_server = nullptr;
    }
}

// Отримання опису навколишнього середовища
FString GetEnvironmentDescription(int player_num)
{
    if (player_num < 0 || player_num >= MAXPLAYERS || !players[player_num].mo)
        return "Invalid player";
    
    return players[player_num].GetEnvironmentDescription();
}

// Отримання інформації про монстрів
TArray<MonsterInfo> GetMonstersInfo(int player_num)
{
    if (player_num < 0 || player_num >= MAXPLAYERS || !players[player_num].mo)
        return {};
    
    return players[player_num].monsters_info;
}

// Отримання інформації про навколишнє середовище
EnvironmentInfo GetEnvironmentInfo(int player_num)
{
    if (player_num < 0 || player_num >= MAXPLAYERS || !players[player_num].mo)
        return {};
    
    return players[player_num].environment_info;
}
