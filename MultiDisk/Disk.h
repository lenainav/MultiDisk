#ifndef DISK_H_INCLUDED
#define DISK_H_INCLUDED

#include <stdio.h>

#include "DiskFile.h"
#include "MemMap.h"
#include "DiskMap.h"


struct Disk                     ///Disk base
{
    char*       diskName;       //name of the disk
    char*       finfos;         //file with infos
    DiskFile**  files;          //files descriptor
    size_t      nFiles;         //number of files
    Memmap*     map;            //memory map
    Diskmap*    dmap;           //file map in the disk

};
typedef struct Disk Disk;


Disk*       dsk_init();         ///create disk in memory

int         dsk_create(         ///create disk in DDs
                Disk*   dsk,    //disk
                char*   name,   //disk name
                char**  dds,    //files
                int     len     //number of disk
                       );

int         dsk_load(           ///load disk with info file
                Disk*   dsk,    //disk
                char*   infos   //info file path
                     );

void        dsk_unload(         ///Save and unload the disk
                Disk*   dsk     //disk
                       );


///Global vars for id
size_t  __id;                   //id seed

void    id_init();              //initialize ids
size_t  id_define();            //define the id




#endif // DISK_H_INCLUDED
