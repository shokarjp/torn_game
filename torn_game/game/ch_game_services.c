#include "ch_game_services.h"



CH_GameServices*
CH_GameServicesInit(GFX_Renderer* renderer, OS_App* app)
{
    CH_GameServices* gs = MEM_ArenaAlloc(MEM_GetDefaultArena(), sizeof(CH_GameServices));
    
    *gs = (CH_GameServices)
    {
        .renderer = renderer,
        .app = app,
        .shader = &renderer->default_shader
    };
    printf("%i\n", renderer->default_shader.program);
    return gs;
}