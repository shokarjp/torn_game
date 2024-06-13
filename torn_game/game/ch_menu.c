#include "ch_scene.h"

CH_Menu 
CH_MenuCreate(CH_GameServices* services)
{
    CH_Menu menu = (CH_Menu)
    {
        .rectangle = GFX_CreateRect(v2(100,100), v2(120,120))
    };
    menu.services = services;

    return menu;
}

void 
CH_MenuRun(CH_Menu* menu)
{
   
    GFX_DrawRect(&menu->rectangle, menu->services->renderer);
}