#ifndef CH_SCENE
#define CH_SCENE 
#include "../torn.h"
#include "ch_player.h"
#include "ch_game_services.h"
#include "ch_tilemap.h"

typedef struct CH_Menu CH_Menu;
struct CH_Menu
{
    GFX_Rect rectangle; 
    CH_GameServices* services;

};

typedef struct CH_Game CH_Game;
struct CH_Game
{
    CH_Player player;
    CH_GameServices* services;
    CH_TileMap map;
    GFX_View view;  
     
    u8* map_loc;
};


typedef enum CH_ActiveScene CH_ActiveScene;
enum CH_ActiveScene {
    SCENE_GAME,
    SCENE_MENU
};

typedef struct CH_SceneGeneral CH_SceneGeneral;

struct CH_SceneGeneral
{
    u8* map_loc;
    union
    {   
        CH_Menu menu;
        CH_Game game;
    } scenes;

    CH_GameServices* services;
    CH_ActiveScene scene_type;

};


CH_SceneGeneral CH_MakeScene(GFX_Renderer* renderer_service, OS_App* app_service);
void CH_RunScene(CH_SceneGeneral* scene_general);
void CH_CloseScene(CH_SceneGeneral* scene_general);
void CH_ConfigurateScene(CH_SceneGeneral* sg);

void CH_MenuRun(CH_Menu* menu);
CH_Menu CH_MenuCreate(CH_GameServices* services);

void CH_GameRun(CH_Game* game);
void CH_GameSceneConfigurate(CH_Game* game);
CH_Game CH_GameCreate(CH_GameServices* services);

#endif
