#pragma once

#include "d_player.h"
#include "p_local.h"

// Структури вже визначені в d_player.h
// Додаємо нові функції для роботи з даними

// Функції для роботи з видимими об'єктами
void UpdateVisibleObjects(player_t* player);
void TrackMonsters(player_t* player);
void UpdateEnvironmentInfo(player_t* player);
FString GetEnvironmentDescription(player_t* player);
