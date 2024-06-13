#ifndef CH_ENTITY_H
#define CH_ENTITY_H

#include "../torn.h"

typedef enum CH_EntityFlag CH_EntityFlag;
enum CH_EntityFlag
{
    CH_ENTITY_ATTACK = 0b00000001, // This will ensure that the entity will attack the player whenever he's near.
    CH_ENTITY_FOLLOW = 0b00000010,  // This will ensure that the entity will follow the player.
    CH_ENTITY_FLOAT  = 0b00000100

};


// CH_EntitySmartFlag is a special structure and requires the parameters listed to work - it's a passthrough because
// most of these values actually do come from an ini file. (see: entity.ini)

typedef struct CH_EntityPassThrough CH_EntityPassThrough;
struct CH_EntityPassThrough
{
    CH_EntityFlag flag;
    i32 follow_distance;
    i32 attack_damage;
    i32 id;
    V2F pos_to_follow;
    r32 speed;
    GFX_Texture2D texture;

};

typedef struct CH_Entity CH_Entity;
struct CH_Entity
{
    GFX_Rect base;
    CH_EntityPassThrough* pt;    
    V2F velocity;
    
};


CH_Entity CH_CreateEntity(CH_EntityPassThrough* passthrough, V2F pos);


void CH_EntityDraw( CH_Entity* entity, GFX_Renderer* renderer, OS_App* app);


#endif