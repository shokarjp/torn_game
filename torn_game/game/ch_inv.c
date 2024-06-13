#include "ch_inv.h"




CH_InvMgr 
CH_CreateInventory(V2F window_size)
{
    CH_InvMgr mgr = {0};
    mgr.inventory.tiles = MEM_ArenaAlloc(MEM_GetDefaultArena(), sizeof(GFX_Rect) * 8);
    mgr.inventory.tile_count = 8;
    mgr.selected_id = 9;

    // Create the rectangles and position them releative to form a 'snap grid' 
    i32 inventory_scale = 64;
    i32 tile_padding = 10;
    V2F prev_pos = v2((window_size.x /2 ) - ((mgr.inventory.tile_count * inventory_scale)/1.5),window_size.h - inventory_scale - tile_padding-25); // At the inital part, it will serve as the origin.

    for (int i = 0; i< mgr.inventory.tile_count - 1; i++)
    {

        V2F calculated_pos = v2(   
            prev_pos.x + (inventory_scale) + tile_padding,
            prev_pos.y
        );
        prev_pos = calculated_pos;
        mgr.inventory.tiles[    mgr.inventory.tile_used++].inventory_tile  = GFX_CreateRect(v2(inventory_scale,inventory_scale), calculated_pos);
    }
    

    return mgr;
}
void
CH_DrawInventory(CH_InvMgr* inv, OS_App* window, GFX_Renderer* renderer)
{
    
    for (int i = 0;
        i < inv->inventory.tile_used;
        i++)
    {
        // Let's update the sprites releative to the players' mouseHover.
        GFX_Rect* active_rectangle = &inv->inventory.tiles[i].inventory_tile;
        if (UI_PointInRect(OS_GetMousePosition(window), *active_rectangle))
        {
            // Okay! We are hovering over that rect.
            if (OS_GetLeftMouseState().clicked)
            {
                // Pressed! 
                GFX_SetRectColor(active_rectangle, v4(160,160,160,255));
                inv->selected_id = i;
            } else if (inv->selected_id != i) GFX_SetRectColor(active_rectangle, v4(100,100,100,255));
            
        }  else if (inv->selected_id != i) GFX_SetRectColor(active_rectangle, v4(255,255,255,255));
         
        // Draws the overall sprites
        GFX_DrawRect(active_rectangle, renderer);
    }
}

i32 
CH_GetInvIdForItems(CH_InvMgr* mgr)
{
    return (
        mgr->inventory.tiles[mgr->selected_id].item_id
    );

}