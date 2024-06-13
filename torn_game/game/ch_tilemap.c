#include "ch_tilemap.h"
#include "ch_game_services.h"
CH_TileMap CH_MapLoad(char* file)
{
    CH_TileMap tm = {0};
    tm.raw_map = OS_ReadFile(file);
    i32 tilemap_w = 64;
    i32 tilemap_h = 18;
    tm.tilemap_w = tilemap_w;
    tm.tilemap_h = tilemap_h;
    i32 tile_w = 64;
    i32 tile_h = 64;
    tm.tiles = MEM_ArenaAlloc(MEM_GetDefaultArena(), sizeof(GFX_Rect) * (tilemap_w*tilemap_h));

  
   i32 rows = 0, columns = 0;
    i32 index = 0;
    V2F plr_start_tile = v2(0,0);
    GFX_Texture2D texture = GFX_LoadTexture2D("assets//tile.png");
   for (int i = 0; i < U_GetTextLength(tm.raw_map); i++)
   {
    if (tm.raw_map[i] != '\n') { 
        if (tm.raw_map[i] == '1') {
            tm.tiles[index] = GFX_CreateRect(v2(tile_w, tile_h), v2((columns * tile_w) , (rows * tile_h) ));
            tm.tiles[index++].texture = texture;
        }
        if (tm.raw_map[i] == '0') plr_start_tile =v2((columns * tile_w) , (rows * tile_h) );
        columns += 1;
    }

    else if (tm.raw_map[i] != '\0') { columns = 0; rows += 1;}
    

    


   }
   printf("(+%i tiles produced)\n", index);
    tm.tiles_used = index;
    tm.startpoint = plr_start_tile;
    return tm;
}
char CH_GetTile(i32 x, i32 y, CH_TileMap map)
{
    if  (x >= 0 && x < map.tilemap_w && y >= 0 && y < map.tilemap_h)
    return map.raw_map[y * map.tilemap_w + x];
    return ' ';
}
void CH_MapDraw(CH_TileMap* map, CH_GameServices* services) 
{
    
    for (int i = 0; i < map->tiles_used; i++)
    {
        GFX_DrawRect(&map->tiles[i], services->renderer);
    }
}