#ifndef DISKMAP_H_INCLUDED
#define DISKMAP_H_INCLUDED

///index of files in the disk.
///Don't modify the content of the disk, only index


struct File                         ///File in the memory
{
    size_t  id;                     //id of the element
    size_t  addrDeb;                //address of begin
    size_t  size;                   //size of the file
};
typedef struct File File;

struct Diskmap                      ///Mapping of the memory in the disk
{
    File*   map;                    //list of files
    size_t  msize;                  //size of the map
    size_t  diskSize;               //total size of the disk
};
typedef struct Diskmap Diskmap;

Diskmap*    dm_init();              ///create in memory

void        dm_free(                ///free instance of Diskmap
                Diskmap*    map;    //map
                    );

int8_t      dm_load(                ///Load map from descriptor file, return -1 if fail
                Diskmap*    map,    //map
                char*       path    //path of the data file
                    );

size_t      dm_getFree(             ///Find a free place on the disk, return -1 if fail
                Diskmap*    map,    //map
                size_t      size    //size needed
                        );

int8_t      dm_allocate(            ///Allocate place in the disk, -1 if fail
                Diskmap*    map,    //map
                size_t      addr,   //address
                size_t      size    //size
                        );

int8_t      dm_realloc(             ///reallocation of a file in memory, -1 if fail
                Diskmap*    map,    //map
                File*       file,   //file to reallocate
                size_t      nsize   //new size
                       );

void        dm_ffree(               ///delete a file of the memory
                Diskmap*    map,    //map
                File*       file    //file to delete
                     );

File*       dm_optimize(            ///concatenate this file to the previous file
                Diskmap*    map,    //map
                File*       file    //file to move
                        );






#endif // DISKMAP_H_INCLUDED
