#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "Entite.h"
#include "MemMap.h"
#include "Disk.h"


struct  File                ///File access, for read and write
{
    Entity* rep;            //rep sys file
    Filem*  mem;            //rep memory

    size_t  pos;            //position iterator
};

File*   finit();            ///create a file instance

void    ffree(              ///free file in memory
            File*   file
              );

void    fload(              ///load an existing file
            File*   file,   //file
            char*   path    //path
              );

int8_t  fcreate(            ///create new file
            File*   file,   //file
            char*   path    //path
                );

void    funload(            ///unload file
            File*   file    //file
                );


uint8_t fread(              ///read byte in file
            File*   file    //file
              );

int8_t  fwrite(             ///write byte in file
            File*   file,   //file
            int8_t  byte    //byte to write
               );

uint8_t fseek(              ///move cursor to a new position
            File*   file,   //file
            size_t  npos    //new position
              );

void    fflush(             ///writing the file on the hard disk
            File*   file    //file
               );




#endif // FILE_H_INCLUDED
