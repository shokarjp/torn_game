#include "ch_entity.h"
#include "../torn.h"
#include <math.h>
CH_Entity 
CH_CreateEntity(CH_EntityPassThrough* passthrough, V2F pos)
{
    CH_Entity entity = (CH_Entity)
    {
        .base = GFX_CreateRect(v2(200, 200), pos),
        .pt = passthrough
    };
    if (entity.pt->texture.data != 0)
    GFX_SetRectTexture(&entity.base, entity.pt->texture);
    
    return entity;
}

void 
CH_EntityDraw( CH_Entity* entity, GFX_Renderer* renderer, OS_App* app)
{
     
    if (entity->pt->flag & CH_ENTITY_FOLLOW)
    {
        
        V2F direction = v2(
          entity->base.pos.x - entity->pt->pos_to_follow.x,
         entity->base.pos.y - entity->pt->pos_to_follow.y
        );
        
        r32 mag = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (mag <= entity->pt->follow_distance)
        {
            if (mag > 10){
                // normalization for the velocity vector.
            V2F dir_norm = v2(
                    direction.x / mag,
                    direction.y / mag
                );

            entity->velocity.x = -dir_norm.x;
                entity->velocity.y = -dir_norm.y;
        }
        }
    }
        entity->velocity.x *= 0.9;
    entity->velocity.y *= 0.9;
    entity->base.pos.x += entity->velocity.x * entity->pt->speed;
    entity->base.pos.y += entity->velocity.y * entity->pt->speed;
    if (entity->pt->flag & CH_ENTITY_FLOAT)
    {
        
        entity->base.pos.y +=   sin(OS_GetTime(app) * 3) ;
    }
    GFX_DrawRect(&entity->base, renderer);
}   