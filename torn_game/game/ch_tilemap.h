#ifndef CH_TILEMAP
#define CH_TILEMAP
#include "../torn.h"
#include "ch_game_services.h"
typedef struct CH_TileMap CH_TileMap;
struct CH_TileMap
{
    char* raw_map;
    
    GFX_Rect* tiles;
    i32 tiles_used;
    i32 tiles_size;
    V2F startpoint;

    i32 tilemap_w , tilemap_h;

};

CH_TileMap CH_MapLoad(char* file);
void CH_MapDraw(CH_TileMap* map, CH_GameServices* services);
char CH_GetTile(i32 x, i32 y, CH_TileMap map);


#endif