#ifndef DISKFILE_H_INCLUDED
#define DISKFILE_H_INCLUDED

#include <stdint.h>
#include <stdio.h>

struct DiskFile                     ///file of the disk
{
    size_t      id;                 //file id (because if you have more than 255 disk...)
    char*       fpath;              //file path
    FILE*       file;               //file stream
    size_t      size;               //size of the disk in the file

};
typedef struct DiskFile DiskFile;

DiskFile*   df_init();              ///create in memory

int         df_create(              ///create disk file
                DiskFile*   df,     //disk file
                char*       path,   //disk path
                size_t      size    //disk size
                      );

int         df_load(                ///load file
                DiskFile*   df,     //disk file
                char*       path    //file path
                    );


void        df_destroy(             ///destroy ptr
                DiskFile*   df      //disk file
                       );





#endif // DISKFILE_H_INCLUDED
