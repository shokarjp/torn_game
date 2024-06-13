#include "ch_player.h"
#include "ch_tilemap.h"
#include "ch_collision.h"
CH_Player CH_InitPlayer(V2F position){
    CH_Player player = (CH_Player)
    {
        .base = GFX_CreateRect(v2(64,64), v2(0,0)),
        .position = position
        
    };
    GFX_SetRectColor(&player.base, v4(255,255,255,255));
    player.player_texture = GFX_LoadTexture2D("assets//plr.png");
     player.base.texture = player.player_texture;
    return player;
}

i32 CH_CollisionAABB(GFX_Rect a, GFX_Rect b)
{
    return a.pos.x < b.pos.x + b.size.x &&
           a.pos.x + a.size.x > b.pos.x &&
           a.pos.y < b.pos.y + b.size.y &&
           a.pos.y + a.size.y > b.pos.y;
}




i32 CH_Sign(r32 val)
{ 
    return val > 0 ? 1 : -1;
}
void CH_DrawPlayer(CH_Player* player, CH_GameServices* services, CH_TileMap* tilemap)
{
   
 
 if (OS_GetKeyState('w').pressed) player->velocity.y = -4.8;
    if (OS_GetKeyState('s').pressed) player->velocity.y = 4.8;
    if (OS_GetKeyState('a').pressed) 
    {
        player->base.uv.top_left     = v2(1,0);
        player->base.uv.top_right    = v2(0,0);
        player->base.uv.bottom_left  = v2(1,1);
        player->base.uv.bottom_right = v2(0,1);   
         player->velocity.x = -4.8;
    }
    if (OS_GetKeyState('d').pressed)
    {
        player->base.uv.top_left     = v2(0,0);
        player->base.uv.top_right    = v2(1,0);
        player->base.uv.bottom_left  = v2(0,1);
        player->base.uv.bottom_right = v2(1,1);   
        player->velocity.x = 4.8;
    }
     
     player->velocity.x *= 0.9;
    player->velocity.y *= 0.9;
    player->position.y += player->velocity.y;
    player->position.x += player->velocity.x;
       

    for (i32 i = 0; i < tilemap->tiles_used; i++)
    {
        
        
        #if 1
        i32 dx = tilemap->tiles[i].pos.x - player->position.x;
        i32 dy = tilemap->tiles[i].pos.y - player->position.y;
        
        i32 int_x = abs(dx) - ((tilemap->tiles[i].size.x / 2) + (player->base.size.x/2) );
        i32 int_y = abs(dy) - ((tilemap->tiles[i].size.y / 2) + (player->base.size.y/2) );


        if (int_x < 0.0f && int_y < 0.0f)
        {
            
            
            if (int_x >= int_y)
            {   
                player->velocity.x = 0;
    
                if (dx > 0.0f) {  player->position.x =  round(player->position.x +  int_x ) ;  } 
                else  player->position.x  = round( player->position.x + -int_x ) ;
                
                
            }
            else{
                 
                player->velocity.y = 0;
    
                if (dy > 0.0f) {  player->position.y =  round(player->position.y +  int_y ) ;  } 
                else  player->position.y  = round( player->position.y + -int_y ) ;
                
            }

        }
            #endif
    }
        
    player->base.pos = v3(player->position.x, player->position.y, 0 /* zero deosn't matter, this inquiry was initally to add 3D support to the engine, right now it's just a stub unless 3D capabilities are introduced. */);
    GFX_DrawRect(&player->base, services->renderer);
}