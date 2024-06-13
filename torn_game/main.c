#include "base/settings.h"
#include "gfx/gfx.h"
#include "gfx/gfx_2d.h"
#include "os/os.h"
#include "torn.h"
#include "assert.h"
#include "game/ch_scene.h"
#include "third-party/inireader/iniread.h"
#include "game/ch_entity.h"
#include "bridge/ch_parse_entities.h"
#include "ui/widgets.h"

#include "game/ch_inv.h"
i32 main(void)
{
    TORN_Init();
    
    /////////////////////////////////////////////////////////////////
    OS_App* app = OS_ConstructApp(("game-maker contest"), 
                                  v2(1200,700),
                                  OS_AppDefault,
                                  OS_AppStyleDefault);
    assert(app && "Failed to create window");
    /////////////////////////////////////////////////////////////////
    
    GFX_Renderer* renderer = GFX_CreateRenderer(app);
    assert(renderer && "Failed to create renderer");
   
    CH_SceneGeneral sg= CH_MakeScene(renderer, app);

    iniread_t file = iniread_open("game_metadata/game.ini");

    if (file.status)
    {
        TORN_Error("The game can't continue, important asset file, game_metadata/game.ini, is missing/corrupted/invalid.", "error while parsing ini file");
        TORN_Error(iniread_get_error(file), "Error!");
        return 0x1;
    }

    iniread_key_t map = iniread_get_key(file, "meta",
                                            "map_loc"); 
    iniread_key_t vs0 = iniread_get_key(file, "shaders",
                                            "vs0"); 
    iniread_key_t fs0 = iniread_get_key(file, "shaders",
                                            "fs0");
                                            
    iniread_key_t vs1 = iniread_get_key(file, "shaders",
                                            "vs1"); 
    iniread_key_t fs1 = iniread_get_key(file, "shaders",
                                            "fs1");  
        iniread_key_t vs2 = iniread_get_key(file, "shaders",
                                            "vs2"); 
    iniread_key_t fs2 = iniread_get_key(file, "shaders",
                                            "fs2");  
    
    sg.scene_type = SCENE_GAME;
    if (map.type != INIREAD_STRING || file.status) 
    {
        TORN_Error("malformed data input", "error while parsing ini file.");
        TORN_Error(iniread_get_error(file), "Error!");
        return 0x2;
    }
    
    if (vs0.type != INIREAD_STRING || file.status) 
    {
        TORN_Error("malformed data input", "error while parsing ini file.");
        TORN_Error(iniread_get_error(file), "Error!");
        return 0x2;
    }
    if (fs0.type != INIREAD_STRING || file.status) 
    {
        TORN_Error("malformed data input", "error while parsing ini file.");
        TORN_Error(iniread_get_error(file), "Error!");
        return 0x2;
    }
       if (vs1.type != INIREAD_STRING || file.status) 
    {
        TORN_Error("malformed data input", "error while parsing ini file.");
        TORN_Error(iniread_get_error(file), "Error!");
        return 0x2;
    }
   if (fs1.type != INIREAD_STRING || file.status) 
    {
        TORN_Error("malformed data input", "error while parsing ini file.");
        TORN_Error(iniread_get_error(file), "Error!");
        return 0x2;
    }

  if (vs2.type != INIREAD_STRING || file.status) 
    {
        TORN_Error("malformed data input", "error while parsing ini file.");
        TORN_Error(iniread_get_error(file), "Error!");
        return 0x2;
    }
      if (fs2.type != INIREAD_STRING || file.status) 
    {
        TORN_Error("malformed data input", "error while parsing ini file.");
        TORN_Error(iniread_get_error(file), "Error!");
        return 0x2;
    }
    // Validate whether that map value exists..
    {
        FILE* file_validate = fopen(map.value, "rw");

        if (file_validate == 0) {  TORN_Error("File can not be correctly accessed...", map.value); return 0x3; }
    }
    {
        FILE* file_validate = fopen(fs0.value, "rw");

        if (file_validate == 0) {  TORN_Error("File can not be correctly accessed...", fs0.value); return 0x3; }
    }
    {
        FILE* file_validate = fopen(vs0.value, "rw");

        if (file_validate == 0) {  TORN_Error("File can not be correctly accessed...", vs0.value); return 0x3; }
    }
    {
        FILE* file_validate = fopen(vs1.value, "rw");

        if (file_validate == 0) {  TORN_Error("File can not be correctly accessed...", vs0.value); return 0x3; }
    }
        {
        FILE* file_validate = fopen(fs1.value, "rw");

        if (file_validate == 0) {  TORN_Error("File can not be correctly accessed...", fs1.value); return 0x3; }
    }
       {
        FILE* file_validate = fopen(vs2.value, "rw");

        if (file_validate == 0) {  TORN_Error("File can not be correctly accessed...", vs2.value); return 0x3; }
    }
       {
        FILE* file_validate = fopen(fs2.value, "rw");

        if (file_validate == 0) {  TORN_Error("File can not be correctly accessed...", fs2.value); return 0x3; }
    }
    
    sg.map_loc = map.value;
    CH_ConfigurateScene(&sg);

    GFX_SetClearColor(v4(20,20,20,0));

    // Post Processing Soon (?)
    // Texture Support -> Animation Engine ...
    // 
 
    GFX_Framebuffer framebuffer = GFX_CreateFramebuffer(renderer, GFX_Format_RGB);
    
    /////////////////////////////////////////////////
    GFX_Rect        framebuffer_rectangle = GFX_CreateRect(v2(app->size.w, app->size.h), v2(0,0));
    framebuffer_rectangle.texture = framebuffer.texture;
    GFX_FlipRectUV(&framebuffer_rectangle);
    /////////////////////////////////////////////////
 
    GFX_Shader shader = GFX_CreateShader(OS_ReadFile(vs0.value), OS_ReadFile(fs0.value));
    GFX_ConfigureShader(&shader, renderer);
    GFX_GLSLShader2f(&shader, "u_res",  (app->size.w),   (app->size.h));


    GFX_Framebuffer bl_lightspots = GFX_CreateFramebuffer(renderer, GFX_Format_RGBA);
    GFX_Rect        bl_lightspots_rect = GFX_CreateRect(v2(app->size.w, app->size.h), v2(0,0));
    bl_lightspots_rect.texture = bl_lightspots.texture;
    GFX_FlipRectUV(&bl_lightspots_rect);
 
    GFX_Shader shd_lightspots = GFX_CreateShader(OS_ReadFile(vs1.value), OS_ReadFile(fs1.value));
    
    GFX_ConfigureShader(&shd_lightspots, renderer);
    GFX_GLSLShader2f(&shd_lightspots, "u_res",  (app->size.w),   (app->size.h));


    // Gaussian Blur Layer
    GFX_Framebuffer bl_gb = GFX_CreateFramebuffer(renderer, GFX_Format_RGBA);
    GFX_Rect        bl_gb_rect = GFX_CreateRect(v2(app->size.w, app->size.h), v2(0,0));
    bl_gb_rect.texture = bl_gb.texture;
    GFX_FlipRectUV(&bl_gb_rect);
 
    GFX_Shader shd_bl_gb = GFX_CreateShader(OS_ReadFile(vs2.value), OS_ReadFile(fs2.value));
    
    GFX_ConfigureShader(&shd_bl_gb, renderer);
    GFX_GLSLShader2f(&shd_bl_gb, "u_res",  (app->size.w),   (app->size.h));



    // The following is for different variants of entites
    // TODO(jpshokar): the ability to parse and read from an ini file systematicallty.
     CH_EntityPassThrough passthrough = (CH_EntityPassThrough)
     {
        .flag = 0b00000011,
        .follow_distance = 50,
        .id = 9,
        .attack_damage = 50,
        .speed = 2,
        .pos_to_follow = v2(500,0)
     };

     V2F follow_position = v2(0,0);

     CH_EntityTable table = CH_EntityTableInit();
     CH_LoadEntityTableFromINI(&table, "game_metadata//entity.ini");


     CH_Entity dummy = CH_CreateEntity(&table.passthroughs[0], v2(100,100));

        GFX_Font font = GFX_CreateFont("assets//Roboto-Light.ttf", 20);
            UI_Button button = UI_CreateButton(font, "go to 0,0", v2(150,50), v2(0,0));

        GFX_Text text = GFX_CreateText("github.com/jpshokar", v2(app->size.w-30,app->size.h-30), font);


        CH_InvMgr manager = CH_CreateInventory(v2(app->size.x, app->size.y));


    while (app->running)

    {
        dummy.pt->pos_to_follow = v2(sg.scenes.game.player.position.x - sg.scenes.game.player.base.size.x/2, sg.scenes.game.player.position.y - sg.scenes.game.player.base.size.y/2) ;
        OS_PollEvents(app);
 
        GFX_PushFramebuffer(framebuffer); {
            if (dummy.base.pos.x >= 500 && dummy.base.pos.y == 0)
            {
                follow_position.y = -100;
            } 
            if (dummy.base.pos.x >= 500 && dummy.base.pos.y <= -100)
            {
                follow_position.x = 0;
            } 
            if (dummy.base.pos.x == 0 && dummy.base.pos.y == -100)
            {
                follow_position.y = 0;
            } 
         GFX_Clear(renderer);
         CH_RunScene(&sg);
         CH_EntityDraw(&dummy, renderer, app);
        } GFX_PopFramebuffer();
            /////////////////////////////////////////////////
        
        GFX_PushFramebuffer(bl_lightspots);
        GFX_Clear(renderer);
                        GFX_PushShader(shader);

        GFX_DrawRect(&framebuffer_rectangle, renderer);
                        GFX_PopShader();

         GFX_PopFramebuffer();
        /////////////////////////////////////////////////
         GFX_PushFramebuffer(bl_gb); {
         GFX_Clear(renderer) ;
         GFX_PushShader(shd_lightspots);
         GFX_DrawRect(&bl_lightspots_rect, renderer);
         GFX_PopShader();

         } GFX_PopFramebuffer();

         

         GFX_PushShader(shd_bl_gb);
         GFX_Clear(renderer);
         GFX_DrawRect(&bl_gb_rect, renderer);
         GFX_DrawText(&text, renderer);
                 
                          CH_DrawInventory(&manager,app, renderer);


            UI_UpdateButton(&button, &app);
            UI_DrawButton(&button, renderer);
            if (UI_GetButtonSignal(&button, app).clicked)
            {
                
            }

         GFX_PopShader();


  

         GFX_Present(renderer);
         
    }
    
    TORN_Destroy();
    return 0;
}

