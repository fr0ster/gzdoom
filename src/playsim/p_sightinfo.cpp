#include "p_sightinfo.h"
#include "ai_config.h"
#include "d_player.h"
#include "p_local.h"

// Функції UpdateVisibleObjects, TrackMonsters та UpdateEnvironmentInfo 
// вже визначені в d_main.cpp як заглушки.
// В майбутньому ці функції потрібно буде перенести з d_main.cpp сюди.

// Функція для отримання опису навколишнього середовища
FString GetEnvironmentDescription(player_t* player)
{
    if (!player || !player->mo) 
        return "Invalid player";
    
    FString envInfo;
    
    // Базова інформація про позицію та стан гравця
    envInfo.AppendFormat("Position: (%.1f, %.1f, %.1f) | ", 
                        player->mo->X(), player->mo->Y(), player->mo->Z());
    envInfo.AppendFormat("Health: %d | ", player->health);
    
    // Інформація про сектор, в якому знаходиться гравець
    if (player->mo->Sector)
    {
        envInfo.AppendFormat("Sector: %d | ", player->mo->Sector->sectornum);
        envInfo.AppendFormat("Light level: %d | ", player->mo->Sector->lightlevel);
        envInfo.AppendFormat("Floor height: %.1f | ", player->mo->Sector->floorplane.ZatPoint(player->mo->X(), player->mo->Y()));
        envInfo.AppendFormat("Ceiling height: %.1f | ", player->mo->Sector->ceilingplane.ZatPoint(player->mo->X(), player->mo->Y()));
        
        // Додаткова інформація про спеціальні властивості сектора
        if (player->mo->Sector->special)
            envInfo.AppendFormat("Special sector: %d | ", player->mo->Sector->special);
        
        // Інформація про текстури підлоги та стелі
        // Тимчасово вимикаємо логування текстур, поки не знайдемо правильний спосіб доступу до TexMan
        envInfo.AppendFormat("Floor texture ID: %d | ", player->mo->Sector->GetTexture(sector_t::floor));
        envInfo.AppendFormat("Ceiling texture ID: %d | ", player->mo->Sector->GetTexture(sector_t::ceiling));
    }
    
    // Інформація про видимість (освітлення та екстра-світло)
    envInfo.AppendFormat("Extra light: %d | ", player->extralight);
    if (player->fixedcolormap)
        envInfo.AppendFormat("Fixed colormap: %d | ", player->fixedcolormap);
    
    // Інформація про зброю гравця
    if (player->ReadyWeapon)
        envInfo.AppendFormat("Weapon: %s | ", player->ReadyWeapon->GetClass()->TypeName.GetChars());
    
    // Інформація про стан гравця (біг, стрибок, присідання)
    if (player->onground)
        envInfo.AppendFormat("On ground | ");
    else
        envInfo.AppendFormat("In air | ");
    
    if (player->crouching)
        envInfo.AppendFormat("Crouching | ");
    
    if (player->mo->Vel.Length() > 0.1)
        envInfo.AppendFormat("Moving (%.1f) | ", player->mo->Vel.Length());
    else
        envInfo.AppendFormat("Standing | ");
    
    return envInfo;
}
