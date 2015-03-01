#include "Core.h"

void*   srealloc(               ///safe reallocator
            void* ptr,          //ptr to reallocate
            size_t nsize,       //new size
            void(*frr)(void*)   //free if realloc fail
            )
{
    void* tmp = ptr;

    ptr = realloc(ptr, nsize);
    if (ptr == NULL)
    {
        if (frr != NULL)
            frr(tmp);
        else
            ptr = tmp;

        return NULL;
    }

    return ptr;
}
