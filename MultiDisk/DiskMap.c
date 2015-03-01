#include "DiskMap.h"
#include "core.h"

#include <stdlib.h>

#define ERROR 0 //do an error system


Diskmap*    dm_init()               ///create in memory
{
    Diskmap* map = malloc(sizeof(Diskmap));
    if (map == NULL)
        return ERROR;

    map->diskSize = map->msize = 0;
    map->map = NULL;

    return map;
}


void        dm_free(                ///free instance of Diskmap
                Diskmap*    map     //map
                    )
{
    if (map->map != NULL)
        free(map->map);
    free(map);
}


int8_t      dm_load(                ///Load map from descriptor file, return -1 if fail
                Diskmap*    map,    //map
                char*       path    //path of the data file
                    )
{
    return -1; ///function to do
}

size_t      dm_getFree(             ///Find a free place on the disk, return 0 if fail
                Diskmap*    map,    //map
                size_t      size    //size needed
                        )
{
    size_t addr = 1;
    size_t it   = 0;

    while (addr + size < map->diskSize) //parcours du disque a la recherche d'une place libre
    {
        if (it >= map->msize)
        {
            if (addr + size < map->diskSize)
                return addr;
            else
                return 0;
        }

        if (addr < map->map[it].addrDeb)    //addr est avant l'element pointer
        {
            if (addr + size < map->map[it].addrDeb) //s'il y a la place de placer le fichier
                return addr;
            else
            {
                addr += (map->map[it].addrDeb - addr) + map->map[it].size +1; //placement après l'element
                it++; //selection de l'element suivant
            }
        }
        else
            it++;
    }

    return 0;
}

int8_t      dm_allocate(            ///Allocate place in the disk, -1 if fail
                Diskmap*    map,    //map
                size_t      addr,   //address
                size_t      size    //size
                        )
{
    if (srealloc(map->map, map->msize +1, NULL) != NULL)
    {
        map->msize += 1;
        map->map[map->msize] = (Filem) {addr, 0, size};
        return 1;
    }
    else
        return -1;
}

int8_t      dm_realloc(             ///reallocation of a file in memory, -1 if fail
                Diskmap*    map,    //map
                Filem*       file,  //file to reallocate
                size_t      nsize   //new size
                       );

void        dm_ffree(               ///delete a file of the memory
                Diskmap*    map,    //map
                Filem*       file   //file to delete
                     )
{
    size_t it = 0;

    while(map->map[it].id != file->id && it < map->msize)
        it++;

    if (it < map->msize)
    {
        map->map[it] =(Filem) {0};
        it++;

        while(it < map->msize)
        {
            map->map[it -1] = map->map[it];
            it++;
        }
    }

    if (srealloc(map->map, map->msize -1, &free) != NULL)
        map->msize -= 1;
}

Filem*      dm_optimize(            ///concatenate this file to the previous file
                Diskmap*    map,    //map
                Filem*       file   //file to move
                        )
{
    size_t it = 0;

    while(map->map[it].id != file->id && it)
    {
        it++;
        if (it >= map->msize)
            return NULL;
    }

    if (it > 0)
        map->map[it].addrDeb = map->map[it -1].addrDeb + map->map[it -1].size +1;

    return file;
}

void        dm_sort(                ///Sort elements by address
                Diskmap*    map     //map
                    )
{
    if (map->msize < 2) // nothing to sort
        return;

    size_t it = 1;
    Filem elem = map->map[0];

    while(it < map->msize)
    {
        if (elem.addrDeb > map->map[it].addrDeb)
        {
            map->map[it -1] = map->map[it];
            map->map[it] = elem;
        }

        it++;
    }
}

size_t      dm_serr(                ///Search error in the disk mapping, msize if no error, first file with error otherwise
                Diskmap*    map
                    )
{
    if (map->msize >= 2) //nothing to do if less than 2 files
    {
        size_t it = 1;

        while (it < map->msize) //check all files in the disk
        {
            if (map->map[it-1].addrDeb + map->map[it-1].size >= map->map[it].addrDeb) //test : if previous file is in the present file
                return it -1; //error, return first file

            it++;
        }
    }

    return map->msize;
}
