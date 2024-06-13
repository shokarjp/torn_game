#ifndef CH_GAME_SERVICES
#define CH_GAME_SERVICES
#include "../torn.h"
typedef struct CH_GameServices CH_GameServices;
struct CH_GameServices
{
    GFX_Renderer* renderer;
    OS_App* app;
    GFX_Shader* shader;
};

CH_GameServices* CH_GameServicesInit(GFX_Renderer* renderer, OS_App* app);


#endif