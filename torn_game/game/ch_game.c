#include "ch_player.h"
#include "ch_scene.h"
#include "ch_tilemap.h"
CH_Game
CH_GameCreate(CH_GameServices* services)
{
    CH_Game game = {0};
    game.services = services;
 
 

    return game;
}

void 
CH_GameSceneConfigurate(CH_Game* game)
{
    game->player = CH_InitPlayer(game->map.startpoint);

    game->view = GFX_CreateView();
}
void 
CH_GameRun(CH_Game* game)
{
    CH_MapDraw(&game->map, game->services);
    CH_DrawPlayer(&game->player, game->services, &game->map);

    game->view.position.x = -game->player.position.x + (game->services->app->size.w/2);
    game->view.position.y = -game->player.position.y + (game->services->app->size.h/2);
    GFX_UpdateView(&game->view, game->services->shader);
}