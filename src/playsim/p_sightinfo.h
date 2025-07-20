#pragma once

#include "d_player.h"
#include "p_local.h"

// Структури вже визначені в d_player.h
// Додаємо нові функції для роботи з даними

// Ці функції вже визначені в d_main.cpp як заглушки
// void UpdateVisibleObjects(player_t* player);
// void TrackMonsters(player_t* player);
// void UpdateEnvironmentInfo(player_t* player);

// Функція для отримання опису навколишнього середовища
FString GetEnvironmentDescription(player_t* player);
