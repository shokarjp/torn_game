#ifndef CH_DARRAY_H
#define CH_DARRAY_H
#include "../torn.h"
typedef struct CH_DArray CH_DArray;
struct CH_DArray
{
    void* ptr;
    i32 used;
    i32 u_ptr_size;
};

CH_DArray CH_CreateArray(size_t size);
void CH_PushArray(CH_DArray* array);
void CH_DestroyArray(CH_DArray* array);

#endif
