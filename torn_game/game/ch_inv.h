#ifndef CH_INV_H
#define CH_INV_H
#include "../torn.h"

typedef struct CH_InvTile CH_InvTile;
struct CH_InvTile
{   
    GFX_Rect inventory_tile;
    i32 item_id;
};

typedef struct CH_InvMgr CH_InvMgr;
struct CH_InvMgr
{
    struct {
        CH_InvTile* tiles;
        i32 tile_count;
        i32 tile_used;
    } inventory;


    i32 selected_id; // You can map this to the ID values for all inv items.   
};
i32 CH_GetInvIdForItems(CH_InvMgr* mgr);
CH_InvMgr CH_CreateInventory(V2F window_size);
void CH_DrawInventory(CH_InvMgr* mgr, OS_App* window, GFX_Renderer* renderer);

#endif