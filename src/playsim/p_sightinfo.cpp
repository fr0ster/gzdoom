#include "p_sightinfo.h"
#include "ai_config.h"

// Оновлюємо список видимих об'єктів
void UpdateVisibleObjects(player_t* player)
{
    if (!player || !player->mo) return;
    
    player->visible_objects.Clear();
    
    // Перевіряємо всі актори на мапі
    for (AActor* actor : AllActors())
    {
        if (actor == player->mo) continue;
        
        // Перевіряємо чи об'єкт видимий
        if (P_CheckSight(player->mo, actor, 0))
        {
            VisibleObject obj;
            obj.actor = actor;
            obj.distance = player->mo->GetDistance(actor);
            obj.angle = player->mo->GetAngleTo(actor);
            obj.timestamp = I_GetTimeMS();
            
            player->visible_objects.Push(obj);
        }
    }
}

// Відстежуємо монстрів
void TrackMonsters(player_t* player)
{
    if (!player || !player->mo) return;
    
    player->monsters_info.Clear();
    
    // Перевіряємо всі видимі об'єкти
    for (VisibleObject& obj : player->visible_objects)
    {
        if (obj.actor && obj.actor->IsMonster())
        {
            MonsterInfo monster;
            monster.monster = obj.actor;
            monster.distance = obj.distance;
            monster.angle = obj.angle;
            monster.health = obj.actor->health;
            monster.speed = obj.actor->speed;
            monster.is_attacking = obj.actor->flags2 & MF2_ATTACKING;
            monster.attack_range = obj.actor->GetState()->attackrange;
            monster.weapon_type = obj.actor->GetState()->weapon;
            monster.last_seen = obj.timestamp;
            
            player->monsters_info.Push(monster);
        }
    }
}

// Оновлюємо інформацію про навколишнє середовище
void UpdateEnvironmentInfo(player_t* player)
{
    if (!player || !player->mo) return;
    
    player->environment_info.current_sector = player->mo->Sector->sector;
    player->environment_info.floor_height = player->mo->Sector->GetSecPlane(sector_t::floor).height;
    player->environment_info.ceiling_height = player->mo->Sector->GetSecPlane(sector_t::ceiling).height;
    
    // Перевіряємо освітлення
    player->environment_info.is_dark = player->mo->Sector->GetLightLevel() < 128;
    
    // Перевіряємо рідини
    player->environment_info.has_lava = player->mo->Sector->HasLava();
    player->environment_info.has_water = player->mo->Sector->HasWater();
    
    // Перевіряємо чи на вулиці
    player->environment_info.is_outdoor = player->mo->Sector->IsOutdoor();
    
    // Знаходимо найближчий вихід
    player->environment_info.nearest_exit = -1;
    player->environment_info.nearest_distance = 999999;
    
    for (AActor* item : AllActors())
    {
        if (item->GetState()->type == NAME_Exit)
        {
            double dist = player->mo->GetDistance(item);
            if (dist < player->environment_info.nearest_distance)
            {
                player->environment_info.nearest_distance = dist;
                player->environment_info.nearest_exit = item->tid;
            }
        }
    }
}

// Отримуємо опис навколишнього середовища
FString GetEnvironmentDescription(player_t* player)
{
    if (!player) return "Invalid player";
    
    FString desc;
    
    // Формуємо опис середовища
    desc.Format("Sector %d, Distance to exit: %f, Monsters: %d",
        player->environment_info.current_sector,
        player->environment_info.nearest_distance,
        player->monsters_info.Size());
    
    // Якщо використовуємо MCP, відправляємо дані
    if (g_ai_config.use_mcp && g_mcp_server && g_mcp_server->IsConnected())
    {
        // Формуємо JSON для MCP
        FString json = "{\"environment\": {";
        json += "\"current_sector\": " + FString::FromInt(player->environment_info.current_sector) + ", ";
        json += "\"floor_height\": " + FString::FromDouble(player->environment_info.floor_height) + ", ";
        json += "\"ceiling_height\": " + FString::FromDouble(player->environment_info.ceiling_height) + ", ";
        json += "\"is_dark\": " + FString::FromBool(player->environment_info.is_dark) + ", ";
        json += "\"has_lava\": " + FString::FromBool(player->environment_info.has_lava) + ", ";
        json += "\"has_water\": " + FString::FromBool(player->environment_info.has_water) + ", ";
        json += "\"is_outdoor\": " + FString::FromBool(player->environment_info.is_outdoor) + ", ";
        json += "\"nearest_exit\": " + FString::FromInt(player->environment_info.nearest_exit) + ", ";
        json += "\"nearest_distance\": " + FString::FromDouble(player->environment_info.nearest_distance) + "}, ";
        
        // Додаємо монстрів
        json += "\"monsters\": [";
        for (int i = 0; i < player->monsters_info.Size(); i++)
        {
            if (i > 0) json += ", ";
            MonsterInfo& monster = player->monsters_info[i];
            json += "{\"distance\": " + FString::FromDouble(monster.distance) + ", ";
            json += "\"angle\": " + FString::FromDouble(monster.angle) + ", ";
            json += "\"health\": " + FString::FromDouble(monster.health) + ", ";
            json += "\"speed\": " + FString::FromDouble(monster.speed) + ", ";
            json += "\"is_attacking\": " + FString::FromBool(monster.is_attacking) + ", ";
            json += "\"attack_range\": " + FString::FromDouble(monster.attack_range) + ", ";
            json += "\"weapon_type\": " + FString::FromInt(monster.weapon_type) + ", ";
            json += "\"last_seen\": " + FString::FromDouble(monster.last_seen) + "}";
        }
        json += "]}";
        
        // Відправляємо дані через MCP
        g_mcp_server->SendData(json);
    }
    
    return desc;
}
