#ifndef CH_PLAYER
#define CH_PLAYER
#include "../torn.h"
#include "ch_game_services.h"
#include "ch_tilemap.h"
typedef struct CH_Player CH_Player;
struct CH_Player
{
    V2F position;
    V2F velocity;
    r32 health;
    GFX_Rect base;

    GFX_Texture2D player_texture;
 
};

CH_Player CH_InitPlayer(V2F position);
void CH_DrawPlayer(CH_Player* player, CH_GameServices* services, CH_TileMap* tilemap);


#endif