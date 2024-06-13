#include "ch_scene.h"
#include "ch_game_services.h"
CH_SceneGeneral 
CH_MakeScene(GFX_Renderer* renderer_service, OS_App* app_service)
{
    CH_SceneGeneral scene_general =
    {  
        .services = CH_GameServicesInit(renderer_service, app_service)
    };
  

    return scene_general;
}

void 
CH_ConfigurateScene(CH_SceneGeneral* sg)
{
 

    sg->scenes.menu = CH_MenuCreate(sg->services);
    sg->scenes.game = CH_GameCreate(sg->services);
    
    sg->scenes.game.map_loc = sg->map_loc;
    sg->scenes.game.map = CH_MapLoad( sg->map_loc);
    CH_GameSceneConfigurate(&sg->scenes.game);
    
}

void
CH_RunScene(CH_SceneGeneral* scene_general)
{
    switch (scene_general->scene_type)
    {
        case (SCENE_GAME):
        {
            /* Do whatever with the game scenes. */
            CH_GameRun(&scene_general->scenes.game);
        } break;
        case (SCENE_MENU):
        {
            CH_MenuRun(&scene_general->scenes.menu);
            /* Do whatever with the menu scenes. */
        } break;
        default:
        {
            scene_general->scene_type = SCENE_MENU;
            
        };
    }
}
void
CH_CloseScene(CH_SceneGeneral* scene_general)
{
    // Close all scenes. TODO!
    
}
