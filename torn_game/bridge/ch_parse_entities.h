#ifndef CH_PARSE_ENTITIES
#define CH_PARSE_ENTITIES
#include "../torn.h"
#include "../game/ch_entity.h"

#ifdef INIREAD_IMPL
#undef INIREAD_IMPL
#include "../third-party/inireader/iniread.h"
#endif
typedef struct CH_EntityTable CH_EntityTable;
struct CH_EntityTable
{
    CH_EntityPassThrough* passthroughs;
    i32 end;
    i32 size;
};

CH_EntityTable CH_EntityTableInit(void);
void CH_LoadEntityTableFromINI(CH_EntityTable* et, u8* ini_name);

#endif