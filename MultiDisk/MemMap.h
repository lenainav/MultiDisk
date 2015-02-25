#ifndef MEMMAP_H_INCLUDED
#define MEMMAP_H_INCLUDED

#include "Entite.h"
#include <stdio.h>

struct Memmap                   ///map of the file system
{
    Entity*     root;           //root entity (contain all entities)
    Entity*     actual;         //actual directory ptr
    size_t      len;            //number of entities
    size_t      size;           //total size of elements in the disk

    FILE*       finfo;          //file with the map (on another disk)
    char*       fpath;          //path of the info file
};
typedef struct Memmap Memmap;

Memmap*     mm_init();          ///create in memory

void        mm_free(            ///free memory
                Memmap* mm      //map
                    );

Entity*     mm_count(           ///Count the number of entity
                Memmap* mm      //map
                     );

Entity*     mm_get(             ///access to the entity, NULL if fail
                Memmap* mm,     //map
                char*   path    //path to access entity
                   );

Entity*     mm_add(             ///Create new entity, - if fail
                Memmap* mm,     //map
                char*   path    //path
                   );

Entity*     mm_cd(              ///Change actual directory
                Memmap* mm,     //map
                char*   path    //new actual path
                  );


#endif // MEMMAP_H_INCLUDED
