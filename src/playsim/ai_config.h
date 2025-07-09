#pragma once

#include "d_player.h"
#include "p_sightinfo.h"
#include "mcp.h"

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
};

// Глобальна конфігурація
extern AIConfig g_ai_config;

// Функції для ініціалізації та завершення
void AI_Init();
void AI_Shutdown();

// Функції для отримання даних
FString GetEnvironmentDescription(int player_num);
TArray<MonsterInfo> GetMonstersInfo(int player_num);
EnvironmentInfo GetEnvironmentInfo(int player_num);
