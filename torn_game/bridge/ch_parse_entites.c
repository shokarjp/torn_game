#include "ch_parse_entities.h"
#include "../third-party//inireader//iniread.h"


CH_EntityTable
CH_EntityTableInit(void)
{
    CH_EntityTable et = {0};

    return et;

}



void
CH_LoadEntityTableFromINI(CH_EntityTable* et, u8* ini_name)
{

    iniread_t parser = iniread_open(ini_name);
    if (parser.status)
    {
        TORN_Error("Failed to load-in the entity ini file.", "[inireader]: failed to read the file");
    }
    // calculate the # of 'identifiers'
    i32 identifiers = 0;
    
    i32* ids = MEM_ArenaAlloc(MEM_GetDefaultArena(), sizeof(i32) * 1024);
    for (i32 i = 0; i < parser.lexer.token_array.used; i++)
    {
        if (parser.lexer.token_array.token[i].type == INIREAD_SECTION)
        {
            
            ids[identifiers++] = i;
            printf("The following entity, %s, is acknowledged to exist.\n", parser.lexer.token_array.token[i].value);
        }
    }

    printf("%i sections found.\n", identifiers);
    for (int i = 0; i < identifiers; i++)
    {
            char* section = parser.lexer.token_array.token[ids[i]].value;
            
        printf("\t-> %s\n", section);
    
    }

    et->passthroughs = MEM_ArenaAlloc(MEM_GetDefaultArena(), sizeof(CH_EntityPassThrough) * identifiers );
    et->size = identifiers;
    
    for (int i = 0; i < identifiers; i++){
                

                
               if (i == 0)
               {
                // NOTE: scuffed solution - please fix in the future!
                // PROBLEM: The ini-reader does not read the first element if with a pedding!
                iniread_key_t i_padding = iniread_get_key(parser, parser.lexer.token_array.token[ids[i]].value, 0);

               }
               
                iniread_key_t iflag = iniread_get_key(parser, parser.lexer.token_array.token[ids[i]].value, "flag");
                iniread_key_t ifollow_distance = iniread_get_key(parser, parser.lexer.token_array.token[ids[i]].value, "follow_distance");
                iniread_key_t iattack_damage = iniread_get_key(parser, parser.lexer.token_array.token[ids[i]].value, "attack_damage");
                iniread_key_t iid = iniread_get_key(parser, parser.lexer.token_array.token[ids[i]].value, "id");
                iniread_key_t itexture_loc = iniread_get_key(parser, parser.lexer.token_array.token[ids[i]].value, "texture_loc");
                iniread_key_t ispeed = iniread_get_key(parser, parser.lexer.token_array.token[ids[i]].value, "speed");
                   
                if (parser.status )
                {
                    TORN_Error("Malformed INI file - please contact the developers or reinstall!", ini_name);
                    exit(1);
                }
                
        
                i32 flag = atoi(iflag.value);
                i32 follow_distance = atoi(ifollow_distance.value);
                i32 attack_damage = atoi(iattack_damage.value);
                i32 id = atoi(iid.value);
                i32 speed = atoi(ispeed.value);
                
        
                
                et->passthroughs[i].attack_damage = attack_damage;
                et->passthroughs[i].follow_distance = follow_distance;
                et->passthroughs[i].flag = flag;
                et->passthroughs[i].id = id;
                et->passthroughs[i].speed = speed;
                et->passthroughs[i].texture = GFX_LoadTexture2D(itexture_loc.value);   
            
                if (et->passthroughs[i].texture.data == 0)
                {
                    TORN_Error("Could not load texture file.", itexture_loc.value);
                    exit(1);
                }
    }

}
