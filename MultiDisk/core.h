#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <stdio.h>

void*   srealloc(                       ///safe reallocator
            void* ptr,                  //ptr to reallocate
            size_t nsize,               //new size
            void(*frr)(void*)           //free if fail
                );


#endif // CORE_H_INCLUDED
